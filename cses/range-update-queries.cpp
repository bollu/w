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

static const int N = 2 * int (1e5) + 10;
int n, q;
ll xs[N];
ll tree[4*N];
ll lz[4*N];

void build(int t, int tl, int tr) {
    if (tl == tr) { tree[t] = xs[tl]; return; }
    int tmid = (tl + tr)/2;
    build(t*2, tl, tmid);
    build(t*2+1, tmid+1, tr); 
}

void upd(int t, int tl, int tr, int ql, int qr, ll v) {
    // tt qq | qq tt
    if (tr < ql || qr < tl) { return; }

    // q tt q
    if (ql <= tl && tr <= qr) { lz[t] += v; return; }

    int tmid = (tl + tr)/2;
    upd(t*2, tl, tmid, ql, qr, v);
    upd(t*2+1, tmid+1, tr, ql, qr, v);

}

ll query(int t, int tl, int tr, int qix) {
    if (qix < tl || tr < qix) { return 0; }
    if (tl == tr) { return tree[t] + lz[t]; }

    int tmid = (tl + tr)/2;

    // push down lazy
    lz[t*2] += lz[t];
    lz[t*2+1] += lz[t];
    lz[t] = 0;

    if (qix <= tmid) {
        return query(t*2, tl, tmid, qix);
    } else {
        return query(t*2+1, tmid+1, tr, qix);
    }
 }

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for(int i = 1; i <= n; ++i) { cin >> xs[i]; }
    build(1, 1, n);

    while(q--) {
        int ty; cin >> ty;
        if (ty == 1) {
            int a, b, u; cin >> a >> b >> u;
            upd(1, 1, n, a, b, u);
        } else {
            int k; cin >> k;
            cout << query(1, 1, n, k) << "\n";
        }
    }
    return 0;
}
