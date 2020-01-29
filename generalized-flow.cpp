// https://www.hackerearth.com/practice/algorithms/graphs/maximum-flow/practice-problems/algorithm/doomsday/
// https://www.hackerearth.com/submission/34759648/
#include <iostream>
#include <cmath>
#include <vector>
#include <tuple>
#include <queue>
#include <bitset>
#include <cassert>

using namespace std;
using I=int; const I INF = 1000000000L; const I N = 105;
#define DO(i,n,SSS) for(int i=1;i<=n;++i) SSS


// SRC -(POP)-> CITY m -(REACHABLE IN T)-> CITY n -(NPODS)-> SINK
const int SRC = 1, SINK = 2; 
vector<int> adj[N]; 
int pred[N];
int n;


int gcd(int l, int s) {
    assert (l != 0); assert(s != 0);
    if (l < s) { int t = s; s = l; l = s; };
    if (l % s == 0) return s;
    return gcd(s, l % s);
}

// this is some sort of "partial order + actions"
// consider only numbers {1, 2, 3, 4, 5, 6} under gcd() and lcm(). top 
// will be LCM of all elements = 60. bot will be gcd of all elements = 1
struct MultiplicativeLattice {
    using T = int;
    static const T zero;
    static const T inf;
    // or the bits
    static T add(T x, T y) { return x * y; }
    // add(sub (x, y), y) = x|y
    // remove y from x
    // x + y - y <= x (galois connection)
    // x - y + y >= x (galois connection)
    // remove factors from x
    static T sub(T x, T y) { return max(x / y, 1); };
    static T min(T x, T y) { return gcd(x, y); };
};

const int MultiplicativeLattice::zero = 1;
const int MultiplicativeLattice::inf = 60*60*60;


// this is some sort of "partial order + actions"
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
        // DO(i, N-1, pred[i] = -1);
        for(int i = 0; i < N; i++) pred[i] = -1;
        pred[SRC] = -2; // src is inaccessible.

        queue<pair<int, T>> q;
        q.push({SRC, F::inf});

        while(!q.empty()) {
            const int u = q.front().first; 
            const T s2u = q.front().second;
            q.pop();

            cout << " at vertex: " << u << "\n";
            for(auto v: adj[u]) {
                const T u2v = cap[u][v];
                const T f = F::min(s2u, u2v);
                cout << "  " << SRC << "-(" << s2u << ")->" << u << "-(" << u2v << ")-> " << v << " || ";
                cout << "  " << SRC << "---(" << f << ")--->" << v;
                cout << "\n";

                if (pred[v] == -1 && f != F::zero) {
                    pred[v] = u;
                    if (v == SINK) return f;
                    q.push({v, f});
                }
            }
        }
        return F::zero;
    }

    T maxflow() {
        T mf = F::zero;
        T curflow = F::zero;
        cout << "FLOW\n----\n";
        while((curflow = getflow()) != F::zero) {
          cout << "curflow:= " << curflow << " | mf := " << mf << "+"<<curflow<<":="<<F::add(mf, curflow)<<"\n";
          mf = F::add(mf, curflow);
            for(int v = SINK; v != SRC; v = pred[v]) {
                int u = pred[v];
                // cap[u][v] -= curflow;
                cout << "cap["<<u<<"]["<<v<<"] = "<<cap[u][v]<<" - " << curflow << " := " << F::sub(cap[u][v], curflow) << "\n";
                cap[u][v] = F::sub(cap[u][v], curflow);
                // cap[v][u] += curflow;
                cout << "cap["<<v<<"]["<<u<<"] = min("<<begincap[v][u] << "," << 
                  cap[v][u] << "+" << curflow << ":=" << F::add(cap[v][u], curflow) << 
                  ") := " << 
                  F::min(begincap[v][u], F::add(cap[v][u], curflow)) << "\n";
                cap[v][u] = F::min(begincap[v][u], F::add(cap[v][u], curflow));
            }
            cout << "FLOW\n----\n";
        }
        return mf;
    }
};

template <typename Lat>
void addedge(int i, int j, Flow<Lat> & f, typename Lat::T w) {
    adj[i].push_back(j);
    adj[j].push_back(i);
    f.cap[i][j] = f.begincap[i][j] = w;
}

// given a network that restricts bits, can we reconstruct a {1, 1, 1, 1, 1} 
// given some sources, where the source generates {1, 1, 1, 1, 1}, and
// channels arbitrarily limit bits?
// For even more LOLs, can have capacity
int main() {
    Flow<MultiplicativeLattice> f;
    cin >> n;
    DO(i, N-1, DO(j, N-1, f.cap[i][j] = f.begincap[i][j] = MultiplicativeLattice::zero));

    for(int i = 1; i <= n; ++i) {
        int x, y; cin >> x >> y;
        int w; cin >> w; // keep W separate if we want to change weights.
        addedge<MultiplicativeLattice>(x, y, f, w);
    }

    cout << "ADJ:\n";
    for (int u = 0; u < N; ++u) {
      for(auto v : adj[u]) {
        cout << u << "->" << v << "\n";
      }
    }

    cout << "CAPACITIES:\n";
    for(int i = 1; i < N; ++i) {
        for(int j = 1; j < N; ++j) {
            if (f.cap[i][j] == MultiplicativeLattice::zero) continue;
            cout << i*n+j << ": " << i << "-(" << f.cap[i][j] << ")->" << j << "\n";
        }
    }

    cout << "FLOW:\n";
    cout << f.maxflow() << "\n";
    return 0;
}
