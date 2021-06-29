// https://codeforces.com/contest/1540/submission/120565342
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;
ll MOD = 1e9 + 7;


ll residue(ll i) {  return ((i % MOD) + MOD) % MOD; }
ll mul(ll i, ll j) { return (i * j) % MOD; }
ll add(ll i, ll j) { return (i + j) % MOD; }
ll sub(ll i, ll j) { ll out = (i - j) % MOD; if (out < 0) { return out + MOD; } return out; }

ll pow(ll x, ll n) {
    if (n == 0) { return 1; }
    if (n == 1) { return x; }
    if (n % 2 == 0) {
        ll y = pow(x, n/2); return mul(y, y);
    } else {
        n--;
        ll y = pow(x, n/2);
        return mul(mul(y, y), x);
    }
}
ll inv(ll x) { return pow(x, MOD - 2); }
ll frac(ll p, ll q) { return mul(residue(p), inv(residue(q))); }
int half = frac(1, 2);
int two = frac(2, 1);

const int N = 200+5;
static const int LOGN = 9;
int n;
vector<int> es[N];

int dp[N][N];

int ds1[N], ds2[N];
int parent[N][LOGN];


void bfs(int root, int *dists, bool *visited) {
    assert(!visited[root]);
    dists[root] = 0;
    queue<int> q;
    q.push(root);

    while(!q.empty()) {
        int v = q.front(); q.pop();
        assert(!visited[v]); 
        visited[v] = true;
        for(auto c : es[v]) {
            if (visited[c]) { continue; }
            parent[c][0] = v;
            dists[c] = dists[v] + 1;
            q.push(c); 
        }
    }
}

// dp[x][y] probability to reach left before right if x is depth to left, y is depth to right
void calcdp(){
    for(int l = 0; l < N; ++l) { dp[l][0] = 0; }
    for(int r = 0; r < N; ++r) { dp[0][r] = 1; }

    for(int l = 1; l < N; ++l) {
        for(int r = 1; r < N; ++r) {
            dp[l][r] = add(mul(half, dp[l-1][r]),  mul(half, dp[l][r-1]));
        }
    }
}

void calclca() {
    for(int i = 1; i < LOGN; ++i) {
        for(int v = 0; v < N; ++v) {
            parent[v][i] = parent[parent[v][i-1]][i-1];
        }
    }
}

int up(int x, int d) {
    assert(d >= 0);
    for(int i = LOGN-1; i >= 0; i--) {
        if (d & (1 << i)) { x = parent[x][i]; }
    }
    return x;
}

// int lca(int x, int y) {
//     // difference in depths to equalize
//     if (depth[x] > depth[y]) {
//         x = up(x, depth[x] - depth[y]); 
//     } else {
//         y = up(y, depth[y] - depth[x]); 
//     }
// 
//     if (x == y) { return x; }
//     for(int exp = LOGN-1; exp >= 0; exp--) {
//         if (parent[x][exp] != parent[y][exp]) {
//             x = parent[x][exp];
//             y = parent[y][exp];
//         }
//     }
//     return parent[x][0];
// }

int main() {
    ios_base::sync_with_stdio(false);
    // dp is calculated.
    calcdp();
    
    // for(int i = 1; i <= 20; ++i) {
    //     std::cout << i << " | " << inv(i) << " | " << residue(mul(i, inv(i))) << "\n";
    // }
    // std::cout << two << " | " << half << " | " << mul(half, two) << "\n";
    // return 0;
    cin >> n;

    for(int i = 0; i < n-1; ++i) {
        int x, y; cin >> x >> y;
        x--; y--;
        es[x].push_back(y);; es[y].push_back(x);
    }


    int count = 0;
    // for each pair...
    for(int i = 0; i < n; ++i) {
        int dsi[N];
        bool visitedi[N]; std::fill(visitedi, visitedi+N, false);
        bfs(i, dsi, visitedi);
        for(int j = i+1; j < n; ++j) {
            int dsj[N];
            bool visitedj[N]; std::fill(visitedj, visitedj+N, false);
            bfs(j, dsj, visitedj);

            int i2j= dsi[j];
            assert(i2j == dsj[i]); 
            // for each starting node...
            //  i2j: =
            // i==============j
            // i#######*@@@@@@j
            //         #@          |
            // #dsi[r] #@ dsj[r]@  | commonDist
            //         #@          |
            //         r           |
           for(int r = 0; r < n; ++r) {
                int commonDist = ((dsi[r] + dsj[r]) - i2j) / 2; 
                int di = dsi[r] - commonDist;
                int dj = dsj[r] - commonDist;
                // do we even need to remove commonDist? It doesn't seem like it would change
                // the answer even if we kept it.
                // prob. of hitting j (which is larger) before i (which is smaller) = prob. of inversion
                count = add(count, dp[dj][di]);
            }
        }
    }
    // divide by n for 1/n. prob of picking each vertex.
    count = mul(count, inv(n));
    count = residue(count); // just in case?
    std::cout << count << "\n";
}

