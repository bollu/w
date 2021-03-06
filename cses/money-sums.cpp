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

static const int MAXNUMCOINS = 100 + 5;
static const int MAXCOINVAL = 1000 + 5;


// find total possible types of money
void dpf(int cix, set<int> &ms, const vector<pair<int, int>> &coins) {
    if (cix == 0) {
        ms.insert(coins[0].first);
    } else {
        // insert all previous;
        dpf(cix - 1, ms, coins);
        set<int> curms;
        curms.insert(coins[cix].first);
        // create all new types of monies
        for (int m : ms) {
            curms.insert(m + coins[cix].first);
        }
        ms.insert(curms.begin(), curms.end());
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<pair<int, int>> coins(n);
    for (int i = 0; i < n; ++i) {
        cin >> coins[i].first;
        coins[i].second = i;

    }

    set<int> ms;
     dpf(n - 1, ms, coins);
    // dpf(0, ms, coins);
    cout << ms.size() << "\n";
    for (int m : ms) {
        cout << m << " ";
    }
    cout << "\n";

    return 0;
}
