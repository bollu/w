// https://usaco.guide/solutions/cses-1160
// https://usaco.guide/silver/func-graphs
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

const int N = 1e5 + 10;;

int n, q;
int tp[N]; // teleport(planet)
int nexts[N][32];

int component[N];
int dfscolor[N];
int cycleix[N];
// size of cycle per component.
int cyclesize[N];

const int W = 0, G = 1, B = 2;

void dfs(int s, int c) {
    if (dfscolor[s] == B) { return; }
    component[s] = c;
    dfscolor[s] = G;
    
    if (dfscolor[tp[s]] == B) { return; }
    else if (dfscolor[tp[s]] == W) { dfs(tp[s], c); }
    else {
        // backedge. color entire cycle.
        int ix = 1;
        int cur = s;
        while(1) {
            cycleix[cur] = ++cyclesize[c];
            cur = tp[cur];
            if (cur == s) { break; }
        }
    }
}
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for(int i = 1; i <= n; ++i) {
        cin >> tp[i];
        nexts[i][0] = tp[i];
    }


    // dfs and mark each component. this also marks nodes in cycles (the roots) as 
    // cycle[x] = true.
    for(int i = 1; i <= n; ++i) { dfs(i, i); }

    // make every node in a cycle a root node so these become roots of the binary lifted
    // paths
    for(int i = 1; i <= n; ++i) { if (cycleix[i]) { nexts[i][0] = i; } }

    // binary lift!
    for(int p = 1; p < 32; ++p) {
        for(int i = 1; i <= n; ++i) {
            // to travel 2n, travel n; n.
            int mid = nexts[i][p-1];
            nexts[i][p] = nexts[mid][p-1];
        }
    }

    for(int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;
        if (component[a] != component[b]) { cout << "-1\n"; continue; }
        if (cycleix[a] && cycleix[b]) {
            return (cycleix[a] - cycleix[b] + cyclesize[component[a]]) % cyclesize[component[a]]; 
        } else if (cycleix[a] && !cycleix[b]) {
            
        } else if (!cycleix[a] && cycleix[b]) {

        } else {
            // neither in cycles.
        }
    }

    return 0;
}
