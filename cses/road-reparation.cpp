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

const int N = 1e5 + 10;
int n, m;
struct edge { 
    int v, w, cost;
    bool operator > (const edge &other) const {
        return make_tuple(cost, v, w) > 
                make_tuple(other.cost, other.v, other.w);
    }
};

int ps[N];
// max. height of subtree. TODO: find more intuitive way to write this.
int hts[N]; 

int root(int i) {
    if (i == ps[i]) { return i; }
    return ps[i] = root(ps[i]);
}

void unite(int i, int j) {
    i = root(i); j = root(j);
    if (i == j) { return; }
    if (hts[i] > hts[j]) {
        ps[j] = i;
    } else if (hts[i] < hts[j]) {
        ps[i] = j;
    } else {
        ps[j] = i; hts[i]++;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    minqueue<edge> q;
    for(int i = 1; i < N; ++i) { ps[i] = i; }

    for(int i = 0; i < m; ++i) {
        edge e;
        cin >> e.v >> e.w >> e.cost;
        q.push(e);
    }

    ll tot = 0;
    while(!q.empty()) {
        edge e = q.top(); q.pop();
        // cerr << "[" << e.v << " " << e.w << " cost: " << e.cost << "]\n";
        // already in the same component, connecting will create a cycle
        if (root(e.v) == root(e.w)) { continue; }
        // cerr << "\t chosen.\n";
        tot += e.cost;
        unite(e.v, e.w);
    }

    int comp = root(1);
    for(int i = 1; i <= n; ++i) {
        if (root(i) != comp) { cout << "IMPOSSIBLE\n"; return 0; }
    }

    cout << tot << "\n";
    return 0;
}
