#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;


// how to notice?
//(fi+1, f) = (1 -1) fi  
//            (1   0) fi-1
// m is transition matrix.
// In [33]: m                                                                                                                        
// Out[33]: 
// Matrix([
// [1, -1],
// [1,  0]])
// In [32]: m.eigenvals()                                                                                                            
// Out[32]: {1/2 + sqrt(3)*I/2: 1, 1/2 - sqrt(3)*I/2: 1}
// eingenvalues are nth roots of unity, should have period
// --
// f(i+1) = f(i) - f(i-1)
//
// f3 = y - x
// f4 = (y - x) - y = -x
// f5 = -x - (y - x) = -x - y + x = -y
// f6 = -y - (-x) = -y + x = x - y
// f7 = x - y - (-y) = x - y + y = x


const ll MOD = 1000000007L;

ll mod(ll i) {
    while (i < 0) { i = i + MOD; };
    return i % MOD;
};

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    ll x, y, n; cin >> x >> y >> n;
    switch((n - 1) % 6) {
        case 0: cout << mod(x); break;
        case 1: cout << mod(y); break;
        case 2: cout << mod(y - x); break;
        case 3: cout << mod(-x); break;
        case 4: cout << mod(-y); break;
        case 5: cout << mod(x - y); break;
    }

    return 0;
}

