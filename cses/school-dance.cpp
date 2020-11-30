#include <assert.h>

#include <algorithm>
#include <bitset> // instead of bool[N];
#include <iostream>
#include <map>
#include <numeric> // for gcd
#include <queue>
#include <set>
#include <stack>
#include <stdlib.h> // for exit()
#include <vector>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template <typename T> using minqueue = priority_queue<T, vector<T>, greater<T>>;

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

// flow using the usual flow algorithm (edmonds-karp?)
namespace f0 {
const ll INFTY = 1e13;
const int S = 1020;
const int T = 1030;
const int N = 2 * 500 + 50;

set<int> es[N];
int dfsprev[N];
int n, m, k;
ll cap[N][N];
ll flow[N][N];
int BOFFSET = 501;

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> k;
  for (int i = 0; i < k; ++i) {
    int a, b;
    cin >> a >> b;
    b += BOFFSET;
    es[a].insert(b);
    es[b].insert(a);
    es[S].insert(a);
    es[a].insert(S);
    es[T].insert(b);
    es[b].insert(T);
    cap[S][a] = 1;
    cap[a][b] = 1;
    cap[b][T] = 1;
  }
  ll F = 0;
  while (1) {
    ll Fiter = 0;
    for (int i = 0; i < N; ++i) {
      dfsprev[i] = i == S ? S : 0;
    }
    queue<pair<int, ll>> q;
    q.push({S, INFTY});
    while (!q.empty()) {
      int v;
      ll fv;
      tie(v, fv) = q.front();
      if (v == T) {
        Fiter = fv;
        break;
      }
      q.pop();
      for (int w : es[v]) {
        ll fw = min<ll>(fv, cap[v][w] - flow[v][w]);
        if (dfsprev[w] || fw == 0) {
          continue;
        }
        dfsprev[w] = v;
        q.push({w, fw});
      }
    }
    if (Fiter == 0) {
      break;
    }
    F += Fiter;
    for (int v = T; v != S; v = dfsprev[v]) {
      flow[dfsprev[v]][v] += Fiter;
      flow[v][dfsprev[v]] -= Fiter;
    }
  }

  cout << F << "\n";
  for (int v = 1; v <= n; v++) {
    for (int w : es[v]) {
      if (w == S || w == T || flow[v][w] != 1) {
        continue;
      }
      cout << v << " " << (w - BOFFSET) << "\n";
    }
  }
  return 0;
}

} // namespace f0

namespace f1 {

const int N = 500 + 10;
const int M = 500 + 10; 
const int TOT = N + M + 10;
const ll INFTY = 1e13;

const int S = N + M + 5;
const int T = N + M + 6; 

int n, m, k;
vector<int> adj[TOT]; // adjacency list.
int cap[TOT][TOT];
int F[TOT][TOT];
int level[TOT];
int dfsprev[TOT];



int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i = 0; i < k; ++i) {
        int a, b; cin >> a >> b;
        b += N;
        adj[S].push_back(a);
        adj[a].push_back(S);
        adj[a].push_back(b);
        adj[b].push_back(a);
        adj[b].push_back(T);
        adj[T].push_back(b);
        cap[S][a] = cap[a][b] = cap[b][T] = 1;
    }

    // find augmenting paths and push
    ll Ftot = 0;
    // Dinic's: BFS + DFS
    while(1) {
        // Step 1: BFS
        for(int i = 0; i < TOT; ++i) { level[i] = i == S ? 1 : 0; }
        queue<int> bfs;
        bfs.push(S);
        while(!bfs.empty()) {
            int v = bfs.front(); bfs.pop();
            for(int w : adj[v]) {
                if (cap[v][w] - F[v][w] == 0) { continue; }
                if (level[w]) { continue; }
                level[w] = level[v] + 1;
                bfs.push(w);
            }
        }

        // no augmenting path
        if (!level[T]) { break; }

        // Step 2: repeated DFS
        while(1) {
            ll Fiter = 0;
            stack<pair<int, ll>> dfs;
            dfs.push({S, INFTY}); dfsprev[S] = S;
            for(int i = 0; i < TOT; ++i) { dfsprev[i] = i == S ? S : 0; }

            // DFS for augmenting path.
            while(!dfs.empty()) {
                int v = dfs.top().first; ll Fv = dfs.top().second;
                dfs.pop();
                if (v == T) { Fiter = Fv; break; }
                for(int w : adj[v]) {
                    // edge is not part of augmentation.
                    // TODO: vvv do I need this condition? 
                    if (dfsprev[w]) { continue;}
                    if (level[w] != level[v] + 1) { continue; }
                    ll Fw = min<ll>(Fv, cap[v][w] - F[v][w]);
                    if (Fw == 0) { continue; }
                    dfsprev[w] = v;
                    dfs.push({w, Fw});
                }
            }

            // No augmenting path in the BFS(residual)
            if (!Fiter) { break; }

            Ftot += Fiter;
            for(int v = T; v != S; v = dfsprev[v]) {
                F[dfsprev[v]][v] += Fiter; 
                F[v][dfsprev[v]] -= Fiter; 
            }
        } // end augpath while loop

    } // end dinic's while loop.

    cout << Ftot << "\n";
    for (int v = 1; v <= n; v++) {
        for (int w : adj[v]) {
            if (w == S || w == T || F[v][w] != 1) {
                continue;
            }
            cout << v << " " << (w - N) << "\n";
        }
    }
    return 0;
}

} // namespace f1
int main() { return f1::main(); }
