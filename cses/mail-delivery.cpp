#include <assert.h>

#include <algorithm>
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

// Heirholz (magic!)
namespace f0 {

const int N = 2 * (1e5 + 10);
const int M = 3 * (1e5 + 10);

int n, m;
set<int> es[N];
queue<int> vspath;

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int a, b;
    cin >> a >> b;
    es[a].insert(b);
    es[b].insert(a);
  }

  for (int i = 1; i <= n; ++i) {
    if (es[i].size() % 2 == 1) {
      cout << "IMPOSSIBLE\n";
      return 0;
    }
  }

  // Proof of correctness:
  stack<int> vs;
  vs.push(1);
  while (!vs.empty()) {
    int v = vs.top();
    if (es[v].size() == 0) {
      vspath.push(v); // visit vertex first, then visit its entire subtree.
      vs.pop();
    } else {
      int w = *es[v].begin();
      es[v].erase(w);
      es[w].erase(v);
      vs.push(w);
    }
  }
  if (vspath.size() != m + 1) {
    cout << "IMPOSSIBLE\n";
    return 0;
  }

  while (!vspath.empty()) {
    cout << vspath.front() << " ";
    vspath.pop();
  }
  cout << "\n";
  return 0;
}

} // namespace f0

// Tucker
// https://scihub.wikicn.top/10.2307/2319893
// http://www.mathcs.emory.edu/~rg/book/chap5.pdf
// https://cstheory.stackexchange.com/questions/31538/runtime-of-tuckers-algorithm-for-generating-a-eulerian-circuit
// https://gyu.people.wm.edu/Fall2009/math490/euler%20circuit-Sarah%20Will.pdf
// 1. At each vertex arbitrarily pair off, and link together, the incident
// edges. The result is a set
//   of chains that, having no ends, must be circuits.
// 2. Repeatedly combine any two circuits with a common vertex until we have
//    vertex-disjoint circuits
// 3. Since the graph is connected, there is just one circuit – an Euler
//    Circuit.
namespace f1 {
const int N = 1e5 + 10;
int n, m;
vector<int> fwd[N];
vector<int> bwd[N];
int fwdix[N];
int bwdix[N];

vector<tuple<int, int, int>> epairs;
int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; ++i) {
    int a, b;
    cin >> a >> b;
    fwd[a].push_back(b);
    bwd[b].push_back(a);
  }
  return 0;
  }
} // namespace f1

int main() { return f1::main(); }
