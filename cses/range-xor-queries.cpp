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

static const int N = 2 * int(1e5) + 10;
int n, q;
int xs[N];
int tree[4*N];

void build(int t, int l, int r) {
    if (l == r) { tree[t] = xs[l]; return; }
    int mid = (l + r)/2;
    build(t*2, l, mid);
    build(t*2+1, mid+1, r);
    tree[t] = tree[t*2] ^ tree[t*2+1];
}

int query(int t, int tl, int tr, int ql, int qr) {
    // qttq
    if (ql <= tl && tr <= qr) { return tree[t]; }
    // qqtt; ttqq
    if (qr < tl || tr < ql) { return 0; }

    int tmid = (tl + tr)/2;
    return query(t*2, tl, tmid, ql, qr) ^ query(t*2+1, tmid+1, tr, ql, qr);
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> xs[i];
    build(1, 1, n);
    while(q--) {
        int a, b; cin >> a >> b;
        cout << query(1, 1, n, a, b) << "\n";
    }

    return 0;
}
