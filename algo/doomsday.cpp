// https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/doomsday/
// https://www.hackerearth.com/submission/34759648/
#include <iostream>
#include<cmath>
#include<vector>
#include<tuple>
#include<queue>
using namespace std;
using I=int; const I INF = 1000000000L; const I N = 105;
#define DO(i,n,SSS) for(int i=1;i<=n;++i) SSS
// SRC -(POP)-> CITY m -(REACHABLE IN T)-> CITY n -(NPODS)-> SINK
const int SRC = 102, SINK = 103; 
vector<int> adj[N]; int cap[N][N];
int pred[N];
int D[N][N]; /*distances */
int n, e, x;
void apsp() {
    DO(i, n, DO(j, n, DO(k, n, D[i][k] = min(D[i][k], D[i][j] + D[j][k]))));
}
int getflow() {
    DO(i, N-1, pred[i] = -1); pred[SRC] = -2; // src is inaccessible.

    queue<pair<int, int>> q;
    q.push({SRC, INF});

    while(!q.empty()) {
        const int u = q.front().first; const int s2u = q.front().second;
        q.pop();


        for(auto v: adj[u]) {
          const int u2v = cap[u][v];
            if (pred[v] == -1 && u2v != 0) {
                const int f = min(s2u, u2v);
                pred[v] = u;
                if (v == SINK) return f;
                q.push({v, f});
            }
        }
    }
    return 0;
}

int maxflow() {
    int mf = 0;
    int curflow;
    while(curflow = getflow()) {
        // cout << "curflow: " << curflow << "\n";
        mf += curflow;
        for(int v = SINK; v != SRC; v = pred[v]) {
            int u = pred[v];
            cap[u][v] -= curflow;
            cap[v][u] += curflow;
        }
    }
    return mf;
}
int main() {
    int totpop = 0;
    cin >> n >> e >> x;
    DO(i, n, DO(j, n, D[i][j] = INF));
    DO(i, n, DO(j, n, cap[i][j] = 0));
    DO(i, n, { int w; cin >> w; totpop += w; adj[SRC].push_back(i); adj[i].push_back(SRC); cap[SRC][i] = w; });
    DO(i, n, { int w; cin >> w; adj[i].push_back(SINK); adj[SINK].push_back(i); cap[i][SINK] = w; });

    DO(i, e, { int u; int v; cin >> u >> v; cin >> D[u][v]; });

    apsp();
    DO(i, n, DO(j, n,if (D[i][j] <= x) { 
        // cout << "D[" << i << "][" << j << "] <= " << x << "\n";
        adj[i].push_back(j); adj[j].push_back(i); cap[i][j] = cap[j][i] = INF;
        }));
    const int die = totpop - maxflow();
    cout << die << "\n";
    return 0;
}
