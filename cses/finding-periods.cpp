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

const int LEN = 1e7;
int zarr[LEN];

void mkz(const string &s) {
    zarr[0] = 0;
    int shade = 0;
    int i = 1;
    const int n = s.size();
    for(int i = 1; i < n; ++i) {
        assert(i > shade);
        const int shaderight = shade + zarr[shade];
        if (i < shaderight) {
            zarr[i] = min<int>(zarr[i - shade], shaderight  - i);
        }
        while(i + zarr[i] < n && s[i + zarr[i]] == s[zarr[i]]) { zarr[i]++; }
        if (shaderight < i + zarr[i]) { shade = i; }
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s; cin >> s;
    mkz(s);
    const int n = s.size();
    set<int> ps;
    ps.insert(n);

    for(int i = 0; i < n; ++i) {
        if (i + zarr[i] == n) { ps.insert(i); }
    }

    // for(int i = 0; i < n; ++i) {
    //     cout << zarr[i] << " " << s[i] << "| ";
    // }
    // cout << "\n";

    for(int i : ps) {
        cout << i << " ";
    }
    cout << "\n";
    return 0;
}
