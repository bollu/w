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

const int N = 1e5 + 10;
vector<int> es[N];
const int GRAY = 1, BLACK = 2;

int n, m;
int visited[N];
int pred[N];

void dfs(int prev, int cur) {
    // cerr << "dfs[" << prev << " " << cur << "]\n";
    if (visited[cur] == BLACK) { return; }
    if (visited[cur] == GRAY) {
        // backedge!
        vector<int> cycle;
        cycle.push_back(cur);
        int walker = prev;
        do {
            // cerr << "walker: " << walker << "\n";
            cycle.push_back(walker);
            walker = pred[walker];
        } while (cur != walker);
        cycle.push_back(cur);

        cout << cycle.size() << "\n";
        for(int i = cycle.size()-1; i >=0; i--) {
            cout << cycle[i] << " \n"[i == 0];
        }
        exit(0);
    }

    visited[cur] = GRAY;
    pred[cur] = prev;
    for(int next: es[cur]) {
        dfs(cur, next);
    }
    visited[cur] = BLACK;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
    }

    for(int i = 1; i <= n; ++i) {
        if (visited[i] == 0) { dfs(i, i);  };
    }

    cout << "IMPOSSIBLE\n";
    return 0;
}
