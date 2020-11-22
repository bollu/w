#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <stdlib.h> // for exit()

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template<typename T>
using minqueue = priority_queue<T,vector<T>,greater<T>>;

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

const int N = 2e5 + 10;

int v2val[N];
vector<int> es[N];

int t0 = 0;
ll t2val[3*N];
ll st[4*3*N];

int v2tin[N], v2tout[N];
int n, q;



void dfs(int u, int v) {
    ++t0;
    t2val[t0] = v2val[v];
    v2tin[v] = t0;

    for(int w : es[v]) {
        if (u == w) { continue; }
        dfs(v, w);
    }

    ++t0;
    t2val[t0] = -v2val[v];
    v2tout[v] = t0;
}

void build(int tr, int l, int r) {
    if (l == r) { st[tr] =  t2val[l]; return; }
    int mid = (l+r)/2;
    build(tr*2, l, mid);
    build(tr*2+1, mid+1, r);
    st[tr] = st[tr*2] + st[tr*2+1];
}

void upd(int tr, int l, int r, int q, int v) {
    if (l == r) { st[tr] = v; return; }
    // q l r | l r q
    if (q < l || r < q) { return; }
    int mid = (l+r)/2;
    if (q <= mid) {
        upd(tr*2, l, mid, q, v);
    } else {
        upd(tr*2+1, mid+1, r, q, v);
    }
    st[tr] = st[tr*2] + st[tr*2+1];
}

ll query(int tr, int l, int r, int ql, int qr) {
    // q l r q
    if (ql <= l && r <= qr) { return st[tr]; }
    // q q l r | l r q q
    if (qr < l || r < ql) { return 0; }
    int mid = (l+r)/2;
    return query(tr*2, l, mid, ql, qr) + query(tr*2+1, mid+1, r, ql, qr);

}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) { cin >> v2val[i]; }
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b); es[b].push_back(a);
    }

    dfs(1, 1);
    build(1, 1, t0);
    for(int i = 0; i < q; ++i) {
        int t; cin >> t;
        if (t == 1) {
            int s, x; cin >> s >> x;
            upd(1, 1, t0, v2tin[s], x);
            upd(1, 1, t0, v2tout[s], -x);

        } else {
            int s; cin >> s;
            cout << query(1, 1, t0, v2tin[1], v2tin[s]) << "\n";
        }
    }

    return 0;
}
