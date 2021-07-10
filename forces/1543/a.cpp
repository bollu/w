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

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        ll a, b; cin >> a >> b;
        if (a < b) { ll swap = a; a = b; b = swap; }
        assert(a >= b);
        a -= b;
        // (a + d, b + d) === (a - b, b + d)
        if (a == 0) {
            cout << "0 0\n";
        } else if (a == 1) {
            cout << "1 0\n";
        } else {
            // a != 0, a != 1, a >= 2
            // (a, b + d) <= a
            // (a, b + d) <= b
            b %= a;
            cout << a << " " << min(a - b, b) << "\n";
            continue;
        }
    }
}



