#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <assert.h>
//#define DEBUGLINE cout << "\t##" << __LINE__ << "##\n";
#define DEBUGLINE if(0) {};
using namespace std;
using ll = long long;
// 1 2 3 4 5
// 1 2 3 2 1

const int INF = (int) 1e9;
const int LEN = 200000 + 5;
int as[LEN];
int counts[LEN];
int permcounts[LEN];


int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n; 
        for(int i = 1; i <= n; ++i){ counts[i] = 0; }
        bool fail = false;
        for(int i = 1; i <= n; ++i) { int a; cin >> a; as[i] = a; counts[a]++; }
        if (fail) { DEBUGLINE; cout << 0 << "\n"; continue;  }
        int mv = -INF; for(int i = 1; i <= n; ++i) { mv = max(mv, as[i]); }
        fail = false;
        for(int i = 1; i <= mv; ++i) { counts[i]--; }
        if (fail) {DEBUGLINE; cout << 0 << "\n"; continue;  }
        // we have element remaining.
        int mv2 = -INF; for(int i = 1; i <= n; ++i) { if (counts[as[i]]) { mv2 = max(mv2, as[i]); } }
        for(int i = 1; i <= mv2; ++i) { counts[i]--; };
        // check that we ran out of all numbers.
        for(int i = 1; i <= n; ++i) { if (counts[i] != 0) { fail = true; } }
        if (fail) { DEBUGLINE; cout << 0 << "\n"; continue;  }
        DEBUGLINE;
        const int ix1 = min(mv2, n - mv2+1);
        const int ix2 = max(mv2, n - mv2+1);
        set<pair<int, int>> sols;
        {
            for(int i = 1; i <= n; ++i) { permcounts[i]=0; }
            for(int i = 1; i <= mv2; ++i) { permcounts[as[i]]++; }
            bool allperms = true; for(int i = 1; i <= mv2; ++i) { if (permcounts[i] != 1) { DEBUGLINE; allperms = false; break; } }
            if (allperms) { DEBUGLINE; sols.insert(make_pair(mv2, n - mv2)); }
        }

        {
            for(int i = 1; i <= n; ++i) { permcounts[i]=0; }
            for(int i = n; i >= n - mv2+1; i--) { DEBUGLINE; permcounts[as[i]]++; }
            bool allperms = true; for(int i = 1; i <= mv2; ++i) { if (permcounts[i] != 1) { DEBUGLINE; allperms = false; break; } }
            if (allperms) { DEBUGLINE; sols.insert(make_pair(n - mv2, mv2)); }
        }

        cout << sols.size() << "\n";
        for(pair<int, int> p : sols) {
            cout << p.first << " " << p.second << "\n";
        }

    }
    return 0;
}

