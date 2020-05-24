#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int as[200];
        bool paired[200];

        int odds = 0, evens = 0;
        for(int i = 0; i < n; ++i) {
            cin >> as[i];
            evens += as[i] % 2 == 0;
            odds += as[i] % 2 != 0;
        }

        int npairs = 0;
        sort(as, as+n);
        for(int i = 0; i < n-1; ++i) {
            if (as[i]+1 == as[i+1]) { npairs++; }
        }

        bool success = false;
        if (evens % 2 == 0 && odds % 2 == 0) {
            success = true;
        } else {
            for(int i = 0; i <= npairs; ++i) {
                if (((evens - i) % 2 == 0) && ((odds - i) % 2 == 0)) {
                    success = true; break;
                }
            }
        }

        cout << (success ? "YES\n" : "NO\n");

    }
}
