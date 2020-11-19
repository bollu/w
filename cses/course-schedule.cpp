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


// correct solution: sort by reverse of departure time
namespace f0 {
int n, m;
const int N = 1e5 + 10;
vector<int> es[N];
int visited[N];
int t;
int finishtimes[N];

int ixs[N];
const int GRAY = 1; const int BLACK = 2;
void dfs(int prev, int cur) {
    t++;
    if (visited[cur] == BLACK) { return; }
    // loop
    if (visited[cur] == GRAY) {
        cout << "IMPOSSIBLE\n"; exit(0);

    }
    visited[cur] = GRAY;
    for(int next : es[cur]) {
        dfs(cur, next);
    }
    t++;
    visited[cur] = BLACK;
    finishtimes[cur] = t;
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
        if (visited[i] == 0) { dfs(i, i); }
    }

    for(int i = 0; i <= n; ++i) { ixs[i] = i; }
    // half-open: add length to get ending [begin, begin+len)
    // sort in *reverse* order of finishing times.
    sort(ixs+1, ixs+1+n, [&](int i, int j) { return !(finishtimes[i] < finishtimes[j]); });
    for(int i = 1; i <= n; ++i) {
        cout << ixs[i] << " \n"[i==n];
    }

    return 0;
}
}

// correct solution with easier implementation: push back
// into a vector as we depart and finally reverse.
namespace f1 {
int n, m;
const int N = 1e5 + 10;
vector<int> es[N];
int visited[N];
int t;

vector<int> ixs;
const int GRAY = 1; const int BLACK = 2;
void dfs(int prev, int cur) {
    t++;
    if (visited[cur] == BLACK) { return; }
    // loop
    if (visited[cur] == GRAY) {
        cout << "IMPOSSIBLE\n"; exit(0);

    }
    visited[cur] = GRAY;
    for(int next : es[cur]) {
        dfs(cur, next);
    }
    t++;
    visited[cur] = BLACK;
    ixs.push_back(cur);
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
        if (visited[i] == 0) { dfs(i, i); }
    }

    // half-open: add length to get ending [begin, begin+len)
    // sort in *reverse* order of finishing times.
    reverse(ixs.begin(), ixs.end());
    for(int i = 0; i < ixs.size(); ++i) {
        cout << ixs[i] << " \n"[i +1 == ixs.size()];
    }
    return 0;
}
}

int main() { return f1::main(); }