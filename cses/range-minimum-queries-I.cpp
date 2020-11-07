#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

// https://cses.fi/problemset/task/1647

using namespace std;
// Closed intervals
namespace f0 {
constexpr int INFTY = 1e9 + 7;

template<typename T>
void show(T& container) {
  for (const auto& x: container) cout << x << ' ';
  cout << '\n';
}

// @Goose: we assumed that we have closed intervals here, right? [l, r]
// node_idx is 1-indexed, l, r is 0-indexed, [l,r]
void init_segtree(vector<int>& segtree, vector<int>& vals, int node_idx, int l, int r){
  // everything is 0 indexed since that cleans up our formulas a bit
  // if (l > r) { return; }
  if (l == r) { segtree[node_idx] = vals[l]; return; }

  int left_idx = node_idx << 1;
  int right_idx = left_idx + 1;

  // l, r < 2e5, so no overflow in (l+r)
  // I can't hear you anymore so I'll just chug along
  // discord is fucking up so I think you can see this
  int mid = l + (r-l)/2;

  // r = l + 2
  // mid = l + 1
  // (l, l+1) (l+2, l+2)
  //
  // r = l + 1
  // mid = l + 0
  // (l, l) (l+1, l+1)
  

  // l <= mid < r
  // [l, r] --> [l, mid] < r
  // [mid+1, r] l <= mid < mid + 1 | [l, r] --> [mid+1, r]
  // build left
  init_segtree(segtree, vals, left_idx, l, mid);
  // build right
  init_segtree(segtree, vals, right_idx, mid+1, r);

  // combine
  segtree[node_idx] = min({segtree[left_idx], segtree[right_idx]});
  return;
}

// node_idx is 1-idx
// ql, qr, nl, nr are 0-idx [ql, qr], [nl, nr]
int query_segtree(
    vector<int>& segtree, vector<int>& vals,
    int node_idx, int ql, int qr, int nl, int nr)
{
  // if (nl > nr) { return INFTY; }

  // node range within query range
  if ( (ql <= nl) && (nr <= qr) ) return segtree[node_idx];

  // query range outside node range
  if ( (ql > nr) || (qr < nl) ) return INFTY;

  // query and node ranges overlap and we deal with crap
  int left_idx = node_idx << 1;
  int right_idx = left_idx + 1;

  // l, r < 2e5, so no overflow in (l+r)
  int mid = nl + (nr-nl)/2;

  return min({
      query_segtree(segtree, vals, left_idx, ql, qr, nl, mid),
      query_segtree(segtree, vals, right_idx, ql, qr, mid+1, nr)
  });
}

int main () {
  int i;
  int j;
  // ah cool
  int n, q; cin >> n >> q;
  vector<int> values(n);
  for(auto& val: values) cin >> val;

  // write the damn segtree here
  vector<int> segtree(4*n, INFTY);
  // current segtree index, node_idx, l, r
  init_segtree(segtree, values, 1, 0, n-1);

  // show(segtree);
  while(q--){
    int ql, qr; cin >> ql >> qr;
    cout << query_segtree(segtree, values, 1, ql-1, qr-1, 0, n-1) << '\n';
  }
  return 0;
}
}

// Half-open intervals
namespace f1 {
constexpr int INFTY = 1e9 + 7;

template<typename T>
void show(T& container) {
  for (const auto& x: container) cout << x << ' ';
  cout << '\n';
}

// node_idx is 1-indexed, l, r is 0-indexed, [l,r)
void init_segtree(vector<int>& segtree, vector<int>& vals, int node_idx, int l, int r){
  // everything is 0 indexed since that cleans up our formulas a bit
  if (l+1 == r) { segtree[node_idx] = vals[l]; return; }

  int left_idx = node_idx << 1;
  int right_idx = left_idx + 1;

  // l, r < 2e5, so no overflow in (l+r)
  // I can't hear you anymore so I'll just chug along
  // discord is fucking up so I think you can see this
  int mid = l + (r-l)/2;
  // bollu: correctness proof?
  // delta = 3; [0, 1, 2, 3)
  // [0, 1) [1, 3)
  
  // delta = 2; [0, 1, 2)
  // [0, 1) [1, 2)
  
  // l <= mid < r /\ r - l >= 2
  // mid = l + δ where δ > 0
  // [l, r] --> [l, mid] < r
  // [mid, r] l <= mid < mid + 1 | [l, r] --> [mid+1, r]
  
  // build left
  init_segtree(segtree, vals, left_idx, l, mid);
  // build right
  init_segtree(segtree, vals, right_idx, mid, r);

  // combine
  segtree[node_idx] = min({segtree[left_idx], segtree[right_idx]});
  return;
}

// node_idx is 1-idx
// ql, qr, nl, nr are 0-idx [ql, qr), [nl, nr)
int query_segtree(
    vector<int>& segtree, vector<int>& vals,
    int node_idx, int ql, int qr, int nl, int nr)
{
  // if (nl > nr) { return INFTY; }

  // node range within query range
  // query: [nl=i, nr=i+1) | tree : [ql=i, qr=i+1)
  if ( (ql <= nl) && (nr <= qr) ) { return segtree[node_idx];}

  // query range outside node range
  if ( (ql >= nr) || (qr <= nl) ) return INFTY;

  // query and node ranges overlap and we deal with crap
  int left_idx = node_idx << 1;
  int right_idx = left_idx + 1;

  // l, r < 2e5, so no overflow in (l+r)
  int mid = nl + (nr-nl)/2;

  return min({
      query_segtree(segtree, vals, left_idx, ql, qr, nl, mid),
      query_segtree(segtree, vals, right_idx, ql, qr, mid, nr)
  });
}

// 2. generalize to template shenanigans
// 3. find "crystal clear" ways to implement query intersection and disjointness. 
// 3a. min(...), max(...) 
// 3b. lengths of the intervals + 
// 3c. sort all the endpoints (ql, qr, nl, nr)
//      (ql, nl, nr, qr) -> node range within query
//      (ql, qr, nl, nr) -> node range outside query
//      (nl, nr, ql, qr) -> node range outside query
//      ...              -> overlap

// bottom up segtrees: https://codeforces.com/blog/entry/18051

int main () {
  int i;
  int j;
  // ah cool
  int n, q; cin >> n >> q;
  vector<int> values(n);
  for(auto& val: values) cin >> val;

  // write the damn segtree here
  vector<int> segtree(4*n, INFTY);
  // current segtree index, node_idx, l, r
  init_segtree(segtree, values, 1, 0, n);

  // show(segtree);
  while(q--){
    int ql, qr; cin >> ql >> qr;
    cout << query_segtree(segtree, values, 1, ql-1, qr, 0, n) << '\n';
  }
  return 0;
}
}

namespace f2 {
  
const int N = 2 * int(1e5) + 10;
constexpr int INFTY = 1e9 + 7;

template<typename T>
void show(T& container) {
  for (const auto& x: container) cout << x << ' ';
  cout << '\n';
}

int n;
int t[2*N];

// 0 1 2 3 4 5 6 7
//     # # * * * *
//     v ------^^^
//     ----^^^
void build() {
  for (int i = n - 1; i > 0; --i) { t[i] = min({t[i*2], t[i*2+1]}); }
}

// from child, update parent.
// p^1 works because if you are odd,  ie, (n*2+1), you get n*2
//                   if you are even, ie, (n*2),  you get n*2+1


// parent -children-> (parent*2, parent*2+1) -/2-> (parent, parent)
//
// 0 1 2 3 4 5 6 7
//
// children of 2 = 4, 5
// 4/2 = 5/2 = 2
void modify(int p, int value) {  // set value at position p; 0 < p < n?
  p += n;
  while(p > 1) { t[p/2] = min({t[p], t[p^1]}); p /= 2; }
}


// sum on interval [l, r)
// 0 <= l <= r 
int query(int l, int r) {  
  int res = INFTY;
  l += n; r += n;
  // if even, belong to parent of my group
  // if odd, don't have a parent, so I need to add to the computation.
  while(l < r) {
    if (l & 1) { res = min({res, t[l]}); l++;  }
    if (r & 1) { r--; res = min({res, t[r]});  }
    l /= 2; r /= 2;
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int nqueries;
  cin >> n >> nqueries;
  for(int i = 0; i < n; ++i) { cin >> t[n + i]; }
  build();
  while(nqueries--) {
    int ql, qr; cin >> ql >> qr;
    cout << query(ql-1, qr) << '\n';

  }
  

  return 0;
}

}

int main() { f2::main(); }

