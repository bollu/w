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
    int n;
    cin >> n;
    string s;
    cin >> s;
    int i = 0;
    for (char c : s) {
      if (c == 'D') {
        cout << 'U';
      } else if (c == 'U') {
        cout << 'D';
      } else if (c == 'L') {
        cout << 'L';
      } else if (c == 'R') {
        cout << 'R';
      }
    }
    cout << "\n";
  }
}
