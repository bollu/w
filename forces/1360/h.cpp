#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <functional>
#include <set>
#include <algorithm>
using namespace std;
using ll = int64_t;

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
//         v
// 0 1 2 3 4 5 6 7 8 : 8/2: index 4
//
//  (remove 8)
// 0 1 2 3 4 5 6 7:   7/2: index 3
//
//  (remove 7)
// 0 1 2 3 4 5 6:   6/2: index 3
//
//  (remove 6)
// 0 1 2 3 4 5:   5/2: index 2
int main() {
    ll t; cin >> t;
    while(t--) {
        ll m, n; cin >> n >> m;
        string ss[110];
        for(ll i = 0; i < n; ++i) { 
            cin >> ss[i];

        }

        set<ll> svals;
        for(ll i = 0; i < n; ++i) {
            ll v = 0;
            for(ll j = 0; j < ss[i].size(); ++j) {
                const ll ix = (ss[i].size() - 1) - j;
                v |= (ll)(ss[i][j] == '1') << ix;
            }
            svals.insert(v);
        }


        const ll med = (((ll)1 << m) - 1)/2;
        ll ans = -1;
        // M (N + log N)
        for(ll i = max<ll>(med - 60, 0); i <= min<ll>(((ll)1 << m) - 1, med+60); ++i) {
            if (svals.count(i)) { continue; }

            ll lt = i;
            ll geq = ((ll)1 << m) - 1 - i;

            for(ll v : svals) {
                if (v < i) { lt--; }
                else { geq--; }
            }

            if (abs(lt - geq) <= 1) {
                // cout << i << "\n";
                ans = i;
                break;
            }
        }

        for(ll i = m-1; i >= 0; i--) {
            cout << ((ans & ((ll)1 << i)) ? '1' : '0');
        }
        cout << "\n";

    }
}
