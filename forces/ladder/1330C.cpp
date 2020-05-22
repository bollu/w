#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;


// n = 11
// i = 5
// paint cells [p1, ... p1+l1] with color [1]
// paint cells [p2, ... p2+l2] with color [2]
// paint cells [pn, ... pn+ln] with color [n]
//
//
// we want all colors to appear at least once, and all cells to be colored.

// p1 ∈ [1, n+1-l1] ->  [p1, p1-1+l1] [paint these cells with number i]
// p2 ∈ [1, n+1-l2] ->  [p2, p2-1+l2] [paint these cells with number i]
const ll MAX = 1e6+ 6;
ll ls[MAX];
ll outps[MAX];
int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    ll n, m; cin >> n >> m;

    ll totl = 0; 
    for(int i = 1; i <= m; ++i) { cin >> ls[i]; totl += ls[i]; }
    if (totl < n) { cout << -1; return 0; }

    for(int i = 1; i <= m; ++i) {
        const ll x = max<ll>(i, n - totl+1);
        if (x + ls[i] - 1 > n) { cout << -1; return 0; }
        outps[i] = x;
        totl = totl - ls[i];
    }

    for(int i = 1; i <= m; ++i) { cout << outps[i] << " "; }

    return 0;
}

