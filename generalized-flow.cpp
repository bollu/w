// https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/doomsday/
// https://www.hackerearth.com/submission/34759648/
#include <iostream>
#include<cmath>
#include<vector>
#include<tuple>
#include<queue>
#include <bitset>

using namespace std;
using I=int; const I INF = 1000000000L; const I N = 105;
#define DO(i,n,SSS) for(int i=1;i<=n;++i) SSS


// SRC -(POP)-> CITY m -(REACHABLE IN T)-> CITY n -(NPODS)-> SINK
const int SRC = 102, SINK = 103; 
vector<int> adj[N]; 
int pred[N];
int D[N][N]; /*distances */
int n, e, x;
void apsp() {
    DO(i, n, DO(j, n, DO(k, n, D[i][k] = min(D[i][k], D[i][j] + D[j][k]))));
}

struct BitsetLattice {
    using T = bitset<32>;
    static const T zero;
    // or the bits
    static T add(T x, T y) { return x | y; }
    // add(sub (x, y), y) = x|y
    // remove y from x
    static T sub(T x, T y) { return x & (~ y); }
    // take common bits
    static T min(T x, T y) { return x & y; }
};

const bitset<32> BitsetLattice::zero;


struct IntLattice {
    using T = int;
    // identty for add, sub.
    static const int zero;

    // x + zero = x
    // commutative, associative
    inline static T add(T x, T y) { return x + y; }
    // y - x + x == x
    // y - zero = y
    inline static T sub(T x, T y) { return x - y; }

    // y - x + x >= y (we can gain more when we subtract and then add: for example, (x & y) | y == y
    // min(y, y -x+x) == y
    // min(y, zero) = zero
    // min(y, y-x) = y-x
    // min(y, x) = x
    inline static T min(T x, T y) { return std::min(x, y); }
};
const int IntLattice::zero = 0;

template <typename F>
struct Flow {
    using T = typename F::T; // the ground set from F

    T cap[N][N];
    T begincap[N][N];

    T getflow() {
        DO(i, N-1, pred[i] = -1); pred[SRC] = -2; // src is inaccessible.

        queue<pair<int, T>> q;
        q.push({SRC, INF});

        while(!q.empty()) {
            const int u = q.front().first; 
            const T s2u = q.front().second;
            q.pop();


            for(auto v: adj[u]) {
                const T u2v = cap[u][v];
                if (pred[v] == -1 && u2v != 0) {
                    const T f = F::min(s2u, u2v);
                    pred[v] = u;
                    if (v == SINK) return f;
                    q.push({v, f});
                }
            }
        }
        return 0;
    }

    T maxflow() {
        T mf = F::zero;
        T curflow;
        while((curflow = getflow()) != F::zero) {
            // cout << "curflow: " << curflow << "\n";
            // mf = += curflow;
            mf = F::add(mf, curflow);
            for(int v = SINK; v != SRC; v = pred[v]) {
                int u = pred[v];
                // cap[u][v] -= curflow;
                cap[u][v] = F::sub(cap[u][v], curflow);
                // cap[v][u] += curflow;
                cap[v][u] = F::min(begincap[v][u], F::add(cap[v][u], curflow));
            }
        }
        return mf;
    }
};

int main() {
    int totpop = 0;
    Flow<IntLattice> f;
    cin >> n >> e >> x;
    DO(i, n, DO(j, n, D[i][j] = INF));
    DO(i, n, DO(j, n, f.cap[i][j] = f.begincap[i][j] = 0));
    DO(i, n, { int w; cin >> w; totpop += w; adj[SRC].push_back(i); adj[i].push_back(SRC); f.cap[SRC][i] = f.begincap[SRC][i] = w; });
    DO(i, n, { int w; cin >> w; adj[i].push_back(SINK); adj[SINK].push_back(i); f.cap[i][SINK] = f.begincap[i][SINK] = w; });

    DO(i, e, { int u; int v; cin >> u >> v; cin >> D[u][v]; });

    apsp();
    DO(i, n, DO(j, n,if (D[i][j] <= x) { 
        // cout << "D[" << i << "][" << j << "] <= " << x << "\n";
        adj[i].push_back(j); adj[j].push_back(i); f.cap[i][j] = f.cap[j][i] = f.begincap[i][j] = f.begincap[j][i] = INF;
        }));
    cout << totpop - f.maxflow() << "\n";
    // cout << f.maxflow() << "\n";
    return 0;
}
