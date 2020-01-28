// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/xor-and-insert-92b9b529/description/
#include<assert.h>
#include<iostream>
using namespace std;
struct tn { tn *next[2] = { nullptr, nullptr };};
tn *root = new tn();
void insert(int i, tn *p) {
  cout << "inserting: " << i << "\n";
  assert(p);
  if (!p->next[i%2]) {p->next[i%2] = new tn(); }
  if (i > 1) insert(i/2, p->next[i%2]);
}

int min(tn *p, int x) {
  bool b = (x%2)^1;
  cout << "XORCUR (" << b << ")";
  if (p->next[b]) return min(p->next[b], x/2) * 2 + b;
  b = b^1;
  if (p->next[b]) return min(p->next[b], x/2) * 2 + b;
  else return 0;
}

void mk0() {
  tn *p = root;
  for(int i = 0; i < 30; ++i) { p->next[0] = new tn(); p = p->next[0]; }
}

int main() {
  int xorcur = 0;
  int q; cin >> q;
  // create 10^9 = (2^10)^3 = 2^30 number of 0s
  mk0();
  while(q--) {
    int t; cin>>t;
    /*so that during query,when we xor with xorcur, this cancels */ 
    if (t == 1) { int x; cin>>x; insert(x^xorcur, root);}
    else if (t == 2) { int x; cin>>x; xorcur ^= x; } 
    else if (t == 3) { cout << "ANS := " << min(root, xorcur) << "\n"; }
  }
  return 0;
}
