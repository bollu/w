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

namespace f0 {
int main() { 
    int n, x; cin >> n >> x;
    vector<int> nums(n+1);
    for(int i = 0; i < n; ++i) { cin >> nums[i]; }

    int count = 0;
    int cursum = 0; int l = 0, r = 0;
    while(r < n) {
        cursum += nums[r];
        r++;
        while (cursum > x && l < r) {
            cursum -= nums[l];
            l++;
        }

        if (cursum == x) { count++; }
    }
    
    cout << count << "\n";

    return 0;
}
}

int main() {
    ll n, x; cin >> n >> x;
    vector<ll> nums(n+1);
    map<ll, ll> partial_sums;
    for(ll i = 0; i < n; ++i) { cin >> nums[i]; }

    ll count = 0;
    ll cursum = 0; ll l = 0, r = 0;
    while(r < n) {
        cursum += nums[r];
        r++;
        if (cursum == x) { count++; }
        else {
             // cursum - prevsum = x
             // prevsum = cursum - x
             auto it = partial_sums.find(cursum - x);
             if (it != partial_sums.end()) {
                 count += it->second;
             }
        }
        partial_sums[cursum] += 1;
    }
    
    cout << count << "\n";

    return 0;
}
