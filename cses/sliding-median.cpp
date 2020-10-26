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

// https://scicomp.stackexchange.com/a/26260/31940

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

namespace f0 {

// this is the cheating solution that uses PBDS. This passes!
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, k;
    cin >> n >> k;
    ordered_set<pair<ll, ll>> vals;
    vector<ll> valsarr(n + 1);
    for (int i = 1; i <= n; ++i) {
        ll x;
        cin >> x;
        valsarr[i] = x;
        vals.insert({x, i});

        // cerr << i << ":";

        if (i > k) {
            auto it = vals.find({valsarr[i - k], i - k});
            vals.erase(it);
        }

        if (i >= k) {
            // eg. if we have window of size 4, we want to find 
            // order 0 1 2 3  | order 1
            //         ^
            // eg. if we have window of size 5, we want to find 
            // order 0 1 2 3 4  | order 2
            //           ^
            // 5 -> 5/2
            // 4 -> 4/2 - 1
            cout << vals.find_by_order(k % 2 == 0 ? k/2 - 1 : k/2)->first << " ";
        }

        // cerr << "\n---\n";
    }
    cout << "\n";
    return 0;
}
}  // namespace f0

namespace f1 {

static const ll N = 300000;

int arr[N];

// This is not yet solved
// https://stackoverflow.com/questions/9841416/find-median-in-a-fixed-size-moving-window-along-a-long-sequence-of-data#:~:text=In%20side%20the%20window%2C%20sort,two%20heaps%20is%20the%20median.
int main() {
    ll n, k;
    cin >> n >> k;
    // for(int i = 0; i < 10; ++i) { cerr << i << ":" << ceilpow2(i) << "\n"; }
    int window[k];
    for(int i = 0; i < k; ++i) { cin >> arr[i]; window[i] = arr[i]; }
    std::sort(window, window+k);

    std::set<pair<int, int>> lower, upper;
    for(int i = 0; i < k/2+1; ++i) { lower.insert({window[i], i}); }
    for(int i = k/2+1; i < k; ++i) { upper.insert({window[i], i}); }

    // now incrementally take in new elements.
    for(int i = k; i < n ; ++i) {
        cout << "\n---\n";
        for(auto it : lower) { cout << it << " "; } cout << "|";
        for(auto it : upper) { cout << it << " "; }

        pair<int, int> towipe = { arr[i-k], i-k};
        pair <int, int> median = *lower.rbegin();
        cout << median.first << " ";

        cin >> arr[i];

        pair<int, int> newelem = {arr[i], i};
        if (newelem <= median) {
            lower.insert(newelem);

            set<pair<int, int>>::iterator it;
            if((it = lower.find(towipe)) != lower.end()) {
                lower.erase(it);

            } else {
                upper.erase(upper.find(towipe));
                upper.insert(*lower.rbegin());
                lower.erase(*lower.rbegin());
            }
            
        } else {
            upper.insert(newelem);

            set<pair<int, int>>::iterator it;
            if((it = lower.find(towipe)) != lower.end()) {
                lower.erase(it);
                lower.insert(*upper.begin());
                upper.erase(upper.begin());
            } else {
                upper.erase(upper.find(towipe));
            }
        }

        assert(lower.size() == k/2+1);
        assert(upper.size() == k-(k/2+1));
    }

    pair <int, int> median = *lower.rbegin();
    cout << median.first << "\n";
    return 0;

}
}  // namespace f1
int main() { f0::main(); }
