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

namespace segtree {

const int N = 2 * int(1e5) + 10;
int arr[N];
int tree[4 * N];
const int INFTY = 1e9 + 7;

void build(int t, int l, int r) {
    if (l == r) { tree[t] = arr[l]; return; }
    int mid = (l + r)/2; // l <= mid < r;
    build(t*2, l, mid);
    build(t*2+1, mid+1, r);
    tree[t] = min(tree[t*2], tree[t*2+1]);
}

int query(int t, int l, int r, int ql, int qr) {
    // ttqq  || qqtt
    if (r < ql || qr < l) { return INFTY; }
    if (ql <= l && r <= qr) { return tree[t]; }
    int mid = (l + r)/2;
    return min(query(t*2, l, mid, ql, qr), query(t*2+1, mid+1, r, ql, qr));
}

void upd(int t, int l, int r, int qix, int qval) {
    if (qix < l || r < qix) { return; }
    if (l == r) { 
        assert(l == qix);
        tree[t] = qval;
        return;
    }
    int mid = (l + r)/2;
    if (qix <= mid) { upd(t*2, l, mid, qix, qval); }
    else { upd(t*2+1, mid+1, r, qix, qval); }
    tree[t] = min(tree[t*2], tree[t*2+1]);
}

void print(int n) {
    cerr << "\narr: ";
    for(int i = 1; i <= 4*n; ++i) { cerr << tree[i]  << " "; }
    cerr << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < N; ++i) { arr[i] = INFTY; }
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }

    build(1, 1, n);
    // print(n);
    while (q--) {
        int ty;
        cin >> ty;
        if (ty == 1) {
            int k, v;
            cin >> k >> v;
            upd(1, 1, n, k, v);
            // print(n);
        } else {
            int a, b;
            cin >> a >> b;
            cout << query(1, 1, n, a, b) << "\n";
        }
    }
    return 0;
}
}


// https://cp-algorithms.com/data_structures/sqrt_decomposition.html
namespace sqrtdecomp {

    int main() {
        return 0;
    }
};

int main() {
    return sqrtdecomp::main();
}
