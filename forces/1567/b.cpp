#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <map>
#include <new>
#include <ostream>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1e6;
int xors[N];

void solve() {
  int mexval, xorval; cin >> mexval >> xorval;

  int x = xors[mexval-1];
  if (xorval == x) { cout << mexval << "\n"; return; }

  if ((x ^ xorval) != mexval) { cout << mexval+1 << "\n"; return; }
  cout << mexval+2 << "\n";; return;
}


int main() {
  xors[0] = 0;
    for(int i = 1; i < N; ++i) {
      xors[i] = xors[i-1] ^ i;
  }
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
      solve();
    }

}

