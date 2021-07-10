#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        // odd + odd = even
        // even + odd = odd
        // odd + even = odd
        // even + even = even
        int neven = 0, nodd = 0;
        for(int i = 0; i < 2*n; ++i) {
            int x; cin >> x;
            neven += (x % 2 == 0);
            nodd += (x % 2 == 1);
        }

        // n even, m odd

        if (neven == nodd) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
    return 0;
}


