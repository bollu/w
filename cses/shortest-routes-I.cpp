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
const ll C = int(1e9) + 7;
const ll INFTY = C * N;
using Ix = int; using Weight = int;
int n, m;
struct Edge { int vertex; ll wt; bool operator < (const Edge &other) const { return wt < other.wt; } };
struct Event { int vertex; ll dist; bool operator < (const Event & other) const { return dist < other.dist; } };
vector<Edge> es[N];
bool visited[N];
ll dists[N];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // puts the *largest* element first. fuck me.
    priority_queue<Event> events; 

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        es[a].push_back(Edge {.vertex=b, .wt=c});
    }

    for(int i = 1; i <= n; ++i) { dists[i] = INFTY; }

    events.push(Event{.vertex=1, .dist=0});
    while(!events.empty()) {
        Event evt = events.top(); events.pop();
        if (visited[evt.vertex]) { continue; }
        dists[evt.vertex] =  evt.dist;
        // cerr << "evt(v=" << evt.vertex << " " << "dist=" << evt.dist << ")\n";
        visited[evt.vertex] = true;
        for (Edge edge : es[evt.vertex]) {
            // cerr << " " << evt.vertex << " pushed: evt(v=" << edge.vertex << " " << "dist=" << edge.wt + evt.dist << ")\n";
            events.push(Event{.vertex=edge.vertex, .dist=-edge.wt + evt.dist});
        }

    }

    for(int i = 1; i <= n; ++i) { cout << -dists[i] << " "; }
    cout << "\n";

    return 0;
}
