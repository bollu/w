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

int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;

  while (t--) {
    int n, s;
    cin >> n >> s;
    if (n == 1) { cout << s << "\n"; }
    else {
      int median = (n-1)/2;
      int m = n - (median);
      // cout << "\t-n:" << n << " |s:" << s << " |median:" << median << " |m:" << m << "  |s/m:" << s/m << "\n";
      cout << s / m << "\n";
    }
  }
}