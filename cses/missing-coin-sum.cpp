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

// counting upwards, keeping 'sum' counter.
namespace f1 {
void main() {
  int n;
  cin >> n;
  vector<ll> xs(n);
  for (ll i = 0; i < n; ++i) {
    cin >> xs[i];
  }
  sort(xs.begin(), xs.end());
  ll r = 0; // Σ_i=1^n xs[i]
  for (ll i = 0; i < n; ++i) {
    if (xs[i] <= r+1) {
      // xs[i] can represent r+1.
      // We can already represent [0..r]
      // By adding, we can represent [0..r] + (xs[i]) = [xs[i]..r+xs[i]]
      // Since xs[i] <= r+1, [xs[i]..r+xs[i]] <= [r+1, 2r+1].
      // In total, we can represent [0..r] (not using xs[i]) and [<=r+1, <=2r+1]
      // (by using xs[i]) So we can can be sure we won't miss numbers when going
      // from [1..r] to [xs[i]<=r+1...] The largest number we can represent is
      // [xs[i]+r].
      r += xs[i]; // max number we can represent is previous max plus current
    } else {
      // xs[i] > r+1;
      cout << r + 1 << "\n";
      return;
    }
  }
  cout << r + 1 << "\n";
}

} // namespace f1

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  f1::main();
  return 0;
}

