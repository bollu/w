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

const int N = 500 + 10;
const ll minval(ll a, ll b) {
  if (a == -1) {
    return b;
  }
  if (b == -1) {
    return a;
  }
  return std::min<ll>(a, b);
}
ll cap[N][N];
ll flow[N][N];
int parent[N];
vector<int> es[N];
int n, m;
int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; ++i) {
    ll a, b, c;
    cin >> a >> b >> c;
    es[a].push_back(b);
    es[b].push_back(a);
    cap[a][b] += c;
  }

  ll totf = 0;
  while (1) {
    ll f = 0;
    for (int i = 0; i < N; ++i) {
      parent[i] = 0;
    }
    queue<pair<int, ll>> q;
    q.push({1, -1});

    parent[1] = 1;

    while (!q.empty() && f == 0) {
      int v;
      ll fv;
      tie(v, fv) = q.front();
      q.pop();

      // cerr << "[v: " << v << "]\n";
      if (v == n) {
        // cerr << "  [f: " << fv << "]\n";
        f = fv;
        break;
      }

      for (int w : es[v]) {
        ll fvw = minval(fv, cap[v][w] - flow[v][w]);
        assert(fvw >= 0);
        if (parent[w] || fvw == 0) {
          continue;
        }
        parent[w] = v;
        q.push({w, fvw});
        assert(flow[parent[w]][w] + fvw <= cap[parent[w]][w]);
        // cerr << "  [v: " << v << " w: " << w << " cap: " << cap[v][w]
        //      << " flow: " << flow[v][w] << " vwresidual:" << vwresidual
        //      << " vbottleneck:" << vbottleneck << "]\n";
      }
    }

    if (!f) {
      break;
    }

    totf += f;

    // cerr << "[path: ";
    int w = n;
    while (w != 1) {
      assert(flow[parent[w]][w] <= cap[parent[w]][w]);
      assert(flow[parent[w]][w] + f <= cap[parent[w]][w]);
      assert(flow[w][parent[w]] - f <= cap[w][parent[w]]);

      flow[parent[w]][w] += f;
      flow[w][parent[w]] -= f;
      w = parent[w];
    }
    // cerr << " | tot: " << totf << "]\n";
  }
  cout << totf << "\n";

  return 0;
}
