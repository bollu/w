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


static const int INFTY = 1e9;
static const int MAX = 500;
bool dpd[MAX][MAX];
int dp[MAX][MAX];

// w <= h, always
int mksq(int w, int h) {
    // cerr << "mksq" << w << " " << h << "\n";
    if (w == h) { return 0; }
    if (w > h) { std::swap<int>(w, h); }

    if (dpd[w][h]) { return dp[w][h]; }
    // split on larger dimension (h)
    int best = INFTY;
    for(int i = 1; i < h; ++i) {
        best = min<int>(best, 1 + mksq(w, i) + mksq(w, h-i));
    }

    for(int i = 1; i < w; ++i) {
        best = min<int>(best, 1 + mksq(i, h) + mksq(w - i, h));
    }
    dpd[w][h] = true;
    dp[w][h] = best;
    return best;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int a, b; cin >> a >> b;
    cout << mksq(a, b) << "\n";
    return 0;
}

