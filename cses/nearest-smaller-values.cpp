#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
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
static const int N = 1000000;

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

//! namespace f1 {
//! 
//! int main() {
//!     int n;
//!     cin >> n;
//!     vector<int> vals(n + 1);
//! 
//!     ordered_set<int> vals_set;
//!     for (int i = 1; i <= n; ++i) {
//!         cin >> vals[i];
//!         vals_set.insert(vals[i]);
//!     }
//! 
//!     vector<int> order2ix(n + 1);
//!     for (int i = 1; i <= n; ++i) {
//!         order2ix[i] = i;
//!     }
//!     std::sort(order2ix.begin(), order2ix.end(), [&vals](int i, int j) {
//!         return (vals[i] < vals[j]) || (vals[i] == vals[j] && i < j);
//!     });
//! 
//!     vector<int> ix2order(n + 1);
//!     for (int i = 1; i <= n; ++i) {
//!         ix2order[order2ix[i]] = i;
//!     }
//! 
//!     cout << "ix:       ";
//!     for (int i = 1; i <= n; ++i) {
//!         cout << i << " ";
//!     }
//!     cout << "\n";
//!     cout << "vals:     ";
//!     for (int i = 1; i <= n; ++i) {
//!         cout << vals[i] << " ";
//!     }
//!     cout << "\n";
//!     cout << "ix2order: ";
//!     for (int i = 1; i <= n; ++i) {
//!         cout << ix2order[i] << " ";
//!     }
//!     cout << "\n";
//! 
//!     cout << "order2ix: ";
//!     for (int i = 1; i <= n; ++i) {
//!         cout << order2ix[i] << " ";
//!     }
//!     cout << "\n";
//! 
//!     // step 0
//!     // step 0: for(int i = 1; i <= n; ++i) {
//!     // step 0:     int nearest = 0;
//!     // step 0:     for(int j = 1; j < i; ++j) {
//!     // step 0:         if (vals[j] < vals[i]) { nearest = max(nearest, j);  }
//!     // step 0:     }
//! 
//!     // step 1
//!     // step 1: for(int i = 1; i <= n; ++i) {
//!     // step 1:     int nearest = 0;
//!     // step 1:     int order = ix2order[i];
//!     // step 1:     for(int o = 1; o < order; ++o) {
//!     // step 1:         if (order2ix[o] < i) { nearest = max(nearest,
//!     // order2ix[o]); } step 1:     } step 1:     cout << nearest << " "; step 1:
//!     // }
//! 
//!     // step 2: use galois connection to reorder loops
//!     // step 2: vector<int> answers(n+1);
//!     // step 2: for(int o = 1; o <= n; ++o) {
//!     // step 2:     int nearest = 0;
//!     // step 2:     for(int i = 1; i < order2ix[o]; ++i) {
//!     // step 2:         if (ix2order[i] < o) { nearest = max(nearest, i); }
//!     // step 2:     }
//!     // step 2:     answers[order2ix[o]] = nearest;
//!     // step 2: }
//! 
//!     // step 2: for(int i = 1; i <= n; ++i) {
//!     // step 2:     cout << answers[i] << " ";
//!     // step 2: }
//!     // step 2: cout << "\n";
//! 
//!     // step 3: expand nearest into array for resuse between orders
//!     // step 3: vector<int> answers(n+1);
//!     // step 3: vector<int> nearest(n+1);
//!     // step 3: for(int o = 1; o <= n; ++o) {
//!     // step 3:     nearest[o] = 0;
//!     // step 3:     for(int i = 1; i < order2ix[o]; ++i) {
//!     // step 3:         if (ix2order[i] < o) { nearest[o] = max(nearest[o], i); }
//!     // step 3:     }
//!     // step 3:     answers[order2ix[o]] = nearest[o];
//!     // step 3: }
//! 
//!     // step 3: for(int i = 1; i <= n; ++i) {
//!     // step 3:     cout << answers[i] << " ";
//!     // step 3: }
//!     // step 3: cout << "\n";
//! 
//!     cout << "\n";
//!     return 0;
//! }
//! 
//! }  // namespace f1

int main() {
    int n;
    cin >> n;
    vector<int> vs(n+1);
    for(int i = 1; i <= n; ++i) {
        cin >> vs[i];
    }
    vector<int> ord2ix(n+1);
    for(int i = 1; i <= n; ++i) { ord2ix[i] = i; }
    std::sort(ord2ix.begin(), ord2ix.end(), [&vs](int i, int j) { return vs[i] < vs[j]; });
    vector<int> ix2ord(n+1);
    for(int i = 1; i <= n; ++ i) { ix2ord[ord2ix[i]] = i; }
    // TODO: use std::vector<..>

    cout << "\n";
    return 0;
}
