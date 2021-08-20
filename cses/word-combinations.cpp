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

namespace naive {

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  std::string s;
  cin >> s;

  int k;
  cin >> k;
  vector<string> ts(k);
  for (string &t : ts) {
    cin >> t;
  }
  const int n = s.size();
  vector<ll> dp(n + 1, 0);
  dp[n] = 1; // always possible to create empty string.
  for (int i = n - 1; i >= 0; i--) {
      for(const string &t : ts) {
          int j = 0;
          for(; j < t.size(); ++j) {
              if (j + i >= n) { break; }
              if (t[j] != s[i+j]) { break; }
          }
          // could not use all of the string to match.
          if (j != t.size()) { continue; }
          const int MOD = 1e9 + 7;
          dp[i] = (dp[i] + dp[i+j]) % MOD;
      }
  }

  cout << dp[0] << "\n";
  return 0;
}
} // namespace naive



namespace trie_words {

const int MOD = 1e9 + 7;
struct node {
    int n = 0;
    map<char, node *> next;
};

node *start;

void mk(string &t) {
    node *cur = start;
    for(int i = 0; i < t.size(); ++i) {
        if (!cur->next.count(t[i])) {
            cur->next[t[i]] = new node;
        }
        cur = cur->next[t[i]];
    }
    cur->n++; // number of strings ending here increased.
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  std::string s;
  cin >> s;
  start = new node;

  int k;
  cin >> k;
  vector<string> ts(k);
  for (string &t : ts) {
    cin >> t;
    mk(t);
  }
  const int n = s.size();
  vector<ll> dp(n + 1, 0);
  dp[n] = 1; // always possible to create empty string.
  for (int i = n - 1; i >= 0; i--) {
      node *cur = start;
      for(int j = i; j < n; ++j) {
          if (cur->next.count(s[j])) { cur = cur->next[s[j]]; }
          else { cur = nullptr; break; }
          // invariant: at this point, cur matches str[i:j] (closed)
          dp[i] = (dp[i] + cur->n*dp[j+1]) % MOD;
      }
  }

  cout << dp[0] << "\n";
  return 0;
}
} // namespace trie_words

int main() {
    return trie_words::main();
}
