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
const int SRC = 1, SINK = 2; 
vector<int> adj[N]; 
int pred[N];
int D[N][N]; /*distances */
int n;

struct BitsetLattice {
    using T = bitset<32>;
    static const T zero;
    static const T inf;
    // or the bits
    static T add(T x, T y) { return x | y; }
    // add(sub (x, y), y) = x|y
    // remove y from x
    // x + y - y <= x (galois connection)
    // x - y + y >= x (galois connection)
    static T sub(T x, T y) { return x & (~ y); }
    // take common bits
    static T min(T x, T y) { return x & y; }
};

const bitset<32> BitsetLattice::zero;
const bitset<32> BitsetLattice::inf = ~BitsetLattice::zero;


struct IntLattice {
    using T = int;
    // identty for add, sub.
    static const int zero;
    static const int inf;

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
const int IntLattice::inf = INF;

template <typename F>
struct Flow {
    using T = typename F::T; // the ground set from F

    T cap[N][N];
    T begincap[N][N];

    T getflow() {
        DO(i, N-1, pred[i] = -1); pred[SRC] = -2; // src is inaccessible.

        queue<pair<int, T>> q;
        q.push({SRC, F::inf});

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

template <typename T>
void addedge(int i, int j, Flow<T> & f, T w) {
    adj[i].push_back(j);
    adj[j].push_back(i);
    f.cap[i][j] = f.begincap[i][j] = w;
}

// given a network that restricts bits, can we reconstruct a {1, 1, 1, 1, 1} 
// given some sources, where the source generates {1, 1, 1, 1, 1}, and
// channels arbitrarily limit bits?
// For even more LOLs, can have capacity
int main() {
    Flow<IntLattice> f;
    cin >> n;
    DO(i, n, DO(j, n, D[i][j] = INF));
    DO(i, n, DO(j, n, f.cap[i][j] = f.begincap[i][j] = IntLattice::zero));

    cout << totpop - f.maxflow() << "\n";
    // cout << f.maxflow() << "\n";
    return 0;
}
