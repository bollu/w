#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;

using ll = long long;

int rec(int x, int y, int sum) {
    if (x == 0) { return 1; }
    if (y == 0) { return 1; } 
}

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        ll x1, y1, x2, y2; 

        ll x = max(x1 - x2, x2 - x1);
        ll y = max(y1 - y2, y2 - y1);

        cout << comb[x][y] << "\n";
        
    }
}
