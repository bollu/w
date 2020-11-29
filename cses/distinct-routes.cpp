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

namespace f0 {
int n, m;
const ll INFTY = 1e13;
const int N = 500 + 10;
vector<int> es[N];
int cap[N][N];
int flow[N][N];
int parent[N];

vector<vector<int>> paths;

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    es[a].push_back(b);
    es[b].push_back(a); // need reverse edge of 0 capacity.
    cap[a][b] = 1;
  }

  ll Ftot = 0;
  while (1) {
    ll Fiter = 0;
    queue<pair<int, ll>> q;
    q.push({1, INFTY});
    for (int i = 0; i < N; ++i) {
      parent[i] = i == 1 ? 1 : 0;
    }
    while (!q.empty()) {
      int v = q.front().first;
      ll vf = q.front().second;
      q.pop();
      if (v == n) {
        Fiter = vf;
        break;
      }
      for (int w : es[v]) {
        ll wf = min<ll>(vf, cap[v][w] - flow[v][w]);
        if (parent[w] || wf == 0) {
          continue;
        }
        parent[w] = v;
        q.push({w, wf});
      }
    }
    if (Fiter == 0) {
      break;
    }
    Ftot += Fiter;
    vector<int> path;
    for (int i = n; i != 1; i = parent[i]) {
      path.push_back(i);
      flow[parent[i]][i] += Fiter;
      flow[i][parent[i]] -= Fiter;
    }
    path.push_back(1);
    paths.push_back(path);
  }

  // need to eliminate cycles in paths.
  cout << Ftot << "\n";
  for (vector<int> &path : paths) {
    cout << path.size() << "\n";
    int noncycpath[N];
    set<int> seen;
    int ixsrc = 0, szdst = 0;

    while (ixsrc < path.size()) {
      int v = path[ixsrc];
      if (!seen.count(v)) {
        noncycpath[szdst++] = path[ixsrc++];
      } else {
        while (noncycpath[szdst] != v) {
          szdst--;
        }
        szdst++; // keep the vertex, we want one copy of the vertex.
        seen.insert(v);
      }
    }

    for (int i = szdst - 1; i >= 0; i--) {
      cout << noncycpath[i] << " ";
    }
    cout << "\n";
  }
  return 0;
}

} // namespace f0

int main() { return f0::main(); }