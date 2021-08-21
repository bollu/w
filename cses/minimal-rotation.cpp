#include <assert.h>

#include <algorithm>
#include <bitset> // instead of bool[N];
#include <ext/typelist.h>
#include <iostream>
#include <iterator>
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

// https://codeforces.com/blog/entry/90035

namespace automata {
struct Node {
  int len;    // length of longest string in equivalence class
  int minend; // minimum ending position of occurence

  Node *smol;
  map<char, Node *> beeg;
  Node() = default;
  Node(const Node &other) {
    this->len = other.len;
    this->minend = other.minend;
    this->smol = other.smol;
    this->beeg = other.beeg;
  }
};

Node *start = nullptr;
Node *end = nullptr;


void init() {
  start = new Node;
  start->smol = start;
  start->len = 0;
  start->minend = -1;
  end = start;
}

void extend(char c) {
  Node *cur = new Node();
  cur->len = end->len + 1;
  cur->minend = cur->len - 1; // ending index.
  cur->smol = nullptr;        // to be discovered.

  cur->smol = end;
  end = cur; // update end.

  while (!cur->smol->beeg.count(c)) {
    cur->smol->beeg[c] = cur;
    if (cur->smol == start) {
      return;
    } else {
      cur->smol = cur->smol->smol;
    }
  }

  // we tried to add [x+c], where x is a suffix of s.
  // such a state already exists.
  assert(cur->smol->beeg.count(c));
  // assert(relink != start);
  // relink can be start. It could be that the start node has an edge to c.
  Node *p = cur->smol;
  Node *q = cur->smol->beeg[c];
  if (p->len + 1 == q->len) {
    // [q] = [p]:c
    cur->smol = q;
    return;
  } else {
    // [q] is longer that [x+c]
    // so [q] is of the form [x+c+delta]
    // [q] must be longer than [p] since q contains [x+c].
    // vvv TODO: why is it okay to not modify minend?

    Node *qsmol = new Node(*q);
    qsmol->len = cur->smol->len + 1;
    assert(qsmol->len < q->len);
    cur->smol = qsmol; // setup link.

    // q contains [p]:c
    // we have a state for [p]:c.
    // relink q to [p]:c.
    // vvv TODO: DEAR GOD WHY IS THIS CORRECT GOD DAMN IT?
    q->smol = qsmol;
    // relink all things smoler than p that used to point to p to point to
    // qsmol.
    while (p->beeg.count(c) && p->beeg[c] == q) {
      p->beeg[c] = qsmol;
      if (p == start) {
        return;
      } else {
        p = p->smol;
      }
    }
    return;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  init();
  // build automata for s+s.
  for (char c : s) {
    extend(c);
  }
  for (char c : s) {
    extend(c);
  }

  Node *minimal = start;
  for (int i = 0; i < s.size(); ++i) {
    /// cout << sa[root].edge.begin() -> first; /// if you want to output such
    /// string
    cout << minimal->beeg.begin()->first;
    minimal = minimal->beeg.begin()->second;
  }

  cout << "\n";

  return 0;
}

}; // namespace automata

namespace hashsoln {

const int MOD = 1e9 + 7;
const int BASE = 53;

int powmod(int x, int n) {
  if (n == 0)
    return 1;
  if (n % 2 == 1) {
    return (1LL * powmod(x, n - 1) * x) % MOD;
  } else {
    int half = powmod(x, n / 2);
    return (1LL * half * half) % MOD;
  }
}

// P[l] = pow(base, -l) (mod MODULO)
vector<int> P;
// H[r] = sum[k=0 to r] s[k] pow(base, k) (mod MOD)
vector<int> H;

// hash[s] = sum[i=0 to |s|] s[i] pow(b, i)
void init(const string &s) {
  const int n = s.size();
  int b = 1;

  // compute polynomial of the form hash(c(i)) b^i.
  // p[i] is (b^i)^(-1) b^{-i}.
  P.assign(n, 0);
  H.assign(n + 1, 0);
  for (int i = 0; i < n; ++i) {
    const int c = (s[i] - 'a' + 1);
    H[i + 1] = (H[i] + 1LL * b * c) % MOD;
    P[i] = powmod(b, MOD - 2);
    b = (1LL * b * BASE) % MOD;
  }
}

// I. defn
// hash(s[l..r]) =
//     let t = s[l..r]
//     let len = r-l+1 in
//     sum [i=0 to len] t[i] * pow(b, i)
//
// II. substitute s[l..r]:
// hash(s[l..r]) =
//     let t = s[l..r]
//     let len = r-l+1 in
//     sum [i=0 to len] s[i+l] * pow(b, i)
//
// III. substitute i+l = k
// hash(s[l..r]) =
//     sum [k=l to r] s[k] * pow(b, k-l)
//
// IV. multiply by pow(b, l):
// hash(s[l..r]) * pow(b, l)=
//     sum [k=l to r] s[k] * pow(b, k-l) * pow(b, l)
// hash(s[l..r]) * pow(b, l)=
//     sum [k=l to r] s[k] * pow(b, k)
// hash(s[l..r]) * pow(b, l)=
//     {sum [k=0 to r] s[k] * pow(b, k)} - {sum[k=0 to l] s[k] pow(b, k)}
// V, use pow(b, -l)
// hash(s[l..r]) =
//     pow(b, -l) * {sum [k=0 to r] s[k] * pow(b, k)} - {sum[k=0 to l] s[k]
//     pow(b, k)}

int hash_substr(int l, int r) {
  assert(r >= l);
  return (1LL * (H[r] - H[l] + MOD) * P[l]) % MOD;
}

int min_cyc(string &s) {
  const int n = s.size();
  s += s;

  int smol = 0; // current guess for smallest rotation.

  for (int i = 1; i < n; ++i) { // try all strings.

    int lcp = 0;
    int l = 0;
    int r = n - 1;
    while (l <= r) {
      int m = (l + r) / 2; // len.
      // if (s.substr(smol, m) == s.substr(i, m)) {
      if (hash_substr(smol, smol + m) == hash_substr(i, i + m)) {
        lcp = m;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    // find lcp betwen smol and
    if (lcp == n) {
      continue; // Equal
    } else if (s[smol + lcp] > s[i + lcp]) {
      smol = i;
    }
  }

  return smol;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  string s;
  cin >> s;
  init(s);
  const int n = s.size();

  int rot = min_cyc(s);

  for (int ix = 0; ix < n; ++ix) {
    cout << s[(rot + ix) % n];
  }
  cout << "\n";
  return 0;
}
}; // namespace hashsoln

int main() {
  // hashing collides x(
  // hashsoln::main();
  automata::main();
}
