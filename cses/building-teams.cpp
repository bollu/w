#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>

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

// Naive code to perform search over all components
// while keeping track of parity. Passes, but I want
// a cleaner way to implement this.
namespace f0 {

static const int N = int(1e5) + 10;
vector<int> es[N];
bool parity[N];
bool visited[N];
int n, m;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; 
        cin >> a >> b;
        es[a].push_back(b);
        es[b].push_back(a);
    }

    queue<int> q;

    while(1) {
        bool foundUnvisited = false;
        for(int i = 1; i <= n; ++i) {
            if (visited[i]) { continue; }
            q.push(i); visited[i] = true; parity[i] = 1;
            foundUnvisited = true;
            break;
        }
        if (!foundUnvisited) { break; }

        while(!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : es[v]) {
                if (visited[w]) {
                    if (parity[w] != !parity[v]) {
                        cout << "IMPOSSIBLE\n"; return 0;
                    }
                } else {
                    // not visited
                    visited[w] = true;
                    parity[w] = !parity[v];
                    q.push(w);
                }
            }
        }

    }

    for(int i = 1; i <= n; ++i) {
        cout << (parity[i] ? "1" : "2") << " ";
    }
    cout << "\n";

    return 0;
}

} // namespace f0

int main() { f0::main(); }
