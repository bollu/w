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

static const int N = 1e3 + 5;
static const int INFTY = 1e9;
static const int MOD = 1e9 + 7;
bool movable[N][N];
ll npaths[N][N];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < n; ++x) {
            char c;
            cin >> c;
            movable[x][y] = (c == '.');
        }
    }

    for (int x = n; x >= 0; x--) {
        for (int y = n; y >= 0; y--) {
            if (!movable[x][y]) { continue; }

            if (x == n - 1 && y == n - 1) {
                npaths[x][y] = 1;
            }

            if (y + 1 < n && movable[x][y+1]) {
                npaths[x][y] += npaths[x][y + 1];
                npaths[x][y] %= MOD;
            }
            if (x + 1 < n && movable[x+1][y]) {
                npaths[x][y] += npaths[x + 1][y];
                npaths[x][y] %= MOD;
            }
        }
    }

    cout << npaths[0][0] << "\n";
    return 0;
}
