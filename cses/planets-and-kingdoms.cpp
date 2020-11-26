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

// Implement *incorrect* algorithm to understand where it breaks
namespace f0 {
const int N = 1e5 + 10;
bool vis[N];
vector<int> es[N];
vector<int> exitvs; // vertices pushed back as we exit.

void dfs(int v)  {
    cerr << "ENTER: " << v << "\n";
    vis[v] = true;
    for(int w : es[v]) {
        if (vis[w]) { continue; } dfs(w);
    }
    exitvs.push_back(v);
    cerr << "EXIT: " << v << "\n";
}
vector<int> esrev[N];
bool visrev[N];

int comp[N];
void dfsrev(int v, int c)  {
    if (visrev[v]) return; 
    comp[v] = c;
    visrev[v] = true;
    for(int w: es[v]) {
    // for(int w : esrev[v]) {
        if (visrev[w]) { continue; } dfsrev(w, c);
    }
}

int n, m;

// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
// https://www.youtube.com/watch?v=9Wbej7Fy5Lw
// https://www.youtube.com/watch?v=iYJqgMKYsdI
// https://www.iarcs.org.in/inoi/online-study-material/topics/scc.php
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
        esrev[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) { if (!vis[i]) { dfs(i); } }


    cerr << "exitvs: ";
    for(int i = 0; i < exitvs.size(); i++) { cerr << exitvs[i] << " "; } 
    cerr << "\n";

   // a<->b->c<->d
   // DFS from a: a -> b -> c -> d
   // reverse: d will be a final SCC component.
   // will find d<->c
   // remove d, c.
   // next will find b. will do b<->a 
    for(int i = 0; i < exitvs.size(); i++) {
        int v = exitvs[i];
        if (!visrev[v]) { dfsrev(v, v); }
    }

    map<int, int> comp2ix;
    for(int i = 1; i <= n; ++i) {
        auto it = comp2ix.find(comp[i]);
        if (it == comp2ix.end()) {
            comp2ix[comp[i]] =  comp2ix.size()+1;
        }
    }

    cout << comp2ix.size() << "\n";
    for(int i = 1; i <= n; ++i) {
        cout << comp2ix[comp[i]] << " \n"[i==n];
    }

    return 0;
}
} // end f0


// Correct algorithm, is accepted.
namespace f1 {
const int N = 1e5 + 10;
bool vis[N];
vector<int> es[N];
vector<int> exitvs; // vertices pushed back as we exit.

void dfs(int v)  {
    // cerr << "ENTER: " << v << "\n";
    vis[v] = true;
    for(int w : es[v]) {
        if (vis[w]) { continue; } dfs(w);
    }
    exitvs.push_back(v);
    // cerr << "EXIT: " << v << "\n";
}
vector<int> esrev[N];
bool visrev[N];

int comp[N];
void dfsrev(int v, int c)  {
    if (visrev[v]) return; 
    comp[v] = c;
    visrev[v] = true;
    // for(int w: es[v]) {
    for(int w : esrev[v]) {
        if (visrev[w]) { continue; } dfsrev(w, c);
    }
}

int n, m;

// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
// https://www.youtube.com/watch?v=9Wbej7Fy5Lw
// https://www.youtube.com/watch?v=iYJqgMKYsdI
// https://www.iarcs.org.in/inoi/online-study-material/topics/scc.php
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
        esrev[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) { if (!vis[i]) { dfs(i); } }


    // 1 2 3 4 5 -> 5 4 3 2 1 : last to exit is first in exitvs
    std::reverse(exitvs.begin(), exitvs.end());

    for(int i = 0; i < exitvs.size(); i++) {
        int v = exitvs[i];
        if (!visrev[v]) { dfsrev(v, v); }
    }

    map<int, int> comp2ix;
    for(int i = 1; i <= n; ++i) {
        auto it = comp2ix.find(comp[i]);
        if (it == comp2ix.end()) {
            comp2ix[comp[i]] =  comp2ix.size()+1;
        }
    }

    cout << comp2ix.size() << "\n";
    for(int i = 1; i <= n; ++i) {
        cout << comp2ix[comp[i]] << " \n"[i==n];
    }

    return 0;
}
} // end f1


// Reverse everything about the correct algorithm. Checking if it's still
// accepted.
namespace f2 {
const int N = 1e5 + 10;
bool vis[N];
vector<int> es[N];
vector<int> exitvs; // vertices pushed back as we exit.
vector<int> esrev[N];
bool visrev[N];
int comp[N];

void dfs(int v)  {
    vis[v] = true;
    // for(int w: es[v]) {
    for(int w : esrev[v]) {
        if (vis[w]) { continue; } dfs(w);
    }
    exitvs.push_back(v);
}

void dfsrev(int v, int c)  {
    if (visrev[v]) return; 
    comp[v] = c;
    visrev[v] = true;
    for(int w: es[v]) {
    // for(int w : esrev[v]) {
        if (visrev[w]) { continue; } dfsrev(w, c);
    }
}

int n, m;

// https://www.hackerearth.com/practice/algorithms/graphs/strongly-connected-components/tutorial/
// https://www.youtube.com/watch?v=9Wbej7Fy5Lw
// https://www.youtube.com/watch?v=iYJqgMKYsdI
// https://www.iarcs.org.in/inoi/online-study-material/topics/scc.php
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
        esrev[b].push_back(a);
    }

    for(int i = 1; i <= n; ++i) { if (!vis[i]) { dfs(i); } }


    // 1 2 3 4 5 -> 5 4 3 2 1 : last to exit is first in exitvs
    std::reverse(exitvs.begin(), exitvs.end());

    for(int i = 0; i < exitvs.size(); i++) {
        int v = exitvs[i];
        if (!visrev[v]) { dfsrev(v, v); }
    }

    map<int, int> comp2ix;
    for(int i = 1; i <= n; ++i) {
        auto it = comp2ix.find(comp[i]);
        if (it == comp2ix.end()) {
            comp2ix[comp[i]] =  comp2ix.size()+1;
        }
    }

    cout << comp2ix.size() << "\n";
    for(int i = 1; i <= n; ++i) {
        cout << comp2ix[comp[i]] << " \n"[i==n];
    }

    return 0;
}
} // end f2

// tarjan's algorithm.
namespace f3 {
const int N = 1e5 + 10;
int n, m;
vector<int> es[N];
int ixs[N];
int lowlink[N];
stack<int> S;
int index = 1;

int ncomps;
int comps[N];

    // a node remains on the stack after it has been visited if and only if
    // there exists a path in the input graph from it to some node earlier on
    // the stack
    void ssc(int v) {
        ixs[v] = lowlink[v] = index;
        index++;
        S.push(v);

        for(int w : es[v]) {
            // unvisited
            if (!ixs[w]) { 
                ssc(w);
                lowlink[v]  = min<int>(lowlink[v], lowlink[w]);
            }
            // visited; unSSC'd.
            else if (!comps[w]) {
                // w is in current SSC
                // if w is not on stack then (v, w) points to an existing
                // SSC, must be ignored [because it is in the condensation DAG?]
                lowlink[v] = min<int>(lowlink[v], ixs[w]);
            }
        }

        if (lowlink[v] == ixs[v]) {
            ncomps++;
            while (1) {
                int w = S.top(); S.pop();
                comps[w] = ncomps;
                if (w == v) { break; }
            }
        }
    }

    void tarjanssc() {
        for(int i = 1; i <= n; ++i) {
            if (ixs[i] == 0) { ssc(i); }
        }
    }

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);
    }

    tarjanssc();

    cout << ncomps << "\n";
    for(int i = 1; i <= n; ++i) {
        cout << comps[i] << " \n"[i==n];
    }
    return 0; 
}
} // end f3

int main() { return f3::main(); }

// a<->b -> c<->d
//     |      |
//     v      v     
//     e<---->f

// dfs visit: (a (b (e (f f) e) (c (d d) c) b) a)
// exit times: f e d c b a
// f e; d c; b a


// FAILURE!
// 1 2
// 2 3
// 3 1
// 1 4
//
// 1
// 1 1 1 1
// d<---- a -> b
//        ^    |
//        |    v
//        *-c--*
// dfs visit:  (a (d d) (b (c c) b) a) | exit order: d c b a | CORRECT!
// dfs visit:  (a (b (c c) b) (d d) a) | exit order: c b d a | 
//             start DFS from c: c, d, a, b. Will find everything!
//             But this is incorrect. It's because the DFS "leaks out"


// smaller counterexample:
// 3 3
// 1 2
// 2 1
// 1 3
// a<->b->c | [a->b->c] vs  [b->a; c] or [b->c; a]
// ENTER: 1
// ENTER: 2
// EXIT: 2
// ENTER: 3
// EXIT: 3
// EXIT: 1
// exitvs: 2 3 1
// 1
// 1 1 1

// Need to know which vertex to start from.
// Document with proof: https://timroughgarden.org/w11/l/scc.pdf
