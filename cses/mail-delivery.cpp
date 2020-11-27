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

namespace f0 {

const int N = 2 * (1e5 + 10);
const int M = 3 * (1e5 + 10);

using count = int;
int n, m;

struct edge {int v; int w; bool vis; };
edge edges[M];
vector<int> es[N];
vector<int> path;


void visit(int v) {
    for (int vwix: es[v]) {
        edge *e = edges + vwix;
        if (e->vis) { continue; }
        e->vis = true;
        int w = e->v == v ? e->w : e->v;
        visit(w);
    }
    path.push_back(v);
}

bool ereachable[M];
bool connected[N];
void ccomp(int v)  {
    connected[v] = true;
    for (int eix : es[v]) {
        ereachable[eix] = true;
        edge *e = edges + eix;
        int w = e->v == v ? e->w : e->v;
        if (!connected[w]) { ccomp(w); }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int a, b; cin >> a >> b;
        edges[i].v = a;
        edges[i].w = b;
        edges[i].vis = false;
        es[a].push_back(i); es[b].push_back(i);
    }

    for(int i = 1; i <= n; ++i) {
        if (es[i].size() % 2 == 1) {
            cout << "IMPOSSIBLE\n"; return 0;
        }
    }

    ccomp(1);
    for(int i = 1; i <= m; ++i) {
        if (!ereachable[i]) { cout << "IMPOSSIBLE\n"; return 0; }
    }

    visit(1); std::reverse(path.begin(), path.end());

    for(int v : path) { cout << v << " "; }
    cout << "\n";
    return 0;
}

} // end f0

int main() { return f0::main(); }
