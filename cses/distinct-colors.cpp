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


// first solution I thought of using DFS; does not work because
// when we enter and exit a left child, we have lost the record that we
// used to have it's color.
namespace f0 {
const int N = 2 * 1e5 + 10;
int n;

int v2color[N];
int v2ncolors[N];

vector<int> es[N];

bool seencolor[N];
int ncolors;

void dfs(int u, int v) {
    const bool newcolor = !seencolor[v2color[v]];
    seencolor[v2color[v]] = true; 
    
    if (newcolor) { ncolors++; }
    for(int w : es[v]) {
        if (u == w) { continue; }
        dfs(v, w);
    }

    v2ncolors[v] = ncolors;
    // include our own color, so decrement after setting num colors.
    if (newcolor) { ncolors--; }
    seencolor[v2color[v]] = false; 
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    set<int> cs;
    map<int, int> c2compress;

    for(int i = 1; i <= n; ++i) {
        int c; cin >> c; v2color[i] = c; cs.insert(c);
    }

    for(int c : cs) {
        if (c2compress.find(c) != c2compress.end()) { continue; }
        c2compress[c] = c2compress.size() + 1;
    }

    for(int i = 1; i <= n; ++i) { v2color[i] = c2compress[v2color[i]]; }
    
    for(int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b); es[b].push_back(a);
    }

    dfs(1, 1);
    for(int i = 1; i <= n; ++i) {
        cout << v2ncolors[i] << " \n"[i==n];
    }


    return 0;
}
} // end f0

int main() { return f0::main(); }