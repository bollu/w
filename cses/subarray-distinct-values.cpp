#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <bitset> // instead of bool[N];
#include <stdlib.h> // for exit()

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template<typename T>
using minqueue = priority_queue<T,vector<T>,greater<T>>;

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
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, k; cin >> n >> k;
    vector<ll> as(n);
    for(ll i = 0; i < n; ++i) {
        cin >> as[i];
    }

    ll tot = 0;

    // idea: two pointers that keeps track of how elements have been encountered so far. Keep a multiset (elem -> count) map,
    // and a summary `nelems` that counts how many elements have been seen so far. Use the multiset to figure out when a new
    // element has been added (count increases to 1 from 0), and when an element has been dropped (count decreases from 1 to 0).
    // Use this to maintain a sliding window where we have <= k elements.
    ll l = -1;
    ll nelems = 0;
    std::map<ll, ll> counts;
    for(ll r = 0; r < n; ++r) {
        if (counts[as[r]] == 0) { nelems++; }
        counts[as[r]]++;

        while(nelems > k) {
            l++;
            if (counts[as[l]] == 1) { nelems--; }
            counts[as[l]]--;
            assert(counts[as[l]] >= 0);
        }
        // cout << "r=" << r << "|l=" << l << "\n";
        tot += r-l;
    }

    cout << tot << "\n";
    return 0;
}
