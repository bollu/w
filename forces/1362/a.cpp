#include <iostream>
using ll = long long;

using namespace std;

ll log2(ll x) {
    if (x == 1) { return 0; }
    if (x == 0) { return 0; }
    if (x == 2) { return 1; }
    if (x %2 != 0) { return -1; }
    ll rec = log2(x/2);
    if (rec == -1) { return -1; }
    return 1 + rec;
}

int main() {
    int t; cin >> t;
    while(t--) {
        ll a, b; cin >> a >> b;
        if (a < b) { swap(a, b); }
        if  (a == b) { cout << "0\n"; }
        else if (a % b != 0) { cout << "-1\n"; }
        else {
            ll div = a / b;
            ll l2 = log2(div);
            if (l2 == -1) { cout << "-1\n"; }
            else {
                ll n8 = l2 / 3;
                l2 -= n8 * 3;
                ll n4 = l2 / 2;
                l2 -= n4 * 2;
                ll n2 = l2;
                l2 -= n2;
                cout << n8 + n4 + n2 << "\n"; 
            }
            
        }

    }
    return 0;
}
