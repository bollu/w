#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;
#define lli long long int
#define llu unsigned long long int
#define fr(va, beg, end) for (lli va = beg; va < end; va++)
#define pb push_back
#define rt return 0
#define endln "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (lli)(x.size())
const lli MOD = 1e9 + 7;
// cout << fixed << setprecision(0) << pi <<endl;
// typedef tree<int, null_type, less<int>, rb_tree_tag,
//              tree_order_statistics_node_update>
//     new_data_set;
// for multiset
// typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
//              tree_order_statistics_node_update>
//     new_data_set;
// order_of_key(val): returns the number of values less than val
// find_by_order(k): returns an iterator to the kth largest element (0-based)

void solve() {
    lli n, a;
    cin >> n;
    vector<lli> v;
    for (lli i = 0; i < n; i++) {
        cin >> a;
        v.pb(a);
    }

    if (n == 1) {
        cout << "0" << endl;
        return;
    }

    lli val = n / 2;
    if (n % 2 == 1) {
        val++;
    }

    lli inf = 1e15;
    vector<vector<array<lli, 2>>> dp(
        n + 2, vector<array<lli, 2>>(val + 2, array<lli, 2>({inf, inf})));

    dp[0][0][0] = 0;
    if (v[1] >= v[0]) {
        dp[0][1][1] = v[1] - v[0] + 1;
    } else {
        dp[0][1][1] = 0;
    }

    for (lli i = 1; i < n; i++) {
        dp[i][0][0] = 0;
        for (lli j = 1; j <= val; j++) {
            // if this is not
            dp[i][j][0] = min(dp[i - 1][j][0], dp[i - 1][j][1]);

            // if this is
            if (i >= 2) {
                lli p = dp[i - 2][j - 1][1];
                lli pp = min(v[i - 1], v[i - 2] - 1);
                p += max(0ll, pp - v[i] + 1);

                lli q = dp[i - 2][j - 1][0] + max(0ll, v[i - 1] - v[i] + 1);
                if (i != n - 1) {
                    q += max(0ll, v[i + 1] - v[i] + 1);
                    p += max(0ll, v[i + 1] - v[i] + 1);
                }
                dp[i][j][1] = min(p, q);
            } else {
                if (j == 1) {
                    dp[i][1][1] = max(0ll, v[i - 1] - v[i] + 1);
                    if (i != n - 1) {
                        dp[i][1][1] += max(0ll, v[i + 1] - v[i] + 1);
                    }
                }
            }
        }
    }

    for (lli i = 1; i <= val; i++) {
        cout << min(dp[n - 1][i][1], dp[n - 1][i][0]) << " ";
    }
    cout << endln;
}

int main(void) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    // lli t; cin >> t; while(t--)
    solve();
    rt;
}
