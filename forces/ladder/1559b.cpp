#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;


int n; std::string s;
const int N = 101;
int dp[N][2];

const int INFTY = 10000;

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        cin >> n; cin >> s;
        // ?B .. -> RB ..
        // ?R.. -> BR ..
        // first index does not add to imperfectness.
        // whenever you do DP, add a dummy index to think about the empty problem.
        // `x(`
        const int R = 0; const int B = 1; 
        if (s[0] == 'R') {
            dp[0][R] = 0; dp[0][B] = INFTY; 
        } else if (s[0] == 'B') {
            dp[0][B] = 0; dp[0][R] = INFTY;
        } else {
            dp[0][B] = dp[0][R] = 0;
        }

        for(int i = 1; i < n; ++i) {
            if (s[i] == '?') {
                dp[i][R] = min<int>(dp[i-1][R] + 1, dp[i-1][B]);
                dp[i][B] = min<int>(dp[i-1][B] + 1, dp[i-1][R]);
            } else if (s[i] == 'R') {
                dp[i][R] = min<int>(dp[i-1][R]+1, dp[i-1][B]);
                dp[i][B] = INFTY;
            } else if (s[i] == 'B') {
                dp[i][R] = INFTY;
                dp[i][B] = min<int>(dp[i-1][B]+1, dp[i-1][R]);
            }
        }
        std::string out = s; 
        int c = dp[n-1][R] < dp[n-1][B] ? R : B;
        for(int i = n-1; i >= 0; i--) {
            out[i] = c == R ? 'R' : 'B';
            if (i == 0) { break; }
            if (c == R) {
                c = dp[i-1][R] + 1 < dp[i-1][B] + 1 ? R : B;
            } else if (c == B) {
                c = dp[i-1][R] < dp[i-1][B] + 1 ? R : B;
            }
        }
        cout << out << "\n";;
    }

    return 0;
}