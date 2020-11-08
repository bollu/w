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

const ll N = 2 * ll(1e5) + 10;
ll arr[N];
ll tree[4*N];

void build(ll t, ll l, ll r) {
    if (l == r) { tree[t] = arr[l]; return; }
    ll mid = (l + r)/2;
    // l <= mid < r
    build(t*2, l, mid);
    build(t*2+1, mid+1, r);
    tree[t] = tree[t*2] + tree[t*2+1];
}

ll query(ll t, ll l, ll r, ll ql, ll qr) {
    // qttq
    if (ql <= l && r <= qr) { return tree[t]; }
    // ttqq | qqtt
    if (r < ql || qr < l) { return 0; }
    ll mid = (l+r)/2;
    return query(t*2, l, mid, ql, qr) + query(t*2+1, mid+1, r, ql, qr);
}

void upd(ll t, ll l, ll r, ll qix, ll qval) {
    if (qix < l || r < qix) { return; }
    if (l == r) { tree[t] = qval; return; }

    ll mid = (l + r)/2;
    if (qix <= mid) { upd(t*2, l, mid, qix, qval); }
    else { upd(t*2+1, mid+1, r, qix, qval); }
    tree[t] = tree[t*2] + tree[t*2+1];
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, q; cin >> n >> q;
    for(ll i = 1; i <= n; ++i) { cin >> arr[i]; }
    build(1, 1, n);

    while(q--) {
        ll ty; cin >> ty;
        if (ty == 1) {
            ll k, u; cin >> k >> u;
            upd(1, 1, n, k, u);
        } else {
            ll ql, qr; cin >> ql >> qr;
            cout << query(1, 1, n, ql, qr) << "\n";
        }
    }
    return 0;
}
