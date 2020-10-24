#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <numeric> // for gcd
#include <assert.h>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

// https://www.youtube.com/watch?v=G0ocgTgW464


// I should have thought of using a `map` to store how many previous subarrays
// had a partial sum of 'x'.


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

template<typename T1, typename T2>
ostream &operator <<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}

int main() { 
    ll n, x; cin >> n >> x;
    vector<ll> nums(n+1);
    for(ll i = 0; i < n; ++i) { cin >> nums[i]; }
    map<ll, ll> partial_sums_count;

    ll count = 0;
    ll cursum = 0;
    for(ll i = 0; i < n; ++i) {
        cursum += nums[i];
        if (cursum == x) { count++; }
        // x = cursum - partial_sum
        // partial_sum = cursum - x
        auto it = partial_sums_count.find(cursum - x);
        if (it != partial_sums_count.end()) {
            count += it->second;
        }

        partial_sums_count[cursum]++;
    }
    cout << count << "\n";
    return 0;
}
