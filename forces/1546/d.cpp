#include <assert.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
#include <queue>
#include <stack>
// Q. For a given recurrence, what base cases do I need to implement?
using namespace std;
using ll = long long;

static const int N = 1e5 + 10;

static const ll MOD = 998244353;
ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

ll modpow(ll a, ll pow) {
    if (pow == 0) { return 1; }
    if (pow == 1) { return a; }
    ll half = modpow(a, pow/2);
    ll sq = mul(half, half);
    return pow % 2 == 1 ? mul(a, sq) : sq;
}

// a^{p-2}
ll mulinv(ll a) {
    return modpow(a, MOD-2);
}

ll fact[N];

int ncomb(int n, int r) {
    if (r > n) { return 0; }
    return mul(mul(fact[n], mulinv(fact[r])), mulinv(fact[n-r]));
}

// n = number of spaces, tiles = number of tiles.
// returns: number of ways to place k 2x1tiles in n spaes.
ll dp(ll n, ll k) {
    return ncomb(n-k, k);
}


void solve() {
    ll n; cin >> n;
    std::string s; cin >> s;
    ll ntiles = 0;
    ll n1s = 0;

    ll l = 0;
    while(l < n) {
        if (s[l] != '1') { l++; continue; }
        ll r = l; // [l, r)
        while (s[r] == '1') { r++; }
        ll len = r - l;
        ntiles += len / 2;
        n1s += len % 2;
        l = r;
    }
    // cout << "### " << s << " | n1s: " << n1s << " | ntiles: " << ntiles << " | n: " << n << "\n";
    // 1s dont matter because they remain fixed, discount them.
    // count number of configurations with k tiles amnogst
    // n - n1s spaces.
    // spread k (2x1 tiles) amongst n locations
    //
    // > ==|==|==|...| [k=3, n=9]
    // > 12|34|56|789|
    // ...
    // ...
    // > ==|==|==|...| [k=3, n=9]
    // > 12|34|56|789|
    //
    // n-2k = 9 - 3.2 = 3 blank tiles
    //
    // . . .
    // have 6 locations, need to place 3 white 1x1 tiles.
    cout << dp(n-n1s, ntiles) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;

    // check inverse works.
    for(int i = 1; i < N; ++i) {
        assert(mul(i, mulinv(i)) == 1);
    }

    for(int i = 0; i < N; ++i) {
        if (i == 0) { fact[i] = 1; }
        else { fact[i] = mul(i, fact[i-1]); }
    }


    while(t--) {
        solve();
    }
}




