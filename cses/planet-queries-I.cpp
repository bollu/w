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

#include <iostream>
using namespace std;
  
// https://yuihuang.com/cses-1750/

// a[x][i] = vertex from travelleing starting at `x` 2^i times. 
const int N = 2e5 + 10;
int n, q, travel[N][31], x, k;
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> q;
    for (int i = 1; i <= n; i++){
        cin >> travel[i][0];
    }

    for (int b = 1; b < 31; b++){
        for (int v = 1; v <= n; v++){
            // to travel from 2^2=4 -> 2^3 = 8
            // write 2^3 = 2^2 . 2 = 2^2 + 2^2
            // 2^(n+1) = 2^n + 2^n
            // f^(n)(x) = f^n/2 (f^n/2 (x))
            // if log n = b
            // a[v][b] = a[a[v][b-1]][b-1];
            int half = travel[v][b-1]; 
            travel[v][b] = travel[half][b-1];
        }
    }
    while (q--){
        cin >> x >> k;
        for (int i = 0; i < 31; i++){
            // 2 = 1 0
            // travel^i(x) 
            // = travel^[\sum[i] b[i] 2^i ] (x)
            // = (\circ {iverson: b[i] = 1} travel^(2^i)) (x)
            if (k & (1<<i)){
                x = travel[x][i];
            }
        }
        cout << x << "\n";
    }

    return 0;
}
