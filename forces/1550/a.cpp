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
    vector<int> sums;
    sums.push_back(0);
    sums.push_back(1);

    int sum = 1, k = 3;
    while (sum < 1e6) {
        sum += k;
        k += 2;
        sums.push_back(sum);
    }

    while (t--) {
        int s;
        cin >> s;
        int l = 0, r = sums.size() - 1;
        int best = 0;  // largest index i such that  sums[i] < s
        while (l <= r) {
            int m = (l + r) / 2;
            if (sums[m] < s) {
                best = max<int>(best, m);
                // can try larger
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        cout << best + 1 << "\n";
    }
}

