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
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, x;
    cin >> n >> x;
    vector<pair<int, int>> as(n);
    for (int i = 0; i < n; ++i) {
        cin >> as[i].first;
        as[i].second = i;
    }

    std::sort(as.begin(), as.end());
    for (int i = 0; i < n; ++i) {
        if (as[i].first > x) {
            break;
        }
        for (int j = i + 1; j < n; ++j) {
            if (as[i].first + as[j].first > x) {
                break;
            }
            for (int k = j + 1; k < n; ++k) {
                if (as[i].first + as[j].first + as[k].first > x) {
                    break;
                }
                for (int l = k + 1; l < n; ++l) {
                    if (as[i].first + as[j].first + as[k].first + as[l].first > x) {
                        break;
                    }
                    if (as[i].first + as[j].first + as[k].first + as[l].first == x) {
                        cout << 1 + as[i].second << " " << 1 + as[j].second << 
                            " " << 1 + as[k].second << " " << 1 + as[l].second << "\n";
                        return 0;
                    }
                }
            }
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}
}  // namespace f0

int main() { f0::main(); }

