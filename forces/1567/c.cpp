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

namespace dp {
const int N = 32;
// we write xs[n:0] for the digits of the inpit number x.
int dp[N][10][10];
void solve() {
    string s;
    cin >> s;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = 0; k < 10; ++k) {
                dp[i][j][k] = 0;
            }
        }
    }
    // why only 0,0?
    // interpret the number qwerty as 0qwerty, now we want there to be zero
    // carry at the nth digit so we get 0.
    // dp[n][0][0] = 1;

    // compute possibilities at final index.
    const int n = s.size();
    assert(n < N);
    // if input at ultimate+1 digit has no carries, then there is 1 way to
    // produce it legally (0 + 0), since output must be 0.
    dp[0][0][0] = 1;
    for (int ix = 0; ix < n; ix++) {
        for (int d1 = 0; d1 < 10; d1++) {
            for (int d2 = 0; d2 < 10; d2++) {
                for (int carrycur = 0; carrycur < 2; carrycur++) {
                    for (int carrynext = 0; carrynext < 2; carrynext++) {
                        const int newcarrycur = carrynext;
                        const int newcarrynext = (d1 + d2 + carrycur) / 10;
                        const int digit = (d1 + d2 + carrycur) % 10;
                        if (digit != s[ix] - '0') { continue; }
                        // cout << "[" << carrynext << ", " << carrycur << " + " << d1 << " + " << d2 << " = " << s << "[" << ix << "]:" << 
                        //  s[ix] << "\n";
                        dp[ix+1][carrycur][carrynext] += dp[ix][newcarrycur][newcarrynext];
                    }
                }
            }
        }
    }

    cout << dp[n][0][0] - 2 << "\n";
};
int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
};  // namespace dp

namespace observation {

// 1: 1 + 0, 0 + 1: 2
// 2: 0 + 2, 1 + 1, 2 + 0: 3
// 3: 0 + 3, 1 + 2, 2 + 1, 3 + 0: 4
// 4: 0 + 4, 1 + 3, 2 + 2, 3 + 1, 4 + 0: 5
int nsplits_zero(int n) { return n + 1; }

// 3: 1 + 2, 2 + 1
// 4: 1 + 3, 2 + 2, 3 + 1
int nsplits_nonzero(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 1;
    }
    return n - 1;
}

// void add(string a, string b) {
//   map<int, int> carries;
//   vector<char> digits;
//   int maxlen = max<int>(a.size(), b.size());
//   for(int ix = 0; ix < maxlen; ix++) {
//     int cur = 0;
//     if (ix < a.size()) { cur += a[a.size() - 1 - ix] - '0';}
//     if (ix < b.size()) { cur += b[b.size() - 1 - ix] - '0';}
//     cur += carries[ix];
//     if (cur > 10) {
//       int carry = cur % 10;
//       int digit = cur / 10;
//       carries[ix+2] += carry;
//       digits.push_back(digit + '0');
//     }
//   }
// }

void solve() {
    string s;
    cin >> s;
    int place = 1;
    int fst = 0;  // picks up ones place digit.
    for (int i = s.size() - 1; i >= 0; i -= 2) {
        fst = fst + (s[i] - '0') * place;
        place *= 10;
    }
    place = 1;
    int snd = 0;  // picks up tens place digit.
    for (int i = s.size() - 2; i >= 0; i -= 2) {
        snd = snd + (s[i] - '0') * place;
        place *= 10;
    }
    int ans = nsplits_zero(fst) * nsplits_zero(snd) - 2;
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}
}  // namespace observation

int main() { dp::main(); }
