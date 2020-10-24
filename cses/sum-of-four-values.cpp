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
// TLE but correct
namespace f0 {
int main() {
    int n, x;
    cin >> n >> x;
    vector<int> as(n);
    for (int i = 0; i < n; ++i) {
        cin >> as[i];
    }
    unordered_map<int, pair<int, int>> v2ixs;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = as[i] + as[j];
            if (sum > x) {
                break;
            }
            v2ixs[sum] = {i, j};
        }
    }

    for (auto it : v2ixs) {
        const int i = it.second.first, j = it.second.second;
        auto it2 = v2ixs.find(x - it.first);
        if (it2 == v2ixs.end()) {
            continue;
        }

        const int k = it2->second.first, l = it2->second.second;
        if ((k != i && k != j) && (l != i && l != j)) {
            cout << 1 + i << " " << 1 + j << " " << 1 + k << " " << 1 + l << "\n";
            return 0;
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
}

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> as(n);
    for (int i = 0; i < n; ++i) { cin >> as[i]; }

    std::sort(as.begin(), as.end());

    // there maybe more than one way to get the same indexes.
    unordered_map<int, set<pair<int, int>>> v2ixs;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int sum = as[i] + as[j];
            if (sum > x) { break; }

            auto it2 = v2ixs.find(x - sum);
            if (it2 != v2ixs.end()) {
                int k, l;
                // tie(k, l) = it2->second;
                if ((k != i && k != j) && (l != i && l != j)) {
                    cout << 1 + i << " " << 1 + j << " " << 1 + k << " " << 1 + l << "\n";
                    return 0;
                }
            }

            v2ixs[sum] = {i, j};
        }
    }

    /*
    for (auto it : v2ixs) {
        const int i = it.second.first, j = it.second.second;
        auto it2 = v2ixs.find(x - it.first);
        if (it2 == v2ixs.end()) {
            continue;
        }

        const int k = it2->second.first, l = it2->second.second;
        if ((k != i && k != j) && (l != i && l != j)) {
            return 0;
        }
    }
    */

    cout << "IMPOSSIBLE\n";
    return 0;
}
