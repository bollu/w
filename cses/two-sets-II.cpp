#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <vector>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

template <typename T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename K, typename V>
using ordered_map =
    __gnu_pbds::tree<K, V, less<K>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename T1, typename T2>
ostream &operator<<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}

// s1 + s2 = n(n+1)/2
// if s1 = s2
// 2 s2 = n(n+1)/2
// s2 = n(n+1)/4
// Find all subsets of [1,2...n] that sum up of n(n+1)/4

// 500 * (500 + 1)/4 ~ 1e5 + 10

static const ll MOD = 1e9 + 7;
static const int NMAX = 500 + 10;

// top down DP; too slow
namespace f0 {

map<pair<int, int>, ll> dpm;

// will loop upto maxnum
// returns number of ways to pick numbers [curnum..maxnum] to get goalval
ll dp(int curnum, const int maxnum, int cursum, const int goal) {
    auto it = dpm.find({curnum, cursum});
    if (it != dpm.end()) {
        return it->second;
    }
    if (curnum > maxnum) {
        return 0;
    }
    if (cursum == goal) {
        return 1;
    }
    if (cursum > goal) {
        return 0;
    }

    ll out = (dp(curnum + 1, maxnum, cursum + curnum, goal) +
              dp(curnum + 1, maxnum, cursum, goal)) %
             MOD;
    dpm.insert({{curnum, cursum}, out});
    return out;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;

    if (n * (n + 1) % 4 != 0) {
        cout << 0 << "\n";
        return 0;
    }
    ll goal = dp(1, n, 0, (n * (n + 1)) / 4);
    cout << goal << "\n";
    return 0;
}

}  // namespace f0

namespace f1 {
static const ll MOD = 1e9 + 7;
static const int NMAX = 500 + 10;
static const int SUMMAX = NMAX * (NMAX + 1) + 10;
ll dp[NMAX][SUMMAX];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll N;
    cin >> N;

    if (N * (N + 1) % 4 != 0) {
        cout << 0 << "\n";
        return 0;
    }

    const ll goal = (N * (N + 1)) / 4;

    // dp[n][sum]: # of ways to get to sum using [1..n]
    dp[0][0] = 1;
    for(ll n = 1; n <= N; ++n) {
        for(ll sum = 0; sum <= goal; ++sum) {
            if (sum - n < 0) { 
                dp[n][sum] = dp[n-1][sum];
            }
            else { 
                dp[n][sum] = (dp[n-1][sum] + dp[n-1][sum-n]) % MOD; 
            }
        }
    }

    // why N-1? I don't understand the symmetry breaking argument.
    cout << dp[N-1][goal-N] << "\n";
    return 0;
}
}  // namespace f1

int main() { return f1::main(); }
