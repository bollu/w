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

int main() {
  int n;
  cin >> n;
  // vector<int> xs(n);
  multiset<int> occs;
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  for (int i = 0; i < n; ++i) {
    int x;
    cin >> x;
    // cin >> xs[i];
    // we want to extend the chain with the smallest element so far.
    // If no chain [c(1)..c(cn), d(1)..d(dn), e(1)..e(en)]
    //   has an element c(cn) < xs[i] or d(dn) < xs[i] or e(en) < xs[i], then
    //   extend the chain with the smallest last element.
    // If no such chain exists, ie xs[i] < c(cn), xs[i] < d(dn), x[i] < e(en),
    // then start a new chain. This new chain will be the
    //   new smallest chain.
    //
    // find first elem > x;
    auto it = occs.upper_bound(x);
    if (it == occs.end()) {
        occs.insert(x); continue; 
    }

  }

  cout << occs.size() << "\n";
  return 0;
}
