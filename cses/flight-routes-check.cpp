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

template<typename T>
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

// demonstrates incorrect algorithm for SCCs.
// that does not take cross edges into account.
namespace f0 {
const int N = 1e5 + 10;
int n, m;
vector<int> es[N];

int parentdfs[N];
int colordfs[N];
const int WHITE = 0, GRAY = 1, BLACK = 2;

int dsuparent[N];
int dsurank[N];

int dsuroot(int i) {
    if (dsuparent[i] == i) { return i; }
    return dsuparent[i] = dsuroot(dsuparent[i]);
}

void dsuunite(int i, int j) {
    i = dsuroot(i); j = dsuroot(j);
    if (i == j) { return; }
    if (dsurank[i] < dsurank[j]) {
        dsuparent[i] = j;
    } else if (dsurank[j] < dsurank[i]) {
        dsuparent[j] = i;
    } else {
        dsuparent[i] = j; dsurank[j]++;
    }
}

void dfs(int u, int v) {
    if (colordfs[v] == BLACK) { return; }

    parentdfs[v] = u;
    colordfs[v] = GRAY;

    for (int w : es[v]) {
        if (colordfs[w] == WHITE) { dfs(v, w); }
        // found cycle! union everything.
        if (colordfs[w] == GRAY) {
            int cur = v;
            while(1) {
                dsuunite(cur, w);
                cur = parentdfs[cur];
                if (cur == w) { break; }
            }
        }
        // found cross edge. This is the *real* problem.
        else if (colordfs[w] == BLACK) {
            assert(false && "cross edge!");
        }
    }
    colordfs[v] = BLACK;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
    }

    for(int i = 0; i < N; ++i) { dsuparent[i] = i; }

    dfs(1, 1);
    int root1 = dsuroot(1);
    for(int i = 1; i <= n; ++i) {
        if (dsuroot(i) != root1) {
            // we can reach i from root, so this means that root must be
            // unreachable from root1
            if (colordfs[i] != WHITE) {
                cout << "NO\n" << i << " " << 1 << "\n";
            } else {
                cout << "NO\n" << 1 << " " << i << "\n";
            }
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}
} // end f0

namespace f1 {
const int N = 1e5 + 10;
int n, m;
vector<int> es[N];
vector<int> esrev[N];
vector<int> exits; // order nodes by exit time.
bool vis[N];

void dfs(int v) {
    vis[v] = true;
    for(int w : es[v]) {
        if (vis[w]) { continue; }
        dfs(w);
    }
    exits.push_back(v);
}

bool visrev[N];
void dfsrev(int v) {
    visrev[v] = true;
    for(int w : esrev[v]) {
        if (visrev[w]) { continue; }
        dfsrev(w);
    }
}

// We have only a single component, so u ~> v and v ~> u for all v, u.
// This is same as `u ~> 1` and `1 ~> v` for all u, v!
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
        esrev[b].push_back(a);
    }

    dfs(1);
    dfsrev(1);
    for(int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            cout << "NO\n" << 1 << " " << i << "\n";
            return 0;
        }
        if (!visrev[i]) { 
            cout << "NO\n" << i << " " << 1 << "\n";
            return 0;
        }
    }
    cout << "YES\n";
    return 0;
}
} // end f1

int main() { return f1::main(); }
