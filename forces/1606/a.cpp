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
    string s; cin >> s;
    char lower = s[0];
    char upper = s[0] == 'a' ? 'b' : 'a';

    s[s.size() - 1] = lower;
    cout << s << "\n";
  }
}
