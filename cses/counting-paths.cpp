#include<iostream>
#include <vector>
#include <assert.h>
using namespace std;

#define LOG 
// #define LOG fprintf
// https://cses.fi/problemset/task/1136
const int N = 2 * 1e5 + 10;
// tree_value[a] = sum_{d : descentand(a)} v2contrib[a]

int n, m;
vector<int> adj[N];
int sz[N]; // subtree sizes
int heavy[N]; // heavy child of node.
int heavy_parent[N]; // parent at top of heavy chain
int st[4*N];
int v2ix[N];
int depth[N];
int parent[N]; // parent node of child

// run a dfs and identify heavy nodes.
// this initialies heavy, sz, depth
void dfs(int v, int vparent, int vdepth) {
    sz[v] += 1;
    parent[v] = vparent;
    depth[v] = vdepth;
    int nchildren = 0;
    for(int child : adj[v]) {
        if (child == vparent) { continue; }
        nchildren++;
        dfs(child, v, vdepth+1);
        sz[v] += sz[child];
    }

    // leaf
    if (nchildren == 0) {
        heavy[v] = v; return;
    }

    // non leaf.
    heavy[v] = -1;
    for(int child : adj[v]) {
        if (child == vparent) { continue; }
        if (heavy[v] == -1 || sz[child] > sz[heavy[v]]) {
            heavy[v] = child;
        }
    }
    assert(heavy[v] != -1);
}

// for each v, intialize heavy_parent which is the vertex
// that is at the top of the heavy chain v belongs to.
// hp is the heavy parent of node v.
// this initialize heavy_parent.
void go_heavy_parent(int v, int v_parent, int v_heavy_parent) {
    heavy_parent[v] = v_heavy_parent;
    for(int child : adj[v]) {
        if (child == v_parent) { continue; }
        if (child == heavy[v]) {
            go_heavy_parent(child, v, v_heavy_parent);
        } else {
            // child starts a new heavy
            // Singletons live in their own node.
            go_heavy_parent(child, v, child); 
        }
    }
}

// assign indexes such that all heavy paths occur
// as a contiguous segment in the large segment tree.
// https://www.youtube.com/watch?v=_S1CQ5g9uTg&list=PLrS21S1jm43igE57Ye_edwds_iL7ZOAG4&index=27
// this initializes v2ix
int go_ixs(int v, int freeix) {
    v2ix[v] = freeix;
    freeix += 1;
    // leaf
    if (v == heavy[v]) { return freeix; }

    freeix = go_ixs(heavy[v], freeix);
    for(int child : adj[v]) {
        if (child == parent[v] || child == heavy[v]) { continue; }
        freeix = go_ixs(child, freeix);
    }
    return freeix;
}

// A(pex)
/// \
//B  C
//<----> array
int query(int i, int apex, int b, int c) {
    // fprintf(stderr, "query(i=%4d,apex=%4d,b=%4d,c=%4d)\n", i, apex, b, c);
    assert(b <= c);
    assert(b <= i);
    assert(i <= c);
    if (b == c) {
        return st[apex];
    }
    int mid = (b + c)/2;
    if (i <= mid) {
        return st[apex] + query(i, apex*2, b, mid);
    } else {
        return st[apex] + query(i, apex*2+1, mid+1, c);
    }

}

void increment(int l, int r, int apex, int b, int c) {
    // fprintf(stderr, "increment(l=%4d,r=%4d,apex=%4d, b=%4d,c=%4d)\n", l, r, apex, b, c);
    assert(b <= c);
    assert(l <= r);
    // [l [b c] r]
    if (l <= b && c <= r) {
        st[apex] += 1;
        return;
    }
    //[l r] [b c] [l r]
    if (r < b || c < l) { return; }

    int mid = (b + c)/2;
    increment(l, r, apex*2, b, mid);
    increment(l, r, apex*2+1, mid+1, c);
}


// TODO: this is very subtle. Meditate on why this works.
void incpath(int u, int v) {
    while(1) {
        int up = heavy_parent[u];
        int vp = heavy_parent[v];
        // they are in same chain, so add them up and stop.
        if (up == vp) {
            int l = min(v2ix[u], v2ix[v]);
            int r = max(v2ix[u], v2ix[v]);
            // fprintf(stderr, "  increment(%2d, %2d).\n", l, r);
            increment(l, r, 1, 1, n);
            return;
        } else {
            // decrease depth.
            if (depth[up] > depth[vp]) {
                increment(v2ix[up], v2ix[u], 1, 1, n);
                // fprintf(stderr, "  increment(%2d, %2d)", v2ix[up], v2ix[u]);
                u = parent[up];
            } else {
                increment(v2ix[vp], v2ix[v], 1, 1, n);
                // fprintf(stderr, "  increment(%2d, %2d)", v2ix[vp], v2ix[v]);
                v = parent[vp];
            }
        }
    }
}


int main() {
    cin >> n >> m;

    // fprintf(stderr, "\nedges:\n");
    for(int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        // fprintf(stderr, "  %2d <-> %2d;", u, v);
    }


    dfs(1, 1, 1); // run DFS
    go_ixs(1, 1);
    go_heavy_parent(1, 1, 1);

    // fprintf(stderr, "\nheavy child:\n");
    // for(int i = 1; i <= n; ++i) {
    //     fprintf(stderr, "  %2d -> %2d;", i, heavy[i]);
    // }

    // fprintf(stderr, "\nheavy parent:\n");
    // for(int i = 1; i <= n; ++i) {
    //     fprintf(stderr, "  %2d -> %2d;", i, heavy_parent[i]);
    // }

    // fprintf(stderr, "\nparent:\n");
    // for(int i = 1; i <= n; ++i) {
    //     fprintf(stderr, "  %2d -> %2d;", i, parent[i]);
    // }

    // fprintf(stderr, "\ndepth:\n");
    // for(int i = 1; i <= n; ++i) {
    //     fprintf(stderr, "  %2d -> %2d;", i, depth[i]);
    // }

    // fprintf(stderr, "\nix:\n");
    // for(int i = 1; i <= n; ++i) {
    //     fprintf(stderr, "  %2d -> %2d", i, v2ix[i]);
    // }
    // fprintf(stderr, "\n");


    for(int i = 0; i < m; ++i) {
        int s, t;
        cin >> s >> t;
        // fprintf(stderr, "path increment(%2d, %2d)\n", s, t);
        incpath(s, t);
    }

    for(int i = 1; i <= n; ++i) {
        cout << query(v2ix[i], 1, 1, n) << " ";
    }
    return 0;
}

