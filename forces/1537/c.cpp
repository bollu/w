#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
int t;
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        std::vector<int> xs(n);
        for (int i = 0; i < n; ++i) {
            cin >> xs[i];
        }
        std::sort(xs.begin(), xs.end());
        int gval = 1e9;
        int gix = -1;
        for (int i = 0; i < n - 1; ++i) {
            int g = xs[i + 1] - xs[i];
            if (gix == -1) {
                gval = g;
                gix = i;
                continue;
            }
            if (g < gval) {
                gval = g;
                gix = i;
                continue;
            }
            if (g == gval) {
                // larger gap.
                if (xs[i + 1] - xs[i] > xs[gix + 1] - xs[gix]) {
                    gval = g;
                    gix = i;
                }
            }
        }

        std::priority_queue<int> gt;
        std::priority_queue<int> lt;

        for (int i = 0; i < n - 1; ++i) {
            if (i == gix || i == gix + 1) {
                continue;
            }
            if (xs[i] > xs[gix]) {
                gt.push(xs[i]);
            } else {
                lt.push(xs[i]);
            }
        }
        cout << xs[gix] << " ";
        while (gt.size()) {
            cout << gt.top() << " ";
            gt.pop();
        }
        while (lt.size()) {
            cout << lt.top() << " ";
            lt.pop();
        }
        cout << xs[gix + 1] << "\n";
    }
    return 0;
}
