#include <assert.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
#include <queue>
#include <stack>
using namespace std;
using ll = long long;

static const int INF = 1e11;

void solve() {
    ll n; ll k; cin >> n >> k;

    ll perturb = 0;
    cout << 0 << std::endl; cout.flush();
    {
        ll res; cin >> res;
        if (res == 1) { return; }
    }
    for(ll i = 1; i <= n-1; ++i) {
        cout << (i ^ (i-1)) << std::endl; cout.flush();
        ll res; cin >> res;
        if (res == 1) { return; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) { solve(); }
}



