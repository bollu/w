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
    while (t--) {
        ll n, a, b;
        cin >> n >> a >> b;
        string s;
        cin >> s;

        int nalters = 0;
        int l = 0;
        while (l < n) {
            int r = l;
            while (r < n && s[r] == s[l]) {
                r++;
            }
            // [l, r) has same value.
            nalters++;
            l = r;
        }

        if (b >= 0) {
            cout << a * n + b * n << "\n";
        } else {
            cout << a * n + ((nalters / 2) + 1) * b << "\n";
        }
    }
}

