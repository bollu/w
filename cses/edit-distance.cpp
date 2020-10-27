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

static const int INFTY = (1e9 + 42);
static const int NMAX = 5000 + 5;
bool dpd[NMAX][NMAX];
int dp[NMAX][NMAX];

int edit(string &s, string &t, int i, int j) {
    if (dpd[i][j]) { return dp[i][j]; }

    int ans = INFTY;
    // delete everything in t to match s=""
    if (i == s.size()) { return t.size() - j; }
    // insert everything in s to t="" to match s
    if (j == t.size()) { return s.size() - i; }

    // 1 to insert the letter at position `i`
    ans = min<int>(ans, 1 + edit(s, t, i+1, j));
    // 1 to delete the letter at position `j`
    ans = min<int>(ans, 1 + edit(s, t, i, j+1));

    // edit 'i' to 'j'
    ans = min<int>(ans, (s[i] == t[j] ? 0 : 1)  +  edit(s, t, i+1, j+1));
    dpd[i][j] = true;
    dp[i][j] = ans;


    // cout << "edit '" << s.substr(i) << "' '" << t.substr(j) << "' = " << ans << "\n";
    return ans;
}

int main() {
    std::string s, t;

    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s >> t;

    const int n = s.size(), m = t.size();

    cout << edit(s, t, 0, 0) << "\n";
    return 0;
}

