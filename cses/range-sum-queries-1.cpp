#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

template <typename T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename K, typename V>
using ordered_map =
    __gnu_pbds::tree<K, V, less<K>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename T1, typename T2>
ostream &operator<<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}

// standard segtree, closed intervals.
namespace f0 {

static const int N = 2 * int(1e5) + 10;
ll n, nq;
ll xs[N];
ll tree[4*N];
void build(ll l, ll r, ll t) {
    if (l > r) { return; }
    if (l == r) { tree[t] = xs[l]; return; }
    ll mid = (l + r)/2;
    // l <= mid < r
    // 1 1 2
    build(l, mid, t*2); // length of [l..mid] decreased from [l..r]
    build(mid+1, r, t*2+1); // length of [mid+1,r] decreased from [l..r]
    tree[t] = tree[t*2] + tree[t*2+1];
}
void build() { build(0, n-1, 1); }

// 4sort
// tuple<ll, ll, ll, ll> sort4(ll n0, ll n1, ll n2, ll n3) {
//     // ([0, 1] || [2, 3]); ([0, 2] || [1, 3]); [1, 2]
//     if(n0>n1) { swap(n0, n1); }
//     if(n2>n3) { swap(n1, n3); }
//     if(n0>n2) { swap(n0, n2); }
//     if(n1>n3) { swap(n1, n3); }
//     if(n1>n2) { swap(n1, n2);
//     return make_tuple(n0, n1, n2, n3);
// }

ll q(ll l, ll r, ll t, ll ql, ll qr) {
    if (l > r) { return 0; }

    // qqtt | ttqq
    if (qr < l || r < ql) { return 0; }

    // qttq
    if (ql <= l && r <= qr) { return tree[t]; }

    ll mid = (l + r)/2;
    return q(l, mid, t*2, ql, qr) + q(mid+1, r, t*2+1, ql, qr);
}

ll q(ll ql, ll qr) { return q(0, n-1, 1, ql, qr); }


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> nq;
    for(ll i = 0; i < n; ++i) { cin >> xs[i]; }
    build();

    for(ll i = 0; i < nq; ++i) {
        ll ql, qr; cin >> ql >> qr;
        cout << q(ql-1, qr-1) << "\n";
    }

    return 0;
}
}

// standard segree, half-open intervals.
namespace f1 {
    static const int N = 2 * int(1e5) + 10;
    int xs[N];
    int tree[4*N];

    // [l, r)
    void build(int l, int r, int t) {
        if (r - l <= 0) { return; }
        if (r - l == 1) { tree[t] = xs[l]; return; }
        int mid = (l + r)/2;
        // l <= mid < r
        // [l..r) -> [l..mid) shrunk because mid < r
        build(l, mid);
        // [l..r) -> [mid..r) shrunk? why?
        // 1 2 -> [1, 1) | [1, 2)
        // Interesting, we need the *additional* information that:
        //    r - l > 1
        // OK, so assume we know that r - 1 > 1. 
        //
        // r = l + 2 + δ where δ ≥ 0
        build(mid, r);
    }
}

int main() { f1::main(); }
