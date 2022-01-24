#include<iostream>
#include <vector>
#include <assert.h>
using namespace std;

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
void go_heavy_parent(int v, int parent, int hp) {
    heavy_parent[v] = hp;
    for(int child : adj[v]) {
        if (child == parent) { continue; }
        if (child == heavy[v]) {
            go_heavy_parent(child, v, hp);
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

int query(int ix, int stix, int stl, int str) {
    fprintf(stderr, "query(ix=%4d,stix=%4d,stl=%4d,str=%4d)\n", ix, stix, stl, str);
    assert(stl <= str);
    assert(stl <= ix);
    assert(ix <= str);
    if (stl == str) {
        assert(stix == stl);
        return st[stix];
    }
    int stmid = (stl + str)/2;
    if (ix <= stmid) {
        return st[stix] + query(ix, stix*2, stl, stmid);
    } else {
        return st[stix] + query(ix, stix*2+1, stmid, str);
    }

}

void increment(int ql, int qr, int stix, int stl, int str) {
    fprintf(stderr, "increment(ql=%4d,qr=%4d,stix=%4d, stl=%4d,str=%4d)\n", ql, qr, stix, stl, str);
    assert(stl <= str);
    assert(ql <= qr);
    if (ql <= stl && str <= qr) {
        st[stix] += 1;
        return;
    }
    if (qr < stl || str < ql) { return; }

    int stmid = (stl + str)/2;
    increment(ql, qr, stix*2, stl, stmid);
    increment(ql, qr, stix*2+1, stmid+1, str);
}


// TODO: this is very subtle. Meditate on why this works.
void incpath(int u, int v) {
    while(1) {
        int up = heavy_parent[u];
        int vp = heavy_parent[v];
        // they are in same chain, so add them up and stop.
        if (up == vp) {
            int l = min(v2ix[up], v2ix[vp]);
            int r = max(v2ix[up], v2ix[vp]);
            increment(l, r, 1, 1, n);
            return;
        } else {
            if (depth[up] > depth[vp]) {
                increment(v2ix[up], v2ix[u], 1, 1, n);
                u = up;
            } else {
                increment(v2ix[vp], v2ix[v], 1, 1, n);
                v = vp;
            }

        }
    }
}


int main() {
    cin >> n >> m;

    for(int i = 0; i < n - 1; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        printf("edge %4d <-> %4d\n", u, v);
    }


    dfs(1, 1, 1); // run DFS
    go_ixs(1, 1);
    go_heavy_parent(1, 1, 1);


    for(int i = 0; i < m; ++i) {
        int s, t;
        cin >> s >> t;
        printf("path increment %4d -- %4d\n", s, t);
        incpath(s, t);
    }

    for(int i = 1; i <= n; ++i) {
        cout << query(v2ix[i], 1, 1, n);
    }

    return 0;
}

