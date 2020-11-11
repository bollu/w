#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric> // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

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

// naive segtree with universe reduction. too slow.
namespace f0 {
const int N = 2 * ll(1e5) + 10;
int n, q;
int nsals;

int xs[N];
int counts[10 *N];
int tree[10 * N];

set<int> uniqsals;
unordered_map<int, int> compress;

struct query { char ty; int v, w; };
query qs[N];

void build(int t, int l, int r) {
    if (l == r) { tree[t] = counts[l]; return; }
    int mid = (l+r)/2;
    build(t*2, l, mid);
    build(t*2+1, mid+1, r);
    tree[t] = tree[t*2] + tree[t*2+1];
}

void upd(int t, int l, int r, int ix, int delta)  {
    if (l == r) {  tree[t] += delta; return; }
    int mid = (l+r)/2;
    if (ix <= mid) { upd(t*2, l, mid, ix, delta); }
    else { upd(t*2+1, mid+1, r, ix, delta); }
    tree[t] = tree[t*2] + tree[t*2+1];
    return;
}
int query(int t, int l, int r, int a, int b) {
    // q t t q
    if (a <= l && r <= b) { return tree[t]; }
    // q q t t | t t q q
    if (b < l || r < a) { return 0; }
    int mid = (l+r)/2;
    return query(t*2, l, mid, a, b) + query(t*2+1, mid+1, r, a, b);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> q;
  for (int i = 1; i <= n; ++i) { 
      cin >> xs[i];
      uniqsals.insert(xs[i]);
  }
  for(int i = 0; i < q; ++i) {
      cin >> qs[i].ty >> qs[i].v >> qs[i].w;
      if (qs[i].ty == '!') { uniqsals.insert(qs[i].w); }
      else { uniqsals.insert(qs[i].v); uniqsals.insert(qs[i].w); }
  }

  // compress
  nsals = uniqsals.size();
  int uid = 1; 
  for(int sal : uniqsals) {
      compress[sal] = uid++;
  }

  for(int i = 1; i <= n; ++i) { 
      xs[i] = compress[xs[i]];
      counts[xs[i]]++;
  }

  build(1, 1, nsals);

  for(int i = 0; i < q; ++i) {
      if (qs[i].ty == '!') {
          int oldsal = xs[qs[i].v];
          int newsal = compress[qs[i].w];
          upd(1, 1, nsals, oldsal, -1);
          upd(1, 1, nsals, newsal, +1);
          xs[qs[i].v] = newsal;
      } else {
          cout << query(1, 1, nsals, compress[qs[i].v], compress[qs[i].w]) << " ";
          cout << "\n";
      }
  }

  return 0;
}

}

// https://codeforces.com/blog/entry/77128
namespace f1 {

}



int main() { f1::main(); }