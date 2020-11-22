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


// binary lifting based LCA
namespace f0 {
const int N = 1e5*2 + 10;
const int EXP = 32;

int n, q;
int ps[N][EXP];
int depth[N];

vector<int> children[N];

int up(int v, int d) {
    for(int exp = 0; exp < EXP; ++exp) {
        if (d &  (1 << exp)) { v = ps[v][exp];  }
    }
    return v;
}

void dfs(int v, int d) {
    depth[v] = d;
    for(int w : children[v]) { dfs(w, d+1); }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;

    for(int i = 2; i <= n; ++i) {
        int parent; cin >> parent;
        ps[i][0] = parent;
        children[parent].push_back(i);

    }
    ps[1][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int exp = 1; exp < EXP; ++exp) {
            int mid = ps[i][exp - 1];
            ps[i][exp] = ps[mid][exp - 1];
        }
    }


    dfs(1, 1);
    // cerr << "depths: ";
    // for(int i = 1; i <= n; ++i) {
    //     cerr << i << ":" << depth[i] << " \n"[i == n];
    // }
    for(int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;

        int md = min<int>(depth[a], depth[b]);
        a = up(a, depth[a] - md);
        b = up(b, depth[b] - md);
        // cerr << "a equal depth: " << a << " | b: " << b << "\n";

        if (a == b) { cout << a << "\n"; continue; }
        for(int exp = EXP-1; exp >= 0; exp--) {
            if (ps[a][exp] != ps[b][exp]) {
                a = ps[a][exp];
                b = ps[b][exp];
            }
        }
        cout << ps[a][0] << "\n";
    }
    return 0;
}
} // namespace f0.

// euler tour tree based LCA
namespace f1 {
const int N = 2 * 1e5 + 10;
const int INFTY = 1e9;

int n, q;
vector<int> es[N];
int v2time[N];// map vertex to leftmost time occurence
int height[N];
int time2v[4*N]; // map timestamps to vertices
int st[4*(4*N)];
int t0 = 1;

void dfs(int v, int h) {
    time2v[t0] = v;
    v2time[v] = t0;
    t0++;
    height[v] = h;
    for (int w: es[v]) {
        dfs(w, h+1);
        time2v[t0] = v;
        t0++;
    }
}

void build(int t, int l, int r) {
    if (l == r) { st[t] = time2v[l]; return; }
    int mid = (l + r)/2;
    build(t*2, l, mid);
    build(t*2+1, mid+1, r);
    int lix  = st[t*2], rix = st[t*2+1];
    st[t] = height[lix] < height[rix] ? lix : rix;
}

int query(int t, int l, int r, int ql, int qr) {
    // q t t q
    if (ql <= l && r <= qr) { return st[t]; }
    // t t q q | q q t t 
    if (r < ql || qr < l) { return -1; }
    int mid = (l+r)/2;
    int lix = query(t*2, l, mid, ql, qr);
    int rix = query(t*2+1, mid+1, r, ql, qr);
    if (lix == -1) { return rix; }
    if (rix == -1) { return lix; }
    return height[lix] < height[rix] ? lix : rix;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;

    for(int i = 2; i <= n; ++i) {
        int parent; cin >> parent;
        es[parent].push_back(i);
    }
    dfs(1, 1);


    // cerr << "\time2v: |";
    // for(int i = 1; i <= t0; ++i) {
    //     cerr << i << ":"<< time2v[i] << " ";
    // } cerr << "|\n";
    build(1, 1, t0-1);


    for(int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;
        int l =v2time[a], r = v2time[b];
        if (l >= r) std::swap(l, r);
        cout << query(1, 1, t0-1, l, r) << "\n";
    }
    return 0; 
}
}


// binary lifting, no memory wasted:
// https://codeforces.com/blog/entry/74847
namespace f2 {

const int N = 2e5 + 10;
int depth[N]; // number of times needed to walk parent to reach root.
int parent[N];
int jump[N]; // some ancestor.


int ancestorAtDepth(int v, int d) { // jump if we do not overshoot
    while (depth[v] > d) { v = depth[jump[v]] >= d ? jump[v] : parent[v]; }
    return v;
}

void mkleaf(int ix, int p) {
    parent[ix] = p;
    depth[ix] = depth[p] + 1;

    // jumps according to binary representation, interesting.
    // consider:
    // 1 -> 1 | dist=0
    // INS 2 | 2 -1- 1 -0- 1 | create 2 -1- 1
    // INS 3 | 2 -1- 1 -1- 0 | create 3 -2- 1
    // INS 4 | 3 -2- 1 -1- 0 | create 4 -1- 3
    // INS 5 | 4 -1- 3 -2- 1 | create 5 -1- 4
    // INS 6 | 5 -1- 4 -1- 3 | create 6 -2- 4
    // INS 7 | 7 -1- 6 -1- 5 | create 7 -1- 

    if (depth[p] - depth[jump[p]] == depth[jump[p]] - depth[jump[jump[p]]]) {
        jump[ix] = jump[jump[p]];
    } else {
        jump[ix] = p;
    }
}    

int lca(int u, int v) {
  if (depth[u] > depth[v]) {
    return lca(v, u);
  }

  v = ancestorAtDepth(v, depth[u]);

  while (u != v) {
    if (jump[u] == jump[v]) {
      u = parent[u]; v = parent[v];
    } else {
      u = jump[u];
      v = jump[v];
    }
  }
  return u;
}


int main() {

    parent[1] = 1;
    depth[1] = 0;
    jump[1] = 1;

    return 0;
}
};

// binary lifting based LCA, with LCA code written as binary search.
// NOTE: THIS IS INCORRECT, but VERY EDUCATIONAL!
namespace f3 {
const int N = 1e5*2 + 10;
const int EXP = 32;

int n, q;
int ps[N][EXP];
int depth[N];

vector<int> children[N];

int up(int v, int d) {
    for(int exp = 0; exp < EXP; ++exp) if (d &  (1 << exp)) v = ps[v][exp];
    return v;
}

void dfs(int v, int d) {
    depth[v] = d; for(int w : children[v]) { dfs(w, d+1); }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    cin.tie(NULL);
    cin >> n >> q;

    for(int i = 2; i <= n; ++i) {
        int parent; cin >> parent;
        ps[i][0] = parent; children[parent].push_back(i);

    }
    ps[1][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int exp = 1; exp < EXP; ++exp) {
            int mid = ps[i][exp - 1];
            ps[i][exp] = ps[mid][exp - 1];
        }
    }

    dfs(1, 1);
    for(int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;

        int md = min<int>(depth[a], depth[b]);

        // cerr << "\n"; for(int i = 1; i <= n; ++i) { cerr << i << "=" << depth[i]<< " "; } cerr << "\n";
        a = up(a, depth[a] - md);
        b = up(b, depth[b] - md);

        // consider storing distances of : 2^n - 1 ? That way
        // we don't need special case for (a == b).
        if (a == b) { cout << a << "\n"; continue; }
        // cerr <<"a=" << a << "| b=" << b << "\n";


        // PROBLEM: IT MAY NOT BE POSSIBLE TO REACH LCA DIRECTLY FROM ps[a][....]
        // BECAUSE PS[a] ONLY STORES POWERS OF 2!        
        int l = 0, r = EXP-1;
        while (l < r) {
            int mid = (l+r)/2; 
            // cerr << "[" << l << " " << mid << " " << r << "] " << (ps[a][mid] != ps[b][mid]) << "; ";
            if (ps[a][mid] == ps[b][mid]) {
                r = mid; // we want to find first location where predicate is TRUE.
            } else {
                // ps[a][mid] = ps[b][mid]
                l = mid + 1; // we want to find first location where predicate is TRUE.
            }
        }
        // cerr << "FINAL: [" << l << " " << r << "] " << (ps[a][l] != ps[b][l]) << "\n";;
        cout << ps[a][l] << "\n"; 
    }
    return 0;
}
} // namespace f3


// binary lifting based LCA, with LCA code written as *correct* binary search.
namespace f4 {
const int N = 1e5*2 + 10;
const int EXP = 32;

int n, q;
int ps[N][EXP];
int depth[N];

vector<int> children[N];

int up(int v, int d) {
    for(int exp = 0; exp < EXP; ++exp) if (d &  (1 << exp)) v = ps[v][exp];
    return v;
}

void dfs(int v, int d) {
    depth[v] = d; for(int w : children[v]) { dfs(w, d+1); }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    
    cin.tie(NULL);
    cin >> n >> q;

    for(int i = 2; i <= n; ++i) {
        int parent; cin >> parent;
        ps[i][0] = parent; children[parent].push_back(i);

    }
    ps[1][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int exp = 1; exp < EXP; ++exp) {
            int mid = ps[i][exp - 1];
            ps[i][exp] = ps[mid][exp - 1];
        }
    }

    dfs(1, 1);
    for(int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;

        int md = min<int>(depth[a], depth[b]);

        // cerr << "\n"; for(int i = 1; i <= n; ++i) { cerr << i << "=" << depth[i]<< " "; } cerr << "\n";
        a = up(a, depth[a] - md);
        b = up(b, depth[b] - md);

        // consider storing distances of : 2^n - 1 ? That way
        // we don't need special case for (a == b).
        if (a == b) { cout << a << "\n"; continue; }
        // cerr <<"a=" << a << "| b=" << b << "\n";
        while(1) {
            // find first index l such that ps[a][l] == ps[b][l]
            int l = 0, r = EXP-1;
            while (l < r) {
                int mid = (l+r)/2; 
                if (ps[a][mid] == ps[b][mid]) {
                    r = mid; // we want to find first location where predicate is TRUE.
                } else {
                    l = mid + 1; // we want to find first location where predicate is TRUE.
                }
            }
            // if it is direct parent, use it
            if (l == 0) { cout << ps[a][l] << "\n"; break; }
            // otherwise, we might have overshot, because we only contain powers of 2.
            // so, go to just shy of index where agreement happens and use that.
            a = ps[a][l-1];
            b = ps[b][l-1];
        }
    }
    return 0;
}
} // namespace f4




// binary lifting based LCA, RANDOMIZED walk up to LCA.
// AC: https://cses.fi/problemset/result/1280195/
namespace f5 {
const int N = 1e5*2 + 10;
const int EXP = 32;

int n, q;
int ps[N][EXP];
int depth[N];

vector<int> children[N];

int up(int v, int d) {
    for(int exp = 0; exp < EXP; ++exp) if (d &  (1 << exp)) v = ps[v][exp];
    return v;
}

void dfs(int v, int d) {
    depth[v] = d; for(int w : children[v]) { dfs(w, d+1); }
}

int main() {
    srand(0);
    std::ios_base::sync_with_stdio(false);
    
    cin.tie(NULL);
    cin >> n >> q;

    for(int i = 2; i <= n; ++i) {
        int parent; cin >> parent;
        ps[i][0] = parent; children[parent].push_back(i);

    }
    ps[1][0] = 1;
    for(int i = 1; i <= n; ++i) {
        for(int exp = 1; exp < EXP; ++exp) {
            int mid = ps[i][exp - 1];
            ps[i][exp] = ps[mid][exp - 1];
        }
    }

    dfs(1, 1);
    for(int i = 0; i < q; ++i) {
        int a, b; cin >> a >> b;

        int md = min<int>(depth[a], depth[b]);

        // cerr << "\n"; for(int i = 1; i <= n; ++i) { cerr << i << "=" << depth[i]<< " "; } cerr << "\n";
        a = up(a, depth[a] - md);
        b = up(b, depth[b] - md);

        if (a == b) { cout << a << "\n"; continue; }

        // I want to find a parent whose direct ancestor is the LCA.
        while(1) {
            int ix = rand() % 32;
            // NON-LCA.
            if (ps[a][ix] != ps[b][ix]) {
                a = ps[a][ix];
                b = ps[b][ix];
            }

            // LCA.
            if (ps[a][0] == ps[b][0]) {
                cout << ps[a][0] << "\n"; break;
            }
        }
    }
    return 0;
}
} // namespace f5



int main() { return f2::main(); }