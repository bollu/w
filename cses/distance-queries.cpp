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

#include "grapher.h"
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

int n, q;
const int N = 2 * 1e5 + 10; const int EXP = 31;
vector<int> es[N]; //edges
int ds[N]; //depths
int ps[N][EXP]; // parents


void dfs(int u, int v, int d) {
    ds[v] = d; for(int w: es[v]) {  if (w == u) { continue; } dfs(v, w, d+1); ps[w][0] = v; }
}

int up(int a, int dist) {
    assert(dist >= 0);
    for(int e = 0; e < EXP; ++e) { if (dist & (1 << e)) { a = ps[a][e]; } };
    return a;
}

int main() {
    grapher_init();
    std::ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> n >> q;
    ps[1][0] = 1;
    // for(int i = 1; i <= n; ++i) { grapher_v(i); }
    
    for(int i = 2; i <= n; ++i)  { 
        int a, b; cin >> a >> b;
        es[a].push_back(b); es[b].push_back(a);
        grapher_e(a, b);
    }
    grapher_show();
    
    ps[1][0] = 1; dfs(1, 1, 1); //root
    
    for(int i = 1; i <= n; ++i) { grapher_v(i, std::to_string(i) + ":" + std::to_string(ds[i])); }
    grapher_show();
    
    for(int exp = 1; exp < EXP; ++exp) {// binary lift.
        for(int i = 1; i <= n; ++i) {
            int mid = ps[i][exp - 1]; ps[i][exp] = ps[mid][exp-1]; // to travel 2n, travel n;n
        }
    }

    for(int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;
        const int da = ds[a], db = ds[b], md = min<int>(da, db);
        a = up(a, ds[a] - md); b = up(b, ds[b] - md);
        assert(ds[a] == ds[b]);

        if (a == b) { cout << abs(db - da) << "\n"; continue; }

        // If we can jump, then jump. If we can't jump,
        // then none of our ancestors can make the jump either!
        // So it's perfectly safe to try the "largest jump" to 
        // "smallest jump". If scared, to the `exp--` separately.
        // To have the `exp--` in the loop, we need to have the stronger
        // condition that *EVEN IF I JUMP*, my ancestors can't make the
        // jump. This is slightly subtle, since it relies on a loop
        // invariant. 
        for(int e = EXP-1; e >= 0; e--) {
            if (ps[a][e] != ps[b][e]) {
                a = ps[a][e]; b = ps[b][e]; // can jump, make jump.
            }
        }
        assert(ps[a][0] == ps[b][0]);
        int lca = ps[a][0];
        cout << (da - ds[lca]) + (db - ds[lca]) << "\n"; 
    }

    return 0;
}
