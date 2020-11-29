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
int parent[N];
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
      parent[i] = i == S ? S : 0;
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
        if (parent[w] || fw == 0) {
          continue;
        }
        parent[w] = v;
        q.push({w, fw});
      }
    }
    if (Fiter == 0) {
      break;
    }
    F += Fiter;
    for (int v = T; v != S; v = parent[v]) {
      flow[parent[v]][v] += Fiter;
      flow[v][parent[v]] -= Fiter;
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

int main() { return f0::main(); }
