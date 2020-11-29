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

// find min cut using max flow
namespace f0 {
const int N = 500 + 10;
const ll INFTY = 1e13;

int n, m;
vector<int> es[N];
ll cap[N][N];
ll Ffn[N][N];

ll parent[N];

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    cap[a][b] += 1;
    cap[b][a] += 1;
    es[a].push_back(b);
    es[b].push_back(a);
  }

  ll Ftot = 0;
  while (1) {
    ll F = 0;
    queue<pair<int, ll>> q;
    for (int i = 0; i < N; ++i) {
      parent[i] = i == 1 ? 1 : 0;
    }
    q.push({1, INFTY});
    while (!q.empty()) {
      ll Fv;
      int v;
      std::tie(v, Fv) = q.front();
      q.pop();

      if (v == n) {
        F = Fv;
        break;
      }

      for (int w : es[v]) {
        if (parent[w]) {
          continue;
        }
        ll Fw = min<ll>(Fv, cap[v][w] - Ffn[v][w]);
        if (Fw == 0) {
          continue;
        }
        parent[w] = v;
        q.push({w, Fw});
      }
    }
    if (F == 0) {
      break;
    }
    // cerr << "F: " << F << "|";
    for (int w = n; w != 1; w = parent[w]) {
      //   cerr << w << "<-[" << Ffn[parent[w]][w] << "/" << cap[parent[w]][w]
      //        << "]-" << parent[w] << ";";
      Ffn[parent[w]][w] += F;
      Ffn[w][parent[w]] -= F;
    }
    // cerr << "\n";
    Ftot += F;
  }
  cout << Ftot << "\n";
  vector<pair<int, int>> cut;
  stack<int> dfs;
  dfs.push(1);
  for (int i = 0; i < N; ++i) {
    parent[i] = i == 1 ? 1 : 0;
  }
  // Note that this is NOT EQUIVALENT to the commented code:
  //   vector<pair<int, int>> cuts;
  //   while (!dfs.empty()) {
  //     int v = dfs.top();
  //     dfs.pop();
  //     for (int w : es[v]) {
  //       if (parent[w]) {
  //         continue;
  //       }
  //       if (Ffn[v][w] == cap[v][w]) { cuts.push_back({v, w})};
  //       else { parent[w] = v; dfs.push(w); }
  //     }
  //   }
  // Consider G:
  // 1⋯ ⋯ 2
  // ┃╲   ⋮
  // ┃ ╲  ⋮
  // ┃  ╲ ⋮
  // ┃   ╲⋮
  // 4────3
  // flow is sent through bold lines. All edges are unit capacity
  // =========
  // Now look at the residual graph:
  // 1⋯ ⋯ 2
  //      ⋮
  //      ⋮
  //      ⋮
  //      ⋮
  // 4    3
  // =========
  // - (1, 2, 3) are in one connected component. Thus, (1, 4) and (3, 4) are a
  //   cut.
  // - On the other hand, according to the flawed algorithm, because the edge
  //   (1, 3) is saturated, the edge [1-3] must be a cut edge. This is patently
  //   FALSE.
  // - Saturated edges are not cut edges! Cut edges are those that cross from
  //   the s component into the t component.

  while (!dfs.empty()) {
    int v = dfs.top();
    dfs.pop();
    for (int w : es[v]) {
      if (parent[w]) {
        continue;
      }
      if (Ffn[v][w] < cap[v][w]) {
        parent[w] = v;
        dfs.push(w);
      }
    }
  }
  // find cut edge
  for (int v = 1; v <= n; ++v) {
    if (!parent[v]) {
      continue;
    }
    for (int w : es[v]) {
      if (!parent[w]) {
        cout << v << " " << w << "\n";
      }
    }
  }
  return 0;
}

} // namespace f0

int main() { return f0::main(); }