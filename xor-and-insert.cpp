// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/xor-and-insert-92b9b529/description/
#include<assert.h>
#include<iostream>
#include<queue>
#include<tuple>
using namespace std;
struct tn { tn *next[2] = { nullptr, nullptr };};
tn *root = new tn();

int log2floor(int n) {
    if (n <= 1) return 0;
    return 1 + log2floor(n/2);
}


void insert(int n, tn *p) {
  for(int ix = log2floor(n); ix >= 0; ix--) {
      if (n & (1 << ix)) {
          if (!p->next[1]) p->next[1] = new tn;
          p = p->next[1];
      } else {
          if (!p->next[0]) p->next[0] = new tn;
          p = p->next[0];
      }
  }
}

void printtree() {
    cout << "----\n";
    queue<tuple<string, int, tn*>> q;
    q.push(make_tuple("", 0, root));
    int curh = 0;
    // bfs
    while(!q.empty()) {
        tn *t; int th; string n;
        tie(n, th, t) = q.front(); q.pop();
        if (th != curh) { 
            curh = th;
            cout << "\n";
        }
        cout << "|" << n << "| ";
        if (t->next[0]) q.push(make_tuple(n + "0", th+1, t->next[0]));
        if (t->next[1]) q.push(make_tuple(n + "1", th+1, t->next[1]));
    }
    cout << "\n----\n";
}

int min(tn *p, int xorcur) {
    cout << "*** min(" << xorcur << "):";
    int n = 0;
    for(int ix = log2floor(xorcur); ix >= 0 && (p->next[0] != nullptr || p->next[1] != nullptr); ix--) {
        if(xorcur & (1 << ix)) {
            if (p->next[1]) { n |= 1 << ix; p = p->next[1]; cout << "[" << ix << ": 1 -> 1]"; }
            else  { p = p->next[0]; cout << "[" << ix << ": 1 -> 0]"; }
        } else { // xorcur == 0
            if (p->next[0]) { p = p->next[0]; cout << "[" << ix << ": 0 -> 0]"; }
            else { n |= 1 << ix; p = p->next[1]; cout << "[" << ix << ": 0 -> 1]"; }
        }
    }
    cout << "\n";
    return n ^ xorcur;
}

void mk0() {
  tn *p = root;
  for(int i = 0; i < 30; ++i) { p->next[0] = new tn(); p = p->next[0]; }
}

int main() {
  int xorcur = 0;
  int q; cin >> q;
  // create 10^9 = (2^10)^3 = 2^30 number of 0s
  // mk0();
  while(q--) {
    int t; cin>>t;
    /*so that during query,when we xor with xorcur, this cancels */ 
    if (t == 1) { int x; cin>>x; cout << x << "^" << xorcur << " = " << (x ^ xorcur) << " | "; insert(x^xorcur, root);}
    else if (t == 2) { int x; cin>>x; xorcur ^= x; } 
    else if (t == 3) { int ans = min(root, xorcur); cout << "| " << ans  << "\n"; }
    cout << "CURXOR: " << xorcur << "\n";
    printtree();
  }
  return 0;
}
