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
const int NOT = N;
int n, m;
vector<int> es[3*N];
vector<int> esT[3*N];
bool vis[3*N];
vector<int> exits;
void dfs(int v) {
    vis[v] = true;
    for(int w : es[v]) {
        if (vis[w]) { continue; } dfs(w);
    }
    exits.push_back(v);
}

bool visT[3*N];
int comp[3*N];
void dfsT(int v, int c) {
    visT[v] = true;
    comp[v] = c;
    for(int w : esT[v]) {
        if (visT[w]) { continue; } dfsT(w, c);
    }
}

// Read | https://cses.fi/book/book.pdf
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    for(int i = 1; i <= n; ++i) {
        int ixs[2];
        for(int j = 0; j < 2; ++j) {
            char sgn; int ix;
            cin >> sgn >> ixs[j];
            if (sgn == '+') { ixs[j] = ixs[j]*2+1; }
            else { ixs[j] = ixs[j]*2; }

        }

        // a \/ b = !a => b; !b => a
        es[ixs[0]^1].push_back(ixs[1]); // !a => b
        es[ixs[1]^1].push_back(ixs[0]); // !b => a

        esT[ixs[1]].push_back(ixs[0]^1); // b => !a
        esT[ixs[0]].push_back(ixs[1]^1); // a => !b
    }
                                                                      
    // run SCC algorithm. first find DFS numbers.
    for(int i = 1; i <= 2*m; ++i) {
        if (!vis[i]) { dfs(i); }
    }

    // visit in reverse order of exiting; exit last => visit first.
    for(int i = exits.size()-1; i >= 0; i--) {
        if (!visT[i]) { dfsT(i, i+1); }
    }

    // check if x and !x are in the same component.
    for(int i = 1; i <= m; ++i) {
        if (comp[2*i] == comp[2*i+1]) {  
            if (comp[2*i] != 0) {
                cout << "IMPOSSIBLE\n"; return 0;
            }
        }
    }

    for(int i = 1; i <= m; ++i) {
        if (comp[2*i] == 0) { cout << "- "; }
        else { cout << (comp[2*i] < comp[2*i+1] ? "- " : "+ "); }
    }
    cout << "\n";
    return 0;
}
