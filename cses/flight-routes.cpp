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
const int INFTY = 1e9;

int n, m, k;
struct edge { int v; ll w; };
struct event { 
    int v; ll dist;
    bool operator < (const event &other) const {
        return dist < other.dist || (dist == other.dist && v < other.v);
    }

    bool operator > (const event &other) const {
        return dist > other.dist || (dist == other.dist && v > other.v);
    }

};

vector<ll> dists [N];
vector<edge> es[N];
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m >> k;
    for(int i = 0; i < m; ++i) {
        int a, b; ll c;
        cin >> a >> b >> c;
        es[a].push_back(edge {.v = b, .w = c});
    }
    
    minqueue<event> q;
    q.push(event { .v=1, .dist=0});
    while(!q.empty()) {
        event evt = q.top(); q.pop();
        // we have enough distances.
        if (dists[evt.v].size() == k) { continue; }
        dists[evt.v].push_back(evt.dist);

        for(edge e : es[evt.v]) {
            q.push(event { .v = e.v, .dist = evt.dist + e.w });
        }
    }

    // no need to sort, will be in the correct order because we push back. 
    // std::sort(dists[n].begin(), dists[n].end());
    for(int i = 0; i < dists[n].size(); ++i) {
        // nice golfing to print \n on final iteration.
        cout << dists[n][i] << " \n"[i+1== dists[n].size()];
    }

    
    return 0;
}
