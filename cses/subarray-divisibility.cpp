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
    vector<ll> xs(n);
    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
        xs[i] = xs[i] % n;
        if (xs[i] < 0) { xs[i] += n; }
    }

    ll count = 0;
    ll cursum = 0;
    map<ll, ll> partial_sum_count;
    partial_sum_count[0] = 1;

    for (int i = 0; i < n; ++i) {
        cursum = (cursum + xs[i]) % n;
        auto it = partial_sum_count.find(cursum);
        if (it != partial_sum_count.end()) {
            count += it->second;
        }

        // cout << "xs[" << i << "]:" << xs[i] << " | cursum: " << cursum << " | count: " <<  count << "\n";
        // for(auto it : partial_sum_count) { cout << it << " "; } cout << " | count: " << count << "\n";
        partial_sum_count[cursum]++;
    }

    cout << count << "\n";

    return 0;
}
