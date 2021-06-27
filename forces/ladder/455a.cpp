#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

// key idea: see that the constraints:
//   cancel k-1, k+1
// are redundant. For example, if `l = k+1`, 
//   choosing `k` and then barring ourselves from choosing `k+1`
//   is the same as choosing `k+1` and then barring ourselves from choosing `(k+1)-1=k`.
// So if we process these in sorted order, we only need to check the cancel `k-1`
// condition.
//
// we DP on choosing or not choosing k.
//
// I had to do annoying iterator management. Is there a clear way to implement this?
using ll = long long;
int main2() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    vector<ll> as(n);
    map<ll, ll> counts;
    for(ll i = 0; i < n; ++i) { 
        cin >> as[i];
        counts[as[i]]++;
    }

    map<ll, ll> dp;
    ll kk = -42, kkk = -42;
    for(auto it = counts.begin(); it != counts.end(); ++it) {
        const ll k = it->first; const ll n = it->second;
        // take kkk
        if (k-1 == kk) { 
            dp[k] = std::max(dp[kk], dp[kkk] + k*n);
        } else {
            // take kk
            dp[k] = dp[kk] + k*n;
        }

        // cout << "k:" << k << "  kk:" << kk << "   kkk:" <<  kkk << " n:" <<
        // n << " dp[k]:" << dp[k] << "  dp[kk]:" << dp[kk] << "  dp[kkk]:" <<
        // dp[kkk] << "\n";
        kkk = kk;
        kk = k;
    }
    cout << dp.rbegin()->second << "\n";

    return 0;
}


// use 2D dp.
int main() {
    ios::sync_with_stdio(false);
    int n; cin >> n;
    static const int MAXN = 1e5 + 5;
    static const int MAXA = 1e5 + 5;

    map<ll, ll> counts;
    for(ll i = 0; i < n; ++i) { 
        int x; cin >> x; counts[x]++;
    }
    // dp[i][0]: max value possible using numbers [0..i] without choosing number (i)
    // dp[i][1]: max value possible using numbers [0..i] *with* choosing number (i)
    ll dp[MAXN+10][2];
    // 0 neveroccurs
    dp[0][0] = dp[0][1] = 0;

    // we are iterating on *N* itself [the numbers themselves, NOT the array elements!]
    for(int i = 1; i <= MAXN; ++i) {
        // if we don't pick `i`, then we can both pick and not-pick [i-1].
        dp[i][0] = max(dp[i-1][0], dp[i-1][1]);
        // if we pick i, then we can't pick `i-1`.
        dp[i][1] = dp[i-1][0] + i*counts[i];
    }
    ll best = max(dp[MAXN][0], dp[MAXN][1]);
    cout << best << "\n";

    return 0;
}

