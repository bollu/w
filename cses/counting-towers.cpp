#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <bitset> // instead of bool[N];
#include <stdlib.h> // for exit()

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template<typename T>
using minqueue = priority_queue<T,vector<T>,greater<T>>;

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

// Be very clear on what you are counting! I'm counting *number of towers* with the given configuration.
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    static const int N = 1e6 + 10;
    static const int MOD = 1e9 + 7;
    int dp[N][2]; // dp[i][unlinked: # of towers in height [1, i].
    // dp[_][true]: two 1x1 tiles.
    // dp[_][false]: one 2x1 tile

    dp[1][false] = 1;
    dp[1][true] = 1;

    for(int i = 2; i < N; ++i) {
        dp[i][false] = dp[i][true] = 0;
        // -- 2x1 --
        // --previous 1x1--
        // (a) close both previous 1x1s, create new 2x1
        // |   | 
        // |-+-|
        // | | |
        // dp[i][false] = (dp[i][false] + dp[i-1][true] + 1) % MOD;
        dp[i][false] = (dp[i][false] + dp[i-1][true]) % MOD;
        // --previous 2x1--
        // (a) extend previous 2x1
        // |   |
        // |   |
        // |   |
        dp[i][false] = (dp[i][false]+ dp[i-1][false]) % MOD;
        // (b) close previous 2x1, add new 2x1
        // |   |
        // +---+
        // |   |
        // dp[i][false] = (dp[i][false] + dp[i-1][false] + 1) % MOD;
        dp[i][false] = (dp[i][false] + dp[i-1][false]) % MOD;


        // -- two 1x1 --
        // --previous 1x1--
        // (a) extend left 1x1, close right 1x1
        // | | |
        // | +-|
        // | | |
        dp[i][true] = (dp[i][true]+ dp[i-1][true]) % MOD;
        // (b) close left 1x1, extend right 1x1
        // | | |
        // |-+ |
        // | | |
        dp[i][true] = (dp[i][true]+ dp[i-1][true]) % MOD;
        // (c) extend both 1x1s.
        // | | |
        // | | |
        // | | |
        dp[i][true] = (dp[i][true]+ dp[i-1][true]) % MOD;
        // (d) close both 1x1s.
        // |1|1|
        // |-+-|
        // | | |
        // NO +2! I'm counting TOWERS, not BLOCKS.
        // dp[i][true] = (dp[i][true]+ dp[i-1][true] + 2) % MOD;
        dp[i][true] = (dp[i][true]+ dp[i-1][true]) % MOD;
        // --previous 2x1--
        // (d) close previous 2x1, open two new 2x1
        // | | |
        // |-+-|
        // |   |
        dp[i][true] = (dp[i][true] + dp[i-1][false]) % MOD;
    }

    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        cout << (dp[n][true] + dp[n][false]) % MOD << "\n";
    }

    return 0;
}

