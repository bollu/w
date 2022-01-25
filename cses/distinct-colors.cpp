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

using ll = long long;
using namespace std;

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template<typename T>
using minqueue = priority_queue<T,vector<T>,greater<T>>;

template <typename T1, typename T2>
ostream &operator<<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}


// first solution I thought of using DFS; does not work because
// when we enter and exit a left child, we have lost the record that we
// used to have it's color.
namespace f0 {
    const int N = 2 * 1e5 + 10;
    int n;

    int v2color[N];
    int v2ncolors[N];

    vector<int> es[N];

    bool seencolor[N];
    int ncolors;

    void dfs(int u, int v) {
        const bool newcolor = !seencolor[v2color[v]];
        seencolor[v2color[v]] = true; 

        if (newcolor) { ncolors++; }
        for(int w : es[v]) {
            if (u == w) { continue; }
            dfs(v, w);
        }

        v2ncolors[v] = ncolors;
        // include our own color, so decrement after setting num colors.
        if (newcolor) { ncolors--; }
        seencolor[v2color[v]] = false; 
    }


    int main() {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cin >> n;
        set<int> cs;
        map<int, int> c2compress;

        for(int i = 1; i <= n; ++i) {
            int c; cin >> c; v2color[i] = c; cs.insert(c);
        }

        for(int c : cs) {
            if (c2compress.find(c) != c2compress.end()) { continue; }
            c2compress[c] = c2compress.size() + 1;
        }

        for(int i = 1; i <= n; ++i) { v2color[i] = c2compress[v2color[i]]; }

        for(int i = 0; i < n - 1; ++i) {
            int a, b; cin >> a >> b;
            es[a].push_back(b); es[b].push_back(a);
        }

        dfs(1, 1);
        for(int i = 1; i <= n; ++i) {
            cout << v2ncolors[i] << " \n"[i==n];
        }


        return 0;
    }
} // end f0


// just use std::set, but reuse larger set from your children.
// Think of the value at some node in the tree. As it moves upwards to its parents,
// it will always be merged into a set that is in the worst case twice as big as the current set it inhabits.
// The largest set size is $N$. Thus an element moves at most $\log N$ times. There are $N$ elements, so the
// total cost is $N \log N$

namespace f1 {
    static const int N = 2 * 1e5 + 10;
    int v2color[N+1];
    int out[N+1];
    vector<int> adj[N+1];
    set<int> *data[N+1];;
    bool visited[N+1];

    void visit(int v, int parent) {
        if (visited[v]) { return; }
        visited[v] = true;

        // fprintf(stderr, "visit(%d, parent:%d)\n", v, parent);

        if (adj[v].size() == 1 && adj[v][0] == parent) {
            data[v] = new set<int>();
            data[v]->insert(v2color[v]);
        } else {
            assert(adj[v].size() > 0);
            int wheavy = -1;
            for(int i = 0; i < adj[v].size(); ++i) {
                int w = adj[v][i];
                if (w == parent) { continue; }
                visit(w, v);
                if (wheavy == -1 || data[w]->size() > data[wheavy]->size())  {
                    wheavy = w;
                }
            }

            data[v] = data[wheavy];
            assert(data[v]);
            data[v]->insert(v2color[v]);
            // steal heaviest for log merging.
            for(int i = 0; i < adj[v].size(); ++i) {
                int w = adj[v][i];
                if (w == parent || w == wheavy) { continue; }
                data[v]->insert(data[w]->begin(), data[w]->end());
            }
        }
        assert(data[v]);
        out[v] = data[v]->size();
    }

    int main() {
        int n; cin >> n;
        for(int i = 1; i <= n; ++i) {
            cin >> v2color[i];
        }
        for(int i = 0; i < n - 1; ++i) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b); adj[b].push_back(a);
        }
        visit(1, 1);
        for(int i = 1; i <= n; ++i) {
            cout << out[i] << " ";
        }
        return 0;
    }
}

// Mo's algorithm on paths: https://codeforces.com/blog/entry/43230
int main() { return f1::main(); }
