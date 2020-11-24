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
// calculate SCC
const int N = 1e5 + 10;
bool vis[N];
vector<int> es[N];
int comp[N];

vector<int> esrev[N];
bool visrev[N];
int comprev[N];

void dfs(int v, int c)  {
    comp[v] = c;
    vis[v] = true;
    for(int w : es[v]) {
        if (vis[w]) { continue; } dfs(w, c);
    }
}
void dfsrev(int v, int c)  {
    comprev[v] = c;
    visrev[v] = true;
    for(int w : esrev[v]) {
        if (visrev[w]) { continue; } dfsrev(w, c);
    }
}

int n, m;

// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
// https://www.youtube.com/watch?v=9Wbej7Fy5Lw
// https://www.youtube.com/watch?v=iYJqgMKYsdI
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
        esrev[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) { if (!vis[i]) { dfs(i, i); } }
    for(int i = 1; i <= n; ++i) { if (!visrev[i]) { dfsrev(i, i); } }

    return 0;
}
