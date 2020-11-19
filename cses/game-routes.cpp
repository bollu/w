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

const ll MOD = 1e9 + 7;
const int N = 1e5 + 10;
vector<int> es[N];
int n, m;

bool visited[N];
ll ways[N]; // number of ways of reaching vertex
void visit(int s) {
    if (visited[s]) { return; }
    visited[s] = true;
    for(int t : es[s]) {
        visit(t);
        ways[s] = (ways[s] + ways[t]) % MOD;  
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    ways[n] = 1; visited[n] = true;

    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
    }

    visit(1);
    cout << ways[1] % MOD << "\n";; 
    return 0;
}
