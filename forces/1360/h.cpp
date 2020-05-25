#include <iostream>
#include <vector>
#include <string>
using namespace std;
using ll = unsigned long long;

// floor(x) = ceil(x) - 1 when x is a fraction

// id[floor((2^m-1)/2)] = 
// = id[ceil((2^m-1)/2) - 1] =
// = id[2^m/2 - 1] =
// = id[2^(m-1) -1]

// median with no strings removed:
// m = 2
// 00
// 01 <- 1: 2^1 - 1
// 10
// 11

// m = 3
// 000
// 001
// 010
// 011 <- 3: 2^2-1
// 100
// 101
// 110
// 111

// m = 4
// 0000
// 0001
// 0010
// 0011
// 0100
// 0101
// 0110
// 0111 <- 7: 2^3 - 1
// 1000
// 1001


// algebra of medians?
// median(sorted) = sorted[(sorted.size()-1)//2]
int main() {
    ll t; cin >> t;
    while(t--) {
        ll m, n; cin >> n >> m;
        string ss[110];
        for(int i = 0; i < n; ++i) { 
            cin >> ss[i];

        }

        ll svals[110];
        for(int i = 0; i < n; ++i) {
            svals[i] = 0;
            for(int j = 0; j < ss[i].size(); ++j) {
                const int ix = (ss[i].size() - 1) - j;
                svals[i] |= (ss[i][j] == '1')<< ix;
            }
        }

        for(int i = 0; i < n; ++i) { cout << ss[i] << " : " << svals[i] << "\n"; }

        ll nelem = 1 << m;
        const ll origmedian = (nelem - 1)/2;

        ll sortedvals[110];
        sortedvals[0] = origmedian;
        for(int i = 1; <= n; ++i) { sortedvals[i] = svals[i]; }

        std::sort(sortedvals, sortedvals+n+1);
        int rnk = 0;
        for(int i = 0 i < n +1; ++i) { if (sortedvals[i] == origmedian) { rnk = i; break; } }
    }
}
