#include <iostream>
#include <assert.h>
using namespace std;
using ll = long long;
int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    ll a, b, n; cin >> a >> b >> n;
    // a . 10 + n = 0

    ll mod = -1;
    for(int i = 0; i <= 9; ++i) {
        if ((a*10 + i) % b == 0) { mod = i; break; }
    }

    if (mod == -1) { cout << -1; } 
    else {
        assert(mod >= 0 && mod <= 9);
        cout << a << mod;
        for(ll i = 1; i < n; ++i) { cout << '0'; }
    }
    return 0;
}

