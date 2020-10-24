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

struct N { 
    int ix; int val; 
    bool operator < (const N &other) const {
        return make_pair(val, ix) < make_pair(other.val, other.ix);
    }
};

int main() { 
    int n, x; cin >> n >> x;
    
    vector<N> as(n);
    for(int i = 0; i < n; ++i) { cin >> as[i].val; as[i].ix = i; }
    std::sort(as.begin(), as.end());

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {

            int l = j+1,  r = n;
            while (l < r) {
                int mid = (l + r) / 2;
                int sum = as[i].val + as[j].val + as[mid].val;

                if (sum == x) {
                    cout << 1 + as[i].ix << " " << 1 + as[j].ix << " " << 1 + as[mid].ix << "\n";
                    return 0;
                }

                if (sum < x) { l = mid+1;} else { r = mid; }
            }
        }
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
