//https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/help-ashu-1/
#include<iostream>
#include<tuple>
#include<cmath>
#include<assert.h>
using namespace std; using I=int; int n;
int even[100001*2];
int evenst[100001*2];
int odd[100001*2];
int oddst[100001*2];
void build(int nl, int stix, int nr) {
  //cout << "build[" << nl << "|" << stix << "|" << nr << "]\n";
  assert(nl <= nr);
  if (nl == nr) { evenst[stix] =  even[nl]; oddst[stix] =  odd[nl]; return;}
  int mid = (nl + nr)/2;
  build(nl, stix*2, mid); build(mid+1, stix*2+1, nr); 
  evenst[stix] = evenst[stix*2]+evenst[stix*2+1];
  oddst[stix] = oddst[stix*2]+oddst[stix*2+1];
}
void set(int qix, int nl, int stix, int nr, int val) {
  // cout << "set[" << nl << "|" << nr << "] " << qix << ":=" << val << "\n";
  if (qix < nl || nr < qix) { return;  }
  if (nl == nr) {
    if (nl == qix && nr == qix) { evenst[stix] = val % 2 == 0; oddst[stix] =  val % 2 == 1; }
    return;
  }
  int mid = (nl + nr)/2;
  if (qix <= mid) set(qix, nl, stix*2, mid, val);
  else set(qix, mid+1, stix*2+1, nr, val);
  evenst[stix] = evenst[stix*2]+evenst[stix*2+1];
  oddst[stix] = oddst[stix*2]+oddst[stix*2+1];
}
int query(int ql, int qr, int nl, int stix, int nr, int isodd) {
  int ret; 
  if (qr < nl || nr < ql) { ret = 0; }
  else if (ql <= nl && nr <= qr) { ret = isodd ? oddst[stix] : evenst[stix]; }
  else {
    int mid = (nl + nr)/2;
    ret = query(ql, qr, nl, stix*2, mid, isodd) + query(ql, qr, mid+1, stix*2+1, nr, isodd);
  }
  //cout << "query[" << nl << "|" << stix << "|" << nr << "] " << "range[" << ql << "," << qr << "]" << " := " << ret << "\n";
  return ret;
}
int main() {
  cin.tie(NULL); ios::sync_with_stdio(false);
  int n; 
  cin >> n; 
  for(int i = 1; i <= n; ++i) { int t; cin >> t; even[i] = t % 2 == 0; odd[i]  = t % 2 == 1; }
  build(1, 1, n);
  int q; cin >> q;
  while(q--) {
    int t, x, y; cin >> t >> x >> y;
    if (t == 0) set(x, 1, 1, n, y);
    else if (t == 1) cout << query(x, y, 1, 1, n, false) << "\n";
    else if (t == 2) cout << query(x, y, 1, 1, n, true) << "\n";
  }
}
