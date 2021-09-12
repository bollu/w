#include <assert.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;


int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    
    while(t--) {
      ll l, r; cin >> l >> r;
      if (l > r) { swap(l, r); }
      if (l == 0 && r == 0) { cout << "0\n"; }
      else if (l == r) { cout << "1\n"; }
      else if ((l + r) % 2 != 0) {
        cout << "-1\n"; continue;
      } else {
        cout << "2\n";
      }
    }


}

