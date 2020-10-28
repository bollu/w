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
namespace f0 {};

// greedy, just wrong
namespace f0 {
static const int MAXXS = 1e5 + 5;
static const int MAXM = 100;
int xs[MAXXS];
int dp[MAXXS][MAXM];
int n, m;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
    }

    int lval = 1;
    int i = 0;
    int prod = 1;
    while (i < n) {
        if (xs[i] != 0) {
            lval = xs[i];
            i++;
            continue;
        }
        // we have a 0. find right.
        int j = i;
        while (xs[j] == 0 && j < n) {
            j++;
        }
        int rval = j == n ? m : xs[j];

        prod *= ((rval + 1) - (lval - 1) + 1);
        i = j;
    }
    cout << prod << "\n";
    return 0;
}
}  // namespace f0

// naive DP that adds up states.
namespace f1 {
static const int MAXXS = 1e5 + 5;
static const int MAXM = 100 + 5;
static const int MOD = 1e9 + 7;
ll xs[MAXXS];
ll dp[MAXXS][MAXM];
ll n, m;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) {
        cin >> xs[i];
    }

    {
        const ll vcur = xs[1];
        if (vcur != 0) {
            dp[1][vcur] = 1;
        } else {
            for (ll v = 1; v <= m; ++v) {
                dp[1][v] = 1;
            }
        }
    }

    for (ll ix = 2; ix <= n; ++ix) {
        const ll vcur = xs[ix];
        if (vcur != 0) {
            dp[ix][vcur] = (dp[ix][vcur] + dp[ix - 1][vcur - 1]) % MOD;
            dp[ix][vcur] = (dp[ix][vcur] + dp[ix - 1][vcur]) % MOD;
            dp[ix][vcur] = (dp[ix][vcur] + dp[ix - 1][vcur + 1]) % MOD;
        } else {
            // we can allow all possibilities
            for (ll v = 1; v <= m; ++v) {
                dp[ix][v] = (dp[ix][v] + dp[ix - 1][v - 1]) % MOD;
                dp[ix][v] = (dp[ix][v] + dp[ix - 1][v]) % MOD;
                dp[ix][v] = (dp[ix][v] + dp[ix - 1][v + 1]) % MOD;
            }
        }
    }

    ll tot = 0;
    if (xs[n] == 0) {
        for (ll v = 1; v <= m; ++v) {
            tot = (tot + dp[n][v]) % MOD;
        }
    } else {
        tot = dp[n][xs[n]];
    }
    cout << tot << "\n";

    return 0;
}
}  // namespace f1

// top down DP for ease of use.
// don't have enough stack frames on large examples.
namespace f2 {
static const int MAXXS = 1e5 + 5;
static const int MAXM = 100 + 5;
ll xs[MAXXS];
ll n, m;

bool dpd[MAXXS][MAXM];
ll dp[MAXXS][MAXM];

// number of ways to get value `v` at index `ix`
ll nways(ll ix, ll v) {
    if (dpd[ix][v]) { return dp[ix][v]; }
    // static ll depth = 0;
    // depth++;
    // cerr << "\n"; for(ll i = 0; i < depth; ++i) { cerr << " "; }
    // cerr << "nways " << ix << " " << v;
    ll tot = 0;
    if (ix == 0) {
        if (xs[0] == 0) {
            tot =  (v >= 1 && v <= m) ? 1 : 0;
        } else {
            tot = (v == xs[ix] ? 1 : 0);
        }
    } else {
        if (xs[ix] == 0) {
            tot += v == 1 ? 0 : nways(ix-1, v-1);
            tot += nways(ix-1, v);
            tot += v == m ? 0 : nways(ix-1, v+1);
        } else {
            if (xs[ix] != v) { tot  = 0; }
            else {
                tot += xs[ix] == 1 ? 0 : nways(ix-1, xs[ix]-1);
                tot += nways(ix-1, xs[ix]);
                tot += xs[ix] == m ? 0 : nways(ix-1, xs[ix]+1);
            }
        }
    }
    dp[ix][v] = tot;
    dpd[ix][v] = true;
    // cerr << "\n"; for(ll i = 0; i < depth; ++i) { cerr << " "; }
    // cerr << "nways " << ix << " " << v << " = " << tot << "\n";
    // depth--;
    return tot;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
    }

    ll tot = 0;
    if (xs[n - 1] == 0) {
        for (int i = 1; i <= m; ++i) {
            tot += nways(n - 1, i);
        }
    } else {
        tot = nways(n - 1, xs[n - 1]);
    }
    cout << tot << "\n";

    return 0;
}
}  // namespace f2

int main() { f1::main(); }
