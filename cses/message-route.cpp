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

const int N = int(1e5) + 10;
bool visited[N];
int dist[N];
int prevv[N];
vector<int> es[N];
int n, m;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
        es[b].push_back(a);
    }

    queue<int> q;
    q.push(1);
    while(!q.empty()) {
        int v = q.front(); q.pop();
        if (v == n) {
            vector<int> path;
            int cur = v;
            while(cur != 1) {
                path.push_back(cur); cur = prevv[cur];
            }
            path.push_back(1 /*=cur*/);
            cout << path.size() << "\n";

            for(int i = path.size() - 1; i >= 0; i--) {
                cout << path[i] << " ";
            }
            cout << "\n";
            return 0;
        }

        for(int w : es[v]) {
            if (visited[w]) { continue; }
            dist[w] = dist[v] + 1;
            visited[w] = true;
            prevv[w] = v;
            q.push(w);
        }
    }
    cout << "IMPOSSIBLE\n";
    return 0;
}
