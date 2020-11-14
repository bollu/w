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
vector<int> es[N];

enum State { White=0, Gray=1, Black=2 };
State visited[N];
int parent[N];

int n, m;

int depth = 0;

void dfs(int v) {
    if (visited[v] == Black) { return; }
    // cerr << std::string(depth, ' ') << v << "\n";; depth++;
    visited[v] = Gray;
    for(int w : es[v]) {
        if (visited[w] == Black) { continue; }
        else if (visited[w] == Gray) {
            // found cycle.
            int cur = v;
            vector<int> cycle;
            while(cur != w) { cycle.push_back(cur); cur = parent[cur]; }
            if (cycle.size() < 2) { continue; }
            cycle.push_back(cur);
            cout << cycle.size() + 1 << "\n";
            cout << w << " ";
            for(int c : cycle) { cout << c << " "; }
            cout << "\n";
            exit(0);
        } else {
            parent[w] = v;
            dfs(w); // recurse.
        }
    }
    // --depth;
    visited[v] = Black;
}
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
        es[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) {
        dfs(i);
    }
    cout << "IMPOSSIBLE\n";

    return 0;
}
