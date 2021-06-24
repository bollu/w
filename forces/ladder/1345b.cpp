#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// find ix such that dp[ix] <= sz and dp[ix+1] > sz.
// TODO: think about correctness.
int tallest(vector<long> &dp, int sz) {
    int l = 0, r = dp.size(); 
    // [l, r)
    while(1) {
        if (l + 1 == r ) { return l; }
        // r > (l+1) so, , m := (l+r/2) > (2l+1)/2 > l.
        // so l = m will decrease interval size.
        int m = (l+r)/2;
        if (dp[m] > sz) {
            r = m; // will decrease because floor division.
        } else { 
            l = m; // 
        }
    }
}
int main() {
    vector<long> dp;
    dp.push_back(0);
    dp.push_back(2); // dp[0] = 0, dp[1] = 2.
    for(int h = 2;; h++) {
        long ncards =  dp[1]*h + (h-1) + dp[h-1];
        dp.push_back(ncards);
        if (ncards > 1e9 + 5) { break; }
    }

    // for(int i = 0; i < 10; ++i) { cout << i << " → " << dp[i] << "\n"; }

    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int out = 0;
        while(1) {
            int ix = tallest(dp, n);
            if (ix == 0) { break; }
            out += 1;
            n -= dp[ix];

        }
        cout << out << "\n";
        // while(sum <= n) {
        //     if (sum + dp[ht] > n) { break; }
        //     sum += dp[ht]; ht++;
        // }
        // cout << ht -1 << "\n";
    }

    return 0;
}

