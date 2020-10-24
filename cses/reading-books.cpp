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

int main() {
    int n;
    cin >> n;

    vector<int> ts(n);
    for (int i = 0; i < n; ++i) {
        cin >> ts[i];
    }

    sort(ts.begin(), ts.end());

    // bad strategy: greedily read a book
    // 2 | 8                       |[time=10]
    // 3   | 2 |[time=5]|          |[time=10] 8   |[time=18]
    

    // 8      2 3
    // 2 3    8 
    

    // one person reads ascending, other descending.
    // TODO: correctness?

    return 0;
}
