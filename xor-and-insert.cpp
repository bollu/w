// https://www.hackerearth.com/practice/data-structures/advanced-data-structures/trie-keyword-tree/practice-problems/algorithm/xor-and-insert-92b9b529/description/
#include<assert.h>
#include<iostream>
#include<queue>
#include<tuple>
using namespace std;
using I=long long int;
const I NBITS=30;
struct tn { tn *next[2] = { nullptr, nullptr };};
tn *root = new tn();


void insert(I n, tn *p) {
  for(I ix = NBITS; ix >= 0; ix--) {
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
    I curh = 0;
    // bfs
    while(!q.empty()) {
        tn *t; I th; string n;
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

I mymin(tn *p, I xorcur) {
    cout << "*** min(" << xorcur << "):";
    I n = 0;
    for(I ix = NBITS; ix >= 0 && (p->next[0] != nullptr || p->next[1] != nullptr); ix--) {
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
  for(I i = 0; i < NBITS; ++i) { p->next[0] = new tn(); p = p->next[0]; }
}

int main() {
  I xorcur = 0;
  I q; cin >> q;
  // create 10^9 = (2^10)^3 = 2^30 number of 0s
  insert(0, root);
  while(q--) {
    I t; cin>>t;
    /*so that during query,when we xor with xorcur, this cancels */ 
    if (t == 1) { I x; cin>>x; cout << x << "^" << xorcur << " = " << (x ^ xorcur) << " | "; insert(x^xorcur, root);}
    else if (t == 2) { I x; cin>>x; xorcur ^= x; } 
    else if (t == 3) { I ans = mymin(root, xorcur); cout << "\n\n***ANSWER: " << ans  << "****\n"; }
    cout << "CURXOR: " << xorcur << "\n";
    printtree();
  }
  return 0;
}
