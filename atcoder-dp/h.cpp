#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;

const int MAX = 1e4 + 5;
char a[MAX][MAX];
int dp[MAX][MAX];
const int MODULO = 1e9 + 7;

int add(int a, int b) { return (a + b) % MODULO; }

int main() {
  int H, W;
  cin >> H >> W;
  for (int r = 0; r < H; ++r) {
    for (int c = 0; c < W; ++c) {
      cin >> a[r][c];
    }
  }

  dp[0][0] = 1;
  for (int r = 0; r < H; ++r) {
    for (int c = 0; c < W; ++c) {
      if (r == 0 && c == 0) { continue; }
      dp[r][c] = 0;
      if (a[r][c] == '#') {
        continue;
      }
      if (r > 0 && a[r - 1][c] == '.') {
        dp[r][c] = add(dp[r][c], dp[r - 1][c]);
      }
      if (c > 0 && a[r][c - 1] == '.') {
        dp[r][c] = add(dp[r][c], dp[r][c - 1]);
      }
    }
  }

  // for(int r = 0; r < H; ++r) {
  //   for(int c = 0; c < W; ++c) {
  //     cout << "[" << a[r][c] << "]" << dp[r][c] << " ";
  //   }
  //   cout << "\n";
  // }
  cout << dp[H - 1][W - 1] << "\n";
}
