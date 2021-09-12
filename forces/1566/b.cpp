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
const int INFTY = 1e9;


namespace wrong {
struct State {
  int sum;
  int mex;
};
State dp[N]; // false: don't break. true: break.


int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;

  while (t--) {
    string s; cin >> s;
    const int n = s.size();
    dp[0].sum = 0; dp[0].mex = 0;

    for(int i = 1; i <= n; ++i) {
      int c = s[i-1] - '0';
      
      // can extend here. 
      if (c == dp[i-1].mex) {
        int breaksum = dp[i-1].sum + dp[i-1].mex;
        int breakmex = (c == 0) ? 1 : 0;

        int keepsum = dp[i-1].sum;
        int keepmex = c+1;

        // break here, versus don't break here
        if (breaksum + breakmex > keepsum + keepmex) {
          dp[i].sum = keepsum;
          dp[i].mex = keepmex;
        } else {
          dp[i].sum = breaksum;
          dp[i].mex = breakmex;
        }
      } else {
        dp[i].mex = dp[i-1].mex;
        dp[i].sum = dp[i-1].sum;
      }
    }
    for(int i = 0; i <= n; ++i) {
      cout << "[" << i << "]:" << (i== 0 ? '*': s[i-1]) << "  " 
      << "  |sum:" << dp[i].sum << " | mex: " << dp[i].mex << "\n";
    }
    cout << dp[n].sum + dp[n].mex << "\n";
  }    
}

};



int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
 
  while (t--) {
    string s; cin >> s;
    const int n = s.size();
    bool has[3] = {false, false, false};
    for(int i = 0; i < n; ++i) {
      has[s[i] - '0'] = true;
    }

    int i = 0;
    int n0s = 0;
    while(i < n) {
      if (s[i] == '0') {
        n0s++;
        while(i < n && s[i] == '0') { i++; }
      } else {
        i++;
      }
    }
 
    int mins = n0s;
    if (has[0] && has[1] && has[2]) { mins = min<int>(mins, 3); }
    else if (has[0] && has[1]) { mins = min<int>(mins, 2); }
    else if (has[0]) { mins = min<int>(mins, 1); }
    cout << mins << "\n";
  }
  return 0;
}
