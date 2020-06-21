#include <iostream>
using namespace std;
using LL = long long int;

LL f (LL n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 3;
    return f(n/2) + n;
}

//have ~ 10^3 remaining. log(10^18) = 18.
void solve() {
    LL n; cin >> n; cout << f(n) << "\n";
}

// t ~ 10^5
int main() {
    int t; cin >> t; while(t--) solve();
}
