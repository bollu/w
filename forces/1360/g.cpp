#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <limits>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <functional>
using namespace std;
/*
#define forn(i, s, f) for (int i = (int)s; i < (int)f; i++)
#define ll long long
#define ull unsigned long long
#define ld long double
#define pii pair <int, int>
#define fs first
#define sc second
#define pf push_front
#define pb push_back
#define pop_f pop_front
#define pop_b pop_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define sz(x) (int)(x).size()


template <typename T> istream& operator>>(istream& in, vector <T>& a) {for (auto& i : a) in >> i; return in;}
template <typename T> ostream& operator<<(ostream& out, vector <T>& a)  {for (auto& i : a) out << i << " "; return out;}
template <typename T, typename U> void chkmin(T& a, U b) {if (a > b) a = b;}
template <typename T, typename U> void chkmax(T& a, U b) {if (a < b) a = b;}
 
template <typename T> 
class Max_flow {
private:
    struct Edge {
        int v, u, idx;
        T c, f;
    };
 
    const int INF = 1e9;
    vector <vector <int>> gr;
    vector <Edge> e;
    vector <int> dst;
 
    bool bfs(int s, int t) {
        dst = vector <int> (sz(gr), INF);
        dst[s] = 0;
        deque <int> q = {s};
        while (!q.empty()) {
            int v = q.front();
            q.pop_front();
            for (int i : gr[v]) {
                int u = e[i].u;
                T c = e[i].c, f = e[i].f;
                if (c - f > 0 && dst[v] + 1 < dst[u]) {
                    q.pb(u);
                    dst[u] = dst[v] + 1;
                }
            }
        }
        return dst[t] < INF;
    }
 
    vector <int> lst;
 
    T dfs(int v, int t, T delta) {
        if (v == t || delta == 0)
            return delta;
        for (; lst[v] < sz(gr[v]); ++lst[v]) {
            int i = gr[v][lst[v]];
            int u = e[i].u;
            T c = e[i].c, f = e[i].f;
            if (dst[u] == dst[v] + 1 && c - f > 0) {
                if (T cur_delta = dfs(u, t, min(delta, c - f))) {
                    e[i].f += cur_delta;
                    e[i ^ 1].f -= cur_delta;
                    return cur_delta;
                }
            }
        }
        return 0;
    }
 
    T find_path(int s, int t, vector <vector <int>>& paths) {
        vector <bool> used(sz(gr));
        deque <int> edges;
        int v = s;
        while (!used[v] && v != t) {
            used[v] = true;
            int nxt = -1;
            for (int i : gr[v]) {
                int u = e[i].u;
                T f = e[i].f;
                if (f > 0) {
                    nxt = i;
                    break;
                }
            }
            if (nxt == -1)
                return 0;
            edges.pb(nxt);
            v = e[nxt].u;
        }
        if (used[v])
            while (e[edges[0]].v != v)
                edges.pop_front();
        T delta = numeric_limits<T>::max();
        for (int i : edges)
            chkmin(delta, e[i].f);
        for (int i : edges) {
            e[i].f -= delta;
            e[i ^ 1].f += delta;
        }
        if (!used[v]) {
            paths.pb({});
            paths.back().pb(e[0].v);
            for (auto i : edges)
                paths.back().pb(e[i].u);
        }
        return delta;
    }
 
public:
    Max_flow(int _n) {
        gr.resize(_n);
    }
 
    T dinic(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            lst = vector <int> (sz(gr));
            while (T cur = dfs(s, t, numeric_limits<T>::max()))
                ans += cur;
        }
        return ans;
    }
 
    vector <vector <int>> decompose(int s, int t) {
        vector <vector <int>> paths;
        while (find_path(s, t, paths));
        return paths; 
    }
 
    void add_edge(int v, int u, T c, int i = -1) {
        gr[v].pb(sz(e));
        e.pb({v, u, i, c, 0});
        gr[u].pb(sz(e));
        e.pb({u, v, i, 0, 0});
    }
};

*/

static const int N = 120;
static const int UNVISITED=0;
static const int S = N-2;
static const int T = N-3;
static const int INFTY = 500;
int cap[N][N];
int flow[N][N];
int pred[N];
int totalflow;

int n, m, a, b;

bool augmentpath() {
    int vs[N]; int vp = 0;
    memset(pred, 0, sizeof(pred));

    vs[vp++] = S;
    pred[S] = (-1);
    while(vp > 0) {
        const int u = vs[--vp];
        // cout << "(considering:" << u << ")\n";

        if (u == T) { return true; }

        for(int v = 1; v < N; ++v) {
            // cout << "(" << u << " --(" << cap[u][v] << ")-->? " << v << ")\n";
            if (cap[u][v]  - flow[u][v] > 0 && !pred[v]) {
                // cout << "(" << u << " -> " << v << ")\n";
                pred[v] = u;
                vs[vp++] = v;  // push v to stack.
            }
        }
    }

    return false;
}

void solve() {
    cin >> n >> m >> a >> b;
    memset(cap, 0, sizeof(cap));
    memset(flow, 0, sizeof(flow));
    memset(pred, 0, sizeof(pred));
    totalflow = 0;

    for (int r = 1; r <= n; ++r) { 
        for(int c = n+1; c <= n + m; ++c) { 
            cap[S][r] = a;
            cap[r][c] = 1;
            cap[c][T] = b;
        }
    }

    while(augmentpath()) {
        // cout << "*augmenting...\n";
        // send flow
        int flo = INFTY;
        for(int v = T; v != S; v = pred[v]) { flo = min<int>(flo, cap[pred[v]][v] - flow[pred[v]][v]); }
        assert(flo > 0);
        totalflow += flo;
        for(int v = T; v != S; v = pred[v]) {
            flow[pred[v]][v] += flo;
            flow[v][pred[v]] -= flo;
        }
    }
    
    char ans[N][N];
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            ans[i][j] = '0';
        }
    }

    for (int r = 1; r <= n; ++r) { 
        for(int c = n+1; c <= n + m; ++c) { 
            if (flow[r][c] > 0) {
                ans[r-1][c-n-1] = '1';
            }
        }
    }

    // In this case, we can satisfy the row condition, not the column condition.
    // The reason this is a good condition is that we need.
    // 22 25 1 11
    if (n*a != m*b) { cout << "NO\n"; }
    else if (totalflow != n * a) { cout << "NO\n"; }
    else {
        cout << "YES\n";
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) { cout << ans[i][j]; }
            cout << "\n";
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while (t --) { solve(); }
    return 0;
}
