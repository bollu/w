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

static const int MAXN= 1e6 + 5;
static const int INFTY= 1e9 + 5;
int dp[MAXN];
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;

    dp[0] = 0;
    for(int i = 1; i <= n; ++i) {
        int cur = i;
        dp[i] = INFTY;
        while (cur != 0) {
            const int digit = cur % 10;
            dp[i] = std::min(dp[i], 1 + dp[i - digit]);
            cur = cur / 10;
        }
    }

    cout << dp[n] << "\n";

    return 0;
}
