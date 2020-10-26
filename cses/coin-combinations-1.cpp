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

static const int MOD = 1e9 + 7;
static const int MAXX = 1e6 + 10;

// top down DP with unordered_map for cache: TLE
namespace f0 {
unordered_map<int, int> dp;

int ncombs(int i, const vector<int> &cs) {
    if (i <= 0) {
        return 0;
    }
    auto it = dp.find(i);
    if (it != dp.end()) {
        return it->second;
    }
    int total = 0;

    for (int c : cs) {
        // m for multiplier
        if (i == c) {
            total += 1;
        }
        total = (total + ncombs(i - c, cs)) % MOD;
    }
    dp[i] = total;
    return total;
}

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> cs(n);
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
    }
    cout << ncombs(x, cs) << "\n";
    return 0;
}

}  // namespace f0

// standard bottom up DP
namespace f1 {

int dp[MAXX];

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> cs(n);
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
    }

    dp[0] = 0;
    for (int i = 1; i <= x; ++i) {
        for (int c : cs) {
            if (i - c < 0) {
                continue;
            }
            if (i == c) {
                dp[i] += 1;
            }
            dp[i] = (dp[i] + dp[i - c]) % MOD;
        }
    }
    cout << dp[x] << "\n";
    return 0;
}
}  // namespace f1

// top down DP with bool + int arrays for cache. TLEs
namespace f2 {
int dp[MAXX];
bool dpd[MAXX];  // check if have dp'd an index

int ncombs(int i, const vector<int> &cs) {
    if (i <= 0) {
        return 0;
    }
    if (dpd[i]) {
        return dp[i];
    }
    int total = 0;

    for (int c : cs) {
        // m for multiplier
        if (i == c) {
            total += 1;
        }
        total = (total + ncombs(i - c, cs)) % MOD;
    }
    dp[i] = total;
    return total;
}

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> cs(n);
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
    }
    cout << ncombs(x, cs) << "\n";
    return 0;
}

}  // namespace f2


// program from F2 with obvious recursions eliminiated. Still TLEs.
// clearly bottom up DP is the way to go.
namespace f3 {
int dp[MAXX];
bool dpd[MAXX];  // check if have dp'd an index

int ncombs(const int i, const vector<int> &cs) {
    int total = 0;
    for (int c : cs) {
        // m for multiplier
        if (i - c < 0) {
            continue;
        }
        if (i == c) {
            total += 1;
        }
        if (dpd[i - c]) {
            total = (total + dp[i - c]) % MOD;
        } else {
            total = (total + ncombs(i - c, cs)) % MOD;
        }
    }
    dp[i] = total;
    return total;
}

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> cs(n);
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
    }
    cout << ncombs(x, cs) << "\n";
    return 0;
}

}  // namespace f3

int main() { return f3::main(); }

