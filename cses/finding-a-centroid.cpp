#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <functional>
#include <stack>
using namespace std;

// Wrong solution, based on incorrect intuition that
// node at the center of the diameter will be a centroi.
namespace f0 {

    const int N = 2 * 1e5 + 10;
    int vstar1; int vstar2;
    int dist1[N];
    int dist2[N];
    int farthest2;
    int parent2[N];
    int parent1[N];
    vector<int> adj[N];

    void dfs1(int v, int parent, int dist) {
        if (parent1[v]) { return; }
        dist1[v] = dist;
        parent1[v] = parent;

        if (!vstar1 || dist1[v] > dist1[vstar1]) {
            vstar1 = v;
        }

        for(int w : adj[v]) {
            if (w == parent) { continue; }
            dfs1(w, v, dist+1);
        }
    }

    void dfs2(int v, int parent, int dist) {
        if (parent2[v]) { return; }
        dist2[v] = dist;
        parent2[v] = parent;
        if (!vstar2 || dist2[v] > dist2[vstar2]) {
            vstar2 = v;
        }

        for(int w : adj[v]) {
            if (w == parent) { continue; }
            dfs2(w, v, dist+1);
        }

    }

    void bfs(int root, int *parents, int *dists, int &vstar ) {
        static int count = 0; count++;
    // TODO: what control flow structure permits queues?
        queue<tuple<int, int, int>> q;
        vstar = root;
        q.push(std::tuple<int, int, int>(root, root, 0));
        while(q.size()) {
            int cur; int parent; int dist;
            std::tie(cur, parent, dist) = q.front(); q.pop();
            if (parents[cur] != 0) { continue; }
            fprintf(stderr, "  bfs%d (cur=%2d, parent=%2d, dist=%2d)\n", count, cur, parent, dist);
            parents[cur] = parent;
            dists[cur] = dist;
            if (dists[vstar] <= dists[cur]) { vstar = cur; }

            for(int next : adj[cur]) {
                q.push(std::tuple<int, int, int>(next, cur, dist+1));
            }
        }
    }

    int  main() {
        int n; cin >> n;
        for(int i = 0; i < n-1; ++i) {
            int a, b; cin >> a >> b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }

        bfs(1, parent1, dist1, vstar1);
        bfs(vstar1, parent2, dist2, vstar2);
        fprintf(stderr, "v1*=%2d; v2*=%2d\n", vstar1, vstar2);
        int centroid = vstar2;
    // 0-1=2 => 2/2 = 1 iteration
    // 0-1-2=3 => 3/2 = 1 iteration
    // 0-1-2=3=4 => 4/2 = 2 iterations
        for(int d = 0; d < dist2[vstar2]/2; d++) {
            centroid = parent2[centroid];
        }

        cout << centroid << "\n";
        return 0;
    }

}

namespace f1 {
    static const int N = 2e5 + 10;
    vector<int> es[N];
    int sz[N];
    int parents[N];
    int main() {
        int n; cin >> n;
        for(int i = 0; i < n - 1; ++i) {
            int a, b; cin >> a >> b;
            es[a].push_back(b);
            es[b].push_back(a);
        }

        stack<pair<int, int>> dfs;
        dfs.push({1, 1});
        stack<int> sizes;
        while (dfs.size()) {
            int v, parent;
            std::tie(v, parent) = dfs.top(); dfs.pop();
            parents[v] = parent;
            // queue for size computation
            sizes.push(v);
            if (es[v].size() == 1 && es[v].front() == parent){
                // leaf
                continue;
            } else { // non leaf
                for(int w : es[v]) {
                    if (w == parents[v]) { continue; }
                    dfs.push({w, v});
                }
            }
        }

        while(sizes.size()) {
            int v = sizes.top(); sizes.pop();
            sz[v] += 1;
            for(int w : es[v]) {
                if (w == parents[v]) { continue; }
                sz[v] += sz[w];
            }
        }

        int centroid = 1;
        while(1) {
            bool success = true;
            for(int v : es[centroid]) {
                int vsz = v == parents[centroid] ? (n - sz[centroid]) : sz[v];
                if (vsz > n/2) {
                    success = false;
                    centroid = v;
                    break;
                }
            }
            if (success) { break; }
        }

        cout << centroid << "\n";
        return 0;
    }
}


int main() {
    f1::main();
}


