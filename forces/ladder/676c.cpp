// https://codeforces.com/contest/676/submission/18075788
// WTF is this solution
#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

namespace forloop {
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int best = 0;
    for (int c = 'a'; c <= 'b'; ++c) {
        int l = 0;
        int changed = 0;
        // [l, r]
        for (int r = 0; r < n; ++r) {
            // change to 'a'
            if (s[r] != c) {
                changed++;
            }
            while (changed > k && l < r) {
                if (s[l] != c) {
                    changed--;
                }
                l++;
            }
            best = max(best, r - l + 1);
        }
    }
    cout << best;

    return 0;
}
}  // namespace forloop

namespace whileloop {
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    string s;
    cin >> s;

    int best = 0;
    for (int c = 'a'; c <= 'b'; ++c) {
        int l = 0, r = 0;
        // window: [l, r)
        int changed = 0;
        while (r < n) {
            assert(changed <= k);
            assert(l <= r);
            if (s[r] == c) {
                r++;
            } else {
                if (changed == k) {
                    if (s[l] != c) {
                        changed--;
                    }
                    l++;
                } else {
                    r++;
                    changed++;
                }
            }
            best = max(best, r - l);
        }
    }
    cout << best;

    return 0;
}

}  // namespace whileloop

int main() { return forloop::main(); }

