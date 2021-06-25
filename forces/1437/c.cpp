#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <utility>
#include <map>
using namespace std;


// sort dishes in non-decreasing order of optimal time.
// claim: if t[i] < t[j] then in optimal soln. f[i] < f[j] 
//  (where t[i] is ideal time for dish i, and [f: dishix -> time] is injective fn which assigns dish to outgoing time.)
// proof: suppose for contradiction O* is optimal, such that t[i] < t[j] and f[i] > f[j]. 
// Let t[j] = t[i] + δ, f[i] = f[j] + ε.  (δ, ε > 0)
// cost(O*) = |t[i] - f[i]| + |t[j] - f[j]|
//          = |t[i] - (f[j] + ε)| + |(t[i] + δ) - f[j]|
//          = |(t[i] - f[j]) - ε| + |(t[i] - f[j]) + δ|
//          [let x = t[i] - f[j]]
//          = |x - ε| + |x + δ|
//          ≥ |x - ε + x + δ|
//          ≥ |2x + (δ + ε)|
//
// swap f[i] <-> f[j]:
// cost(O') = |t[i] - f[j]| + |t[j] - f[i]|
//         = |t[i] - f[j]| + |t[i] + δ - f[j] - ε|
//         = |x| + |x + (δ - ε)|
//         [|a+b| ≤ |a| + |b|]
//         ≥ |2x + (δ - ε)|
//
// since δ, ε > 0, we have
// cost(O*) ≥ |2x + (δ + ε)| ≥ |2x + (δ - ε)| 
// TODO: how to bound?
//
//
// Now that we know this, optimal must be in non-decreasing order.
//
// dp[i][T]: min. total cost if UPTO i dishes are processed and current time is T. [i is NOT processed]
//   either we put current dish at T, or we wait.

const int INF = 1e9;

int mainpush() {
    int q; cin >> q;
    while(q--) {
        int n; cin >> n;

        // time t[i].
        vector<int> ts(n);
        for(int i = 0; i < n; ++i) { cin >> ts[i]; ts[i]--; }

        sort(ts.begin(), ts.end());
        vector<vector<int>> dp(n+1, vector<int>(2 * n+1, INF));
        dp[0][0] = 0;
        // push-style dp.
        for(int i = 0; i < n+1; ++i) {
            for(int t = 0; t < 2*n; ++t) {
                // this slot does not know its value, skip.
                if (dp[i][t] == INF) { continue; }
                // process dish i.
                if (i + 1 < n + 1) { dp[i + 1][t + 1] = min(dp[i + 1][t + 1], dp[i][t] + abs(ts[i] - t)); }
                dp[i][t + 1] = min(dp[i][t + 1], dp[i][t]);
            }
        }
        
        cout << dp[n][2 * n] << "\n";


    }
    return 0;
}

// min. cost of processing upto [0..i] dishes in time [0..t]
int mincost(vector<int> &ts, int i, int t, map<pair<int, int>, int> &dp) {
    if (dp.count(make_pair(i, t))) { return dp[make_pair(i, t)]; }
    if (i < 0) { return 0; } // nothing to do!

    // try all placements.
    int out = INF; 
    for(int t2 = 0; t2 <= t; ++t2) {
        out = min(out, mincost(ts, i-1, t2-1, dp) + abs(ts[i] - t2));
    }
    return dp[make_pair(i, t)] = out;
};

int mainpull() {
    int q; cin >> q;
    while(q--) {
        int n; cin >> n;
        vector<int> ts(n);
        for(int i = 0; i < n; ++i) { cin >> ts[i]; ts[i]--; }
        sort(ts.begin(), ts.end());
        map<pair<int, int>, int> dp;
        cout << mincost(ts, n-1, 2*n, dp) << "\n"; // dp[n-1][2 * n] << "\n";
    }
    return 0;
}

int main() { return mainpull(); }
