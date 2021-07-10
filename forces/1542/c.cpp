#include <iostream>
#include <numeric>
using namespace std;

using ll = long long;
static const ll MOD = ll(1e9) + 7;
int main() {
    // f(x) = y  =>
    // [f(x) >= 1] + [f(x) >= 2] + [f(x) >= 3] + ... + [f(x) >= Y] = y
    // 
    // [f(x) >= k] iff 
    //    lcm(1, 2, .. k) | x
    //
    // so, keep checking 
    //    lcm(1, 2, ... k) | x
    // till lcm(1, 2, ... k) > x, ie, we can't have this be a pre-image in the range we are interested in.
    int t; cin >> t;
    while(t--) {
        ll n; cin >> n;
        ll total = 0;
        int i = 1;
        ll lcmUptoI = 1;
        while(n / lcmUptoI > 0) {
            total = (total + ((n / lcmUptoI) % MOD)) % MOD;
            lcmUptoI = std::lcm<ll>(lcmUptoI, i);
            i++;
        }
        cout << total << "\n";
    }
}
