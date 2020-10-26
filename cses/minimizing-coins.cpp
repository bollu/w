#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <numeric> // for gcd
#include <assert.h>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>


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

template<typename T1, typename T2>
ostream &operator <<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}


static const int MOD = 1e9 + 7;
static const int MAXX = 1e6 + 5;
static const int INFTY = 1e9;

int dp[MAXX];
int main() { 
    int n, x; cin >> n >> x;
    vector<int> cs(n);
    for(int i = 0; i < n; ++i) { cin >> cs[i]; }

    for(int i = 1; i <= x; ++i) {
        int mincount = INFTY;
        for(int c : cs) {
            if (c == i) { mincount = 1; break; }
            if (i - c < 0) { continue; }
            if (dp[i-c] == -1) { continue; }
            mincount = min<int>(mincount, (1 + dp[i - c]) % MOD);
        }
        dp[i] = mincount == INFTY ? -1 : mincount;
        // cerr << i << ":" << dp[i] << "\n";
    }
    cout << dp[x] << "\n";
    return 0;
}
