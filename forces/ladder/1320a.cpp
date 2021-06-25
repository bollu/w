#include<iostream>
#include<vector>
#include<map>
using namespace std;

static const int N = 2e5 + 10;
int dp[N];
static const int INF = 1e9;
// dp[l][r] = length of longest path in cities taken from [l..r] 
// c[i+1] - c[i] == b[i+1] - b[i]
// c[i+1] - b[i + 1] == c[i] - b[i]
//
// Intuitition: Δc = Δb <-> Δ(c-b) = 0.
// But Δ(c-b) = 0 is easier to check.
using ll = long long;
int main() {
    int n; cin >> n;
    vector<int> as(n);
    map<ll, ll> m;
    for(int i = 1; i <= n; ++i) {
        int x; cin >> x;
        m[x - i] += x;
    }

    ll best = -INF;
    for(auto it : m) {
        best = std::max(best, it.second);
    }
    cout << best;

    return 0;
}

