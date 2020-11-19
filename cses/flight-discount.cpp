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
const int INFTY = 1e9 + 100;

int n, m;
struct edge {int out; ll w; };
vector<edge> es[N];
vector<edge> esrev[N];


struct event { int out; ll dist; bool operator > (const event &other) const { return dist > other.dist; } };
bool visited1[N];
ll dists1[N];

bool visitedn[N];
ll distsn[N];

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b; ll c; cin >> a >> b >> c; 
        es[a].push_back(edge {.out=b, .w=c });
        esrev[b].push_back(edge{.out=a, .w=c});
    }

    for(int i = 1; i <= n; ++i) {
        dists1[i] = distsn[i] = INFTY;
    }

    {
        minqueue<event> q;
        q.push(event{.out=1, .dist=0});
        while(!q.empty()) {
            event cur = q.top(); q.pop();
            if (visited1[cur.out]) { continue; } 
            visited1[cur.out] = true;
            dists1[cur.out] = cur.dist;
            // cerr << "[" << cur.out << " " << cur.dist << "]\n";
            for(edge e : es[cur.out]) {
                q.push(event { .out=e.out, .dist=cur.dist + e.w});
            }
        }
    }

    // cerr << "[dists "; for(int i = 1; i <= n; ++i) { cerr << dists1[i] << " "; } cerr << "]\n";

    {
        minqueue<event> q;
        q.push(event{.out = n, .dist=0});
        while(!q.empty()) {
            event cur = q.top(); q.pop();
            if (visitedn[cur.out]) { continue; }
            visitedn[cur.out] = true;
            distsn[cur.out] = cur.dist;
            // cerr << "[rev " << cur.out << " " << cur.dist << "]\n";

            for(edge e : esrev[cur.out]) {
                q.push(event {.out=e.out, .dist=cur.dist + e.w});
            }
        }
    }

    // cerr << "[dists-rev "; for(int i = 1; i <= n; ++i) { cerr << distsn[i] << " "; } cerr << "]\n";


    ll best = -1;
    for(int v = 1; v <= n; ++v) {
        for(edge e : es[v]) {
            // cerr << "[1 -" << dists1[v] << "-> " << v <<  
            // " -" << e.w/2 << "-> " << e.out << " -" << distsn[e.out] << "-> n" << "]\n";
            
            if (best == -1) { best = dists1[v] + e.w/2 + distsn[e.out]; }
            else { best = min<ll>(best, dists1[v] + e.w/2 + distsn[e.out]); }
        }
    }

    cout << best << "\n";

    return 0;
}
