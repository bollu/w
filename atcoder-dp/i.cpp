#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
#include <iomanip>
using namespace std;
using ll = long long;
using rr = double;

const int N = 3000 + 3;
rr ps[N];
int n;

// dp[d][k]: prob. to get k heads using [0, d) coins.
// [d for dimension | k for subspsace dimension]
rr dp[N][N];

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> ps[i];
  }

  dp[0][0] = 1;

  // prob. of getting 0 heads using [0, d) coins.
  rr tailprod = 1;
  for (int d = 1; d <= n + 1; ++d) {
    tailprod *= (1 - ps[d - 1]);
    dp[d][0] = tailprod;
  }

  // prob. of getting  k>=1 heads using [0, 0) = no coins.
  for (int k = 1; k <= n + 1; ++k) {
    dp[0][k] = 0;
  }

  for (int d = 1; d <= n + 1; ++d) {
    for (int k = 1; k <= n + 1; ++k) {
      rr p = ps[d - 1];
      dp[d][k] = (1 - p) * dp[d - 1][k] + p * dp[d - 1][k - 1];
    }
  }

  rr tot = 0;
  for (int k = n / 2 + 1; k <= n; ++k) {
    tot += dp[n + 1][k];
  }

  cout << setprecision(20) << tot << "\n";
}
