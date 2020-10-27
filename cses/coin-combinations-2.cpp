#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
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

// naive. TLE.
namespace f0 {
static const int MOD = 1e9 + 7;
static const int XMAX = 1e6 + 5;
static const int NCOINMAX = 100 + 5;
int dp[XMAX][NCOINMAX];
int cs[NCOINMAX];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
    }
    std::sort(cs, cs + n);

    // m for money
    for (int m = 1; m <= x; m++) {
        for (int i = 0; i <= n; ++i) {
            const int c = cs[i];
            if (m == c) {
                dp[m][i] = (1 + dp[m][i]) % MOD;
            }
            if (m - c < 0) {
                break;
            }  // coins after this are too large
            // equal or higher valued coins
            for (int j = i; j <= n; j++) {
                dp[m][i] = (dp[m][i] + dp[m - c][j]) % MOD;
            }
            // cout << "dp[" << m <<"][" << i << ":" << c << "] = " << dp[m][i]
            // << "\n";
        }
    }

    int tot = 0;
    for (int i = 0; i < n; ++i) {
        tot = (tot + dp[x][i]) % MOD;
    }
    cout << tot << "\n";
    return 0;
}
}  // namespace f0

// Be more canny in picking DP space. Still TLE.
// dp[m][i]: number of ways to break money `m` into coins of ix >= i
namespace f1 {
static const int MOD = 1e9 + 7;
static const int XMAX = 1e6 + 5;
static const int NCOINMAX = 100 + 5;
int dp[XMAX][NCOINMAX];
int cs[NCOINMAX];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
    }
    std::sort(cs, cs + n);

    // m for money
    // dp[m][i]: number of ways to break money `m` into coins of ix >= i
    for (int m = 1; m <= x; m++) {
        for (int i = n - 1; i >= 0; i--) {
            if (i < n - 1) {
                dp[m][i] = dp[m][i + 1];
            }
            const int c = cs[i];
            if (m == c) {
                dp[m][i] = (dp[m][i] + 1) % MOD;
                continue;
            }
            if (m - c < 0) {
                continue;
            }  // coins after this are too large

            dp[m][i] = (dp[m][i] + dp[m - c][i]) % MOD;
        }
    }

    cout << dp[x][0] << "\n";
    return 0;
}
}  // namespace f1

// Switch orderof loops: first loop over all coins, then on `m`.
namespace f2 {
static const int MOD = 1e9 + 7;
static const int XMAX = 1e6 + 5;
static const int NCOINMAX = 100 + 5;
int dp[XMAX];
int cs[NCOINMAX];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
    }
    std::sort(cs, cs + n);

    // m for money
    // dp[m][i]: number of ways to break money `m` into coins of ix >= i
    for (int i = n - 1; i >= 0; i--) {
        const int c = cs[i];
        for (int m = 0; m <= x; m++) {
            if (m - c < 0) { continue; }
            if (m == c) { dp[m] = (dp[m] + 1) % MOD; continue; }
            dp[m] = (dp[m] + dp[m - c]) % MOD;
        }
    }

    cout << dp[x] << "\n";
    return 0;
}
}  // namespace f2

int main() { return f2::main(); }
