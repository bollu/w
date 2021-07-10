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

ll invert(ll n, ll k) {
    vector<ll> digits;
    // <o t h>
    while(n > 0) {
        ll rem = n % k;
        digits.push_back(rem);
        n /= k;
    }
    

    ll out = 0;
    // ((0*k + h) * k + t) * k + o
    for(int i = digits.size() - 1; i >= 0; i--) {
        out *= k;
        out += (k - digits[i]) % k;
    }
    return out;
}

ll kxor(ll n, ll m, ll k) {
    vector<ll> digits;
    while(n > 0 || m > 0) {
        ll rem1 = n % k;
        ll rem2 = m % k;
        digits.push_back((rem1 + rem2) % k);
        n /= k; m /= k;
    }
    

    ll out = 0;
    for(int i = digits.size() - 1; i >= 0; i--) {
        out *= k;
        out += (digits[i]) % k;
    }
    return out;
}

void solve() {
    ll n; ll k; cin >> n >> k;

    cout << 0 << std::endl; cout.flush();
    {
        ll res; cin >> res;
        if (res == 1) { return; }
    }
    for(ll i = 1; i <= n-1; ++i) {
        cout << kxor(invert(i-1, k), i, k) << std::endl; cout.flush();
        ll res; cin >> res;
        if (res == 1) { return; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) { solve(); }
}



