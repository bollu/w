#include <assert.h>
#include <stdlib.h>  // for exit()

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

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template <typename T>
using minqueue = priority_queue<T, vector<T>, greater<T>>;

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


// use all pairs shortest path. slow
namespace f0 {
const int N = 2500 + 10;
const int M = 5000 + 10;
int INFTY = 1e9 + 10;
int adj[N][N];
int best[N];

int add(int a, int b) {
    if (a == -INFTY || b == -INFTY) { return -INFTY; }
    return a + b;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            adj[i][j] = i == j ? 0 : -INFTY;
        }
    }

    for (int i = 0; i < m; ++i) {
        int a, b;
        int x;
        cin >> a >> b >> x;
        adj[a][b] = x;
    }

    // r = the indexes of the middle vertices in a path u~~~x1x2..xn~>v
    // is going to be <= r, so [forall i. xi <= r]
    for (int r = 1; r <= n; ++r) {
        for (int a = 1; a <= n; ++a) {
            for (int b = 1; b <= n; ++b) {
                adj[a][b] = max<int>(add(adj[a][r], adj[r][b]), adj[a][b]);
                // we have a cycle with positive cost
                if (a == b && adj[a][b] > 0) {
                    // adj is along the path
                    if (adj[1][a] != -INFTY && adj[a][n] != -INFTY &&
                        adj[a][a] > 0) {
                        // cerr << "a:" << a << "|b: " << b << "\n";
                        cout << "-1\n";
                        exit(0);
                    }
                }
            }
        }

       // printf("==%d==\n", r);
       //  for (int i = 1; i <= n; ++i) {
       //      for (int j = 1; j <= n; ++j) {
       //          printf("%20lld ", adj[i][j]);
       //      }
       //      printf("\n");
       //  }
       //  printf("===\n");

    }

    cout << adj[1][n] << "\n";
    return 0;
}
}

// use single source shotest path with negative weights (bellman ford)
namespace f1 {
const int N = 2500 + 10;
const int M = 5000 + 10;
int INFTY = 1e9 + 10;
int best[N];

int add(int a, int b) {
    if (a == -INFTY || b == -INFTY) { return -INFTY; }
    return a + b;
}

vector<tuple<int, int, int>> es;
// vertex, wt
vector<pair<int, int>> adjl[N];


int n, m;
bool negcycle;
bool visited[N];
bool onpath[N];

bool dfs(int v) {
    if (visited[v]) { return onpath[v]; }
    visited[v] = true;
    if (v == n) { onpath[v] = true; }
    for(auto e : adjl[v]) { onpath[v] |= dfs(e.first); }
    return onpath[v];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; ++i) { best[i] = -INFTY; }
    best[n] = 0;

    es.reserve(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        int x;
        cin >> a >> b >> x;
        es[i] = {a, b, x};
    }

    for(int v = 0; v < n; ++v) {
        for(int i = 0; i < m; ++i) {
            int a, b, x;
            tie(a, b, x) = es[i];
            best[a] = max<int>(best[a], add(x, best[b]));
        }
    }

    dfs(1);
    for(int i = 0; i < m; ++i) {
        int a, b, w;
        tie(a, b, w)  = es[i];
        // have not stabilizied
        if (onpath[a] && onpath[b] && (best[a] + w > best[b])) {
            cout << -1 << "\n";
        }
    }

    cout << best[1] << "\n";
    return 0;
}
}

int main() { return f1::main(); }
