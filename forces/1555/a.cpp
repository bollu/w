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


ll dp[121];
ll calc(ll n) {
  ll n120 = n/120;
  ll out = 0;
  out += dp[120] * n120;
  out += dp[n % 120];

  if (n120 >= 1 && (n % 120 == 1 || n % 120 == 2)) {
    out -= 10;
  } else if (n120 >= 1 && (n % 120 == 3 || n % 120 == 4)) {
    out -= 5;
  }
  return out;

}

const ll INFTY = 1e5;
int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;

    for(int i = 0; i <= 120; ++i) {
      if (i == 0) { dp[i] = 0; }
      else if (i <= 6) { dp[i] = 15; }
      else if (i <= 8) { dp[i] = 20; }
      else if (i <= 10) { dp[i] = 25; }
      else {
        dp[i] = min<ll>(min<ll>(15 + dp[i-6], 20 + dp[i-8]), 25 + dp[i-10]);
      }
    }

    
    while(t--) {
      ll n; cin >> n;
      cout << calc(n) << "\n";
    }


}

