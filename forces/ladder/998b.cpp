// 1200
#include <iostream>
#include <vector>
#include <assert.h>
#include <utility>

using namespace std;

static const int INF = 1e9;
int N; int B;
// 1 indexed.
int as[101];
// nodd[i] = # of odd numbers in range [0..i) (exclusive)
int nodds[101], nevens[101];

// check if segment [l..r] is inclusive
// l, r ∈ [1, N]
bool legalsegment(int l, int r) {
    assert(r-l+1 >= 1); 
    // int o = 0;
    // int e = 0;
    // for(int i = l; i <= r; ++i) {
    //     if (as[i] %2 == 0) { e += 1; } else { o += 1; }
    // }
    int o = nodds[r+1] - nodds[l];
    int e = nevens[r+1] - nevens[l];
    return o == e;
}

int main() {
    cin >> N >> B;
    int o = 0, e = 0;
    for(int i = 0; i < N; ++i) { 
        cin >> as[i];
        o += as[i] % 2 == 1;
        e += as[i] % 2 == 0;
        nodds[i+1] = o;
        nevens[i+1] = e;
    }
    // lemma: dp[ix][b]: best # of cuts by having cuts upto index `ix` using `b` bitcoins
    // cout << solve(N, B);
    int dp[101][101]; // dp[ix][b]: best # of cuts in range [1..ix] using `b` bitcoins.
    for (int i = 0; i < 101; ++i) {
        for(int j = 0; j < 101; ++j) { 
            dp[i][j] = 0;
        }
    }

    for(int i = 0; i < N; ++i) {
        dp[i][0] = i > 0 ? dp[i-1][0] : 0;
        for(int b = 1; b <= B; ++b) {
            // split points
            // [0..s-1];[s..i]
            dp[i][b] = dp[i][b-1];
            for(int s = 1; s <= i-1; s++) {
                int cost = abs(as[s-1] - as[s]);
                int bleft = b - cost; if (bleft < 0) { continue; }
                if (!legalsegment(0, s-1)) { continue; }
                if (!legalsegment(s, N-1)) { continue; }
                dp[i][b] = max(dp[i][b], dp[s][bleft] + 1);
            }
        }
    }

    // for (int i = 0; i < N ; ++i) {
    //     for(int j = 0; j < B; ++j) { 
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    cout << dp[N-1][B] << "\n";

}
