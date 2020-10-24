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

struct M {
    ll duration;
    ll deadline;

    bool operator < (const M &other) {
        return duration < other.duration;
    }
};

// 2 jobs
// a. (dead[0] - dur[0]) + (dead[1] - dur[0] - dur[1]) = dead[0] + dead[1] - 2 dur[0] - dur[1]
// b. (dead[1] - dur[1]) + (dead[1] - dur[1] - dur[0]) = dead[1] + dead[0] - 2 dur[1] - dur[0]
//
// n jobs: Σi dead[i] - n dur[0] - (n-1) dur[1] - .... - dur[0]
//
//
// (2a + b)  < (a + 2b) => a - b < 0 => a < b
//
// a < b => 2a + b < a + 2b !
//
// So to make (2dur[0] - dur[1]) ssmallest, we should pick `a` to be the smaller number.

int main() {
    int n;
    cin >> n;
    vector<M> machines(n);
    for(int i = 0; i < n; ++i) { cin >> machines[i].duration >> machines[i].deadline; }

    // maximize sum[i] |finish[i] - end[i]|
    std::sort(machines.begin(), machines.end());

    ll r = 0;
    ll time = 0;
    for(int i = 0; i < n; ++i) {
        time += machines[i].duration;
        r += machines[i].deadline - time;
    }

    cout << r << "\n";

    return 0;
}
