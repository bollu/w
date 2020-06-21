#include <iostream>
#include <queue>
#include <tuple>
#include <utility>
#include <functional>
#include <set>
using TIME = int;

using namespace std;
#define N 1000000

vector<int> es[N];
int ts[N];
vector<int> topic2vs[N];
set<int> topics;
bool visited[N];

bool cycvisted[N];

/*
void bfs(int n) {
    for(int v : topic2vs[1]) {
        queue<int> q;
        q.push(v);

        while(!q.empty()) {
            int w; w= q.front(); q.pop();

            cout << w << " ";
            visited[w] = true;
            for(int x: es[w]) { if (ts[x] == ts[w] + 1 && !visited[x]) { q.push(x); } }
        }
    }
}
*/

bool hascycle(int n) {
    for(int i = 1; i <= n; ++i) {
        if (cycvisted[i]) continue;
        queue<int> q;
        q.push(cycvisted[i]);

        while(!q.empty()) {
            int cur = q.front(); q.pop();
            if (cycvisted[cur]) { return true; }
            cycvisted[cur] = true;
            for(int next : es[cur]) { q.push(next); }

        }
    }
}


int main() {
    int n, m; cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        int a, b;
        cin >> a >> b;
        es[a].push_back(b);
        es[b].push_back(a);
    }


    for(int i = 1; i <= n; ++i) {
        int ti ; cin >> ti;
        topic2vs[ti].push_back(i);
        topics.insert(ti);
        ts[i] = ti;
    }

    // for each topic, check that the node has a node adjacent to it
    // of topic t-1
    bool possible = true;
    for(int v = 1; v <= n; ++v) {
        set<int> counts;
        for(int w : es[v]) {
            if (ts[v] == ts[w]) { possible = false; break; }
            if (ts[w] < ts[v]) { counts.insert(ts[w]); }
        }

        if (!(counts.size() == ts[v] - 1)) {  possible = false; break; }
        /*

        if (!possible) { break; }

        bool hasadj = false;
        if (ts[v] == 1) { hasadj = true; break; }
        for(int w : es[v]) {
            if (ts[w] == ts[v] - 1) { hasadj = true; break; }
        }
        if (!hasadj) { possible = false; break; }
        */
    }

    if (!possible) { cout << -1; }
    else {
        // bfs(n);

         for(auto t: topics) {
             for(auto v: topic2vs[t]) { cout << v<< " "; }
         }
    }

    return 0;
}
