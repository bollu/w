#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        int n; cin >> n;
        if (n % 3 == 0) {
            // l = n/3, r = n/3
            cout << n/3 << " " << n/3 << "\n"; 
        } else if (n % 3 == 1) {
            // l = n/3+1, r = n/2
            cout << n/3+1 << " " << n/3 << "\n";
        } else if (n % 3 == 2) {
            cout << n/3 << " " << n/3+1 << "\n";
        } else {
            assert(false && "unreachable");
        }
    }
}

