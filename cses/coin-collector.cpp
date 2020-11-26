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

const int N = 4 * (1e5 + 10);
int n, m;
vector<int> es[N];

int t = 1;
int v2t[N]; // time node was entered.
int low[N]; // lowest reachable time from node.
stack<int> S; // stack of nodes that don't know their SCC.

int ncomps = 0; // number of SCC's
int v2comp[N]; // SCC number of a given vertex.
vector<int> compes[N];
ll comp2money[N]; // money in each condensed node.
ll v2money[N];

void visit(int v) {
    v2t[v] = low[v] = t++;
    S.push(v);

    for(int w : es[v]) {
        if (!v2t[w]) { visit(w); low[v] = min<int>(low[v], low[w]); }
        // else if (!v2comp[w]) { low[v] = min<int>(low[v], low[w]); }
        else if (!v2comp[w]) { low[v] = min<int>(low[v], v2t[w]); }
    }

    if (low[v] == v2t[v]) {
        ncomps++;
        while(1) {
            int w = S.top(); S.pop(); 
            v2comp[w] = ncomps;
            comp2money[ncomps] += v2money[w];
            if (v == w) { break; }
        }
    }
}


bool visitedcomp[N];
ll comp2best[N];

void visitcomp(int c) {
    visitedcomp[c] = true;
    ll bestd = 0;
    for(int d : compes[c]) {
        if (!visitedcomp[d]) { visitcomp(d); }
        bestd = max<ll>(comp2best[d], bestd);
    }
    comp2best[c] = comp2money[c] + bestd;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m; cin >> n >> m;
    for(int i = 1; i <= n; ++i) { cin >> v2money[i]; };
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
    }
    for(int i = 1; i <= n; ++i) {
        if (!v2t[i]) { visit(i); }                                                   
    }

    assert(!S.size());

    for(int v = 1; v <= n; ++v) {
        for (int w : es[v]) {
            if (v2comp[v] != v2comp[w]) {
                compes[v2comp[v]].push_back(v2comp[w]);
            }
        }
    }

    // great, we now have the condensation graph. Visit each component.
    ll best = 0;
    for(int c = 1; c <= ncomps; ++c) {
        if (!visitedcomp[c]) { visitcomp(c); }
        best = max<ll>(best, comp2best[c]);
    }

    cout << best << "\n";
    return 0;   
}
