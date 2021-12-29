#include <algorithm>
#include <assert.h>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1e5 + 10;
string s, t;

bool zero(int i) { return s[i] == '0' && t[i] == '0'; }
bool one(int i) { return s[i] == '1' && t[i] == '1'; }
bool both(int i) {
  return (s[i] == '0' && t[i] == '1') || (s[i] == '1' && t[i] == '0');
}

int main() {
  ios::sync_with_stdio(false);
  int tests;
  cin >> tests;

  while (tests--) {
    int n;
    cin >> n >> s >> t;
    int tot = 0;
    int i = 0;
    for (; i < n ;) {
      // cout << "i:" << i << "| tot: " <<  tot << "\n";
      if (both(i)) {
        tot += 2;
        i += 1;
      } else if (zero(i)) {
        if (i + 1 == n) { tot += 1; i += 1;}
        else if ((zero(i + 1) || both(i + 1))) {
          // break here.
          tot += 1;
          i += 1;
        } else {
          // take [00 \\ 11]
          assert(one(i + 1));
          tot += 2;
          i += 2;
        }
      } else {
        assert(one(i));
        if (i + 1 == n) { i += 1; }
        else if (zero(i+1)) {
          tot += 2; i += 2;
        } else if (both(i+1)) {
          i += 1;
        } else {
          assert(one(i+1));
          i += 1; 
        }
      }
    } // end for
    // cout << "i:" << i << "| tot: " <<  tot << "\n";
    cout << tot << "\n";

  } // end while
  return 0;
}
