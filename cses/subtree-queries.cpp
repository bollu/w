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
int t2v[4*N]; // euler tour
ll st[16*N]; //segtree over t2v
ll vs[N]; //values
vector<int> es[N]; // edges.
int n, q;
int t0 = 0; //initial time. Variable always points to last used slot..
int v2tin[N];

// NOTE TO SELF: IT IS *CRITICAL* that a vertex only appears once.
// It will *store* the ending time, but WILL NOT CREATE A NEW ENTRY
// in `t2v`. This allows it to know the subtree, without creating new
// nodes.
int v2tout[N];

void dfs(int u, int v) {
    ++t0; v2tin[v] = t0;
    t2v[t0] = v;
    
    for(int w : es[v]) {
        if (w == u) { continue; } dfs(v, w);
    }
    v2tout[v] = t0;
}

void build(int t, int l, int r) {
    if (l == r) { st[t] = vs[t2v[l]]; return; }
    int mid = (l + r)/2;
    build(t*2, l, mid); build(t*2+1, mid+1, r);
    st[t] = st[t*2] + st[t*2+1];
}

ll query(int t, int l, int r, int ql, int qr) {
    // q t t q
    if (ql <= l && r <= qr) { return st[t]; }
    // q q t t | t t q q 
    if (qr < l || r < ql) { return 0; }
    int mid = (l + r)/2;
    return query(t*2, l, mid, ql, qr) + query(t*2+1, mid+1, r, ql, qr);
}   

void update(int t, int l, int r, int q, ll v) {
    if (l == r) { st[t] = v; return; }
    // q l r | l r q 
    if (q < l || r < q) { return; }
    int mid = (l+r)/2;
    if (q <= mid) {
        update(t*2, l, mid, q, v);
    } else {
        update(t*2+1, mid+1, r, q, v);
    }
    st[t] = st[t*2] + st[t*2+1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) cin >> vs[i];
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b; es[a].push_back(b); es[b].push_back(a);
    }
    dfs(1, 1);
    build(1, 1, t0);
    
    for(int i = 0; i < q; ++i) {
        int q; cin >> q;
        if (q == 1) {
            int s, x; cin >> s >> x;
            update(1, 1, n, v2tin[s], x);
        } else {
            int s; cin >> s;
            cout << query(1, 1, n, v2tin[s], v2tout[s]) << "\n";
        }
          
    }
    return 0;
}
