#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
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


// LCA with binary lifting
namespace f0 {
const int N = 2 * 1e5 + 10;
int n, q;
const int EXP = 32;
int ps[N][EXP+10];
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;

    for(int i = 2; i <= n; ++i) {
        cin >> ps[i][0];
    }

    for(int exp = 0; exp < EXP; ++exp) {
        ps[1][exp] = -1;
    }


    // binary lifting.
    for(int exp = 1; exp < EXP; ++exp) {
        for(int i = 2; i <= n; ++i) {
            int mid = ps[i][exp-1];
            if (mid == -1) { ps[i][exp] = -1; }
            else { ps[i][exp] = ps[mid][exp-1]; }
        }
    }

    // cout << "===\n";
    // for(int i = 1; i <= n; ++i) {
    //     for(int exp = 0; exp <= 5; ++exp) {
    //         cout << ps[i][exp] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "===\n";

    for(int i = 0; i < q; ++i) {
        int x, k; cin >> x >> k;
        for(int exp = 0; exp < EXP; ++exp) {
            if (k & (1 << exp)) {
                x = ps[x][exp];
                if (x == -1) { break; }
            }
        }

        cout << x << "\n";
    }
    return 0;
}

}

// LCA with RMQ
namespace f1 {
    int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}
}

int main() { 
    return f0::main();
}
