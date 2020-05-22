#include <vector>
#include <tuple>
#include <assert.h>
const int INF=1000000;
using namespace std;
int n;
vector<vector<int>> capacity;
vector<vector<int>> adj;

int bfs(int s, int t, vector<int>& pred) {
    fill(pred.begin(), pred.end(), -1);
    pred[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (pred[next] == -1 && capacity[cur][next]) {
                pred[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t) return new_flow;
                q.push({next, new_flow});
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    vector<int> pred(n);
    int new_flow;

    while (new_flow = bfs(s, t, pred)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = pred[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}
