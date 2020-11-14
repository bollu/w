#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <cmath>

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

const int N = int(1e5) + 10;
const int M = 2 * int(1e5) + 10;
int ps[N];
int rnks[N];
int n, m;

int root(int i) {
    if (i == ps[i]) { return i; }
    int r = root(ps[i]);
    ps[i] = r;
    return r;
}

void unite(int i, int j) {
    i = root(i);
    j = root(j);
    if (i == j) { return; }
    if (rnks[i] > rnks[j]) {
        // connect smaller to larger
        ps[j] = i;
    } else if (rnks[i] < rnks[j]) {
        ps[i] = j;
    } else {
        // subtree under j became larger by heigt 1.
        ps[i] = j; rnks[j]++;
    }
}




int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >>  m;
    for(int i = 1; i <= n; ++i) { ps[i] = i; }
    // for(int i = 1; i <= n; ++i) { cerr << ps[i] << " "; } cerr << "\n";
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        unite(a, b);
    }
    // for(int i = 1; i <= n; ++i) { cerr << ps[i] << " "; } cerr << "\n";



    set<int> leaders;
    for(int i = 1; i <= n; ++i) { leaders.insert(root(i)); }; 
    cout << leaders.size() - 1 << "\n";

    vector<int> leadersvec(leaders.begin(), leaders.end());
    for(int i = 0; i < leaders.size() - 1; ++i) {
        cout << leadersvec[i] << " " << leadersvec[i+1] << "\n";
    }
    cout << "\n";
    return 0;
}
