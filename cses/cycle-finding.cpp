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

const int N = 2500 + 10;
const int INFTY = 1e9 + 100;

struct edge {int u; int v; int w;};

ll add(ll a, ll b) {
    if ((a == INFTY && b > 0 )|| (b == INFTY && a > 0)) { return INFTY; }
    return a + b;
}

// https://cp-algorithms.com/graph/finding-negative-cycle-in-graph.html
// https://www.youtube.com/watch?v=kZfm68XKC58
// Interesting idea to think of negative cycle as shortest distance to a smaller node A'
// vertex being relaxed is either part of a negative cycle, or is adjacent to the negative cycle!
namespace f0 {

vector<edge> alles;
ll dist[N];
ll relaxant[N];


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        alles.push_back(edge {.u = a, .v = b, .w = c});
    }

    for(int i = 1; i <= n; ++i) {
        dist[i] = i == 1 ? 0 : INFTY;
        relaxant[i] = i;
    }

    for(int i = 1; i <= n; ++i) {
        for(edge e: alles) {
            ll newdist = add(dist[e.u], e.w);
            if (newdist < dist[e.v])   {
                dist[e.v] = newdist;
                relaxant[e.v] = e.u;
            }
        }
    }

    ll negsrc = -1;
    for(edge e: alles) {
        ll newdist = add(dist[e.u], e.w);
        if (newdist < dist[e.v])   {
            negsrc = e.v; // THINK: should this be e.u?
            // THINK: do I need to rerun this?
            dist[e.v] = newdist;
            relaxant[e.v] = e.u;
        }
    }

    if (negsrc == -1) {
        cout << "NO\n"; return 0;
    }
    
    // how to find the correct start of the cycle??
    // the CP-algorithms code contains this:
    for(int i = 1; i <= n; ++i) { negsrc = relaxant[negsrc]; }
    vector<int> cycle;
    int cur = negsrc;
    while(cur != negsrc || cycle.size() < 1) {

        cycle.push_back(cur);
        cur = relaxant[cur];
    }

    cout << "YES\n";
    cout << cycle[0] << " ";;
    for(int i = cycle.size()-1; i >= 0; i--) {
        cout << cycle[i] << " ";
    }
    cout << "\n";
    

    return 0;
}

}


// Same, just bail our early on finding a negative edge.
// I find it really annoying that we need to do the backtracking thing.
// IDEA:
// use DFS, find back edges
// if we find a negative weight backedgeedge that relaxes
// distance, then we know that we have found a cycle.
// This eliminates the need to do the "backward trace" thing that I don't trust
// very much.
namespace f1 {
vector<edge> alles;
vector<edge> es[N];

ll dist[N];
ll relaxant[N];

ll dfsprev[N];
ll color[N];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int a, b, c; cin >> a >> b >> c;
        alles.push_back(edge {.u = a, .v = b, .w = c});
    }

    for(int i = 1; i <= n; ++i) {
        dist[i] = i == 1 ? 0 : INFTY;
        relaxant[i] = i;
    }

    for(int i = 1; i <= n; ++i) {
        for(edge e: alles) {
            ll newdist = add(dist[e.u], e.w);
            if (newdist < dist[e.v])   {
                dist[e.v] = newdist;
                relaxant[e.v] = e.u;
            }
        }
    }

    ll negsrc = -1;
    for(edge e: alles) {
        ll newdist = add(dist[e.u], e.w);
        if (newdist < dist[e.v])   {
            assert(e.w < 0);
            negsrc = e.u;
            break;
        }
    }

    if (negsrc == -1) {
        cout << "NO\n"; return 0;
    }

    for(int i = 1; i <= n; ++i) { negsrc = relaxant[negsrc]; }

    // how to find the correct start of the cycle??
    // the CP-algorithms code contains this:
    // for(int i = 1; i <= n; ++i) { negsrc = relaxant[negsrc]; }
    vector<int> cycle;
    int cur = negsrc;
    while(cur != negsrc || cycle.size() < 1) {

        cycle.push_back(cur);
        cur = relaxant[cur];
    }

    cout << "YES\n";
    cout << cycle[0] << " ";;
    for(int i = cycle.size()-1; i >= 0; i--) {
        cout << cycle[i] << " ";
    }
    cout << "\n";
    

    return 0;
}

}

int main() { return f1::main(); }