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

struct event {
    ll price, nhops;
    ll v;
    bool operator > (const event &other) const {
        return make_tuple(price, nhops) > make_tuple(other.price, other.nhops);
    }
};

// naively collect all data at the terminal node and then filter
namespace f0 {

struct edge {
    ll v, price;
};

const int N = 1e5 + 10;
const ll INFTY = 1e9 + 10;
vector<edge> es[N];
int n, m;
bool visited[N];

vector<event> finalroutes;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        ll a, b, c; cin >> a >> b >> c;
        es[a].push_back(edge { .v = b, .price = c});
    }

    minqueue<event> q;
    q.push(event { .price=0, .nhops=0, .v=1});

    while(!q.empty()) {
        event ev = q.top(); q.pop();
        visited[ev.v] = true;

        for (edge e: es[ev.v]) {
            if (visited[e.v]) { continue; }
            q.push(event { .price = ev.price + e.price, .nhops = ev.nhops + 1, .v = e.v});
        }

        if (ev.v == n) {
            if (finalroutes.empty()) {
                finalroutes.push_back(ev);
            } else if (ev.price == finalroutes[0].price) {
                finalroutes.push_back(ev);
            }
        }
    }

    cout << finalroutes[0].price << " " << finalroutes.size() << " ";
    ll minflights = INFTY, maxflights = -INFTY;
    for(event ev : finalroutes) {
        minflights = std::min<ll>(minflights, ev.nhops);
        maxflights = std::max<ll>(maxflights, ev.nhops);
    }
    cout << minflights << " " << maxflights << "\n";

    return 0;
}

} // end f0

// This is too slow, because I depend on being able to find *all* paths, and thus try
// to loop over every path.
namespace f1 {

struct edge {
    ll v, price;
};

const int MOD = 1e9 + 7;
const int N = 1e5 + 10;
const ll INFTY = 1e9 + 10;
vector<edge> es[N];
int n, m;
bool visited[N];

ll bestprice = INFTY;
ll minhops = 0;
ll maxhops = 0;
ll npaths = 0; 

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        ll a, b, c; cin >> a >> b >> c;
        es[a].push_back(edge { .v = b, .price = c});
    }

    minqueue<event> q;
    q.push(event { .price=0, .nhops=0, .v=1});
    visited[1] = true;

    while(!q.empty()) {
        event ev = q.top(); q.pop();
        if (visited[ev.v]) { continue; }
        visited[ev.v] = true;

        // quit early.
        // if (npaths > 0 && ev.price > bestprice) { continue; }

        for (edge e: es[ev.v]) {
            q.push(event { .price = ev.price + e.price, .nhops = (ev.nhops + 1), .v = e.v});
        }

        if (ev.v == n) {
            // we don't know the best price.
            if (npaths == 0) { 
                npaths = 1;
                bestprice = ev.price;
                minhops = maxhops = ev.nhops;
                assert(false);
            }
            // skip this if we don't have the best price
            else if (ev.price ==  bestprice) {
                npaths = (npaths + 1) % MOD;;
                minhops = min<ll>(minhops, ev.nhops);
                maxhops = max<ll>(maxhops, ev.nhops);
             }
        }
    }

    cout << bestprice << " " <<  npaths << " " << minhops << " " << maxhops << "\n";
    return 0;
}


} // end f1

int main() { return f1::main(); }