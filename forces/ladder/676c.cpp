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
            if (s[r] != c) { changed++; }

            while (changed > k) {
                if (s[l] != c) { changed--; }
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

namespace binarysearch {
    int main() {
        int n, k; cin >> n >> k;
        string s; cin >> s;

        vector<int> as(n+1, 0); // as[i] = #as in [0..i] [closed]
        vector<int> bs(n+1, 0); // as[i] = #as in [0..i] [closed]
        for(int i = 0; i < n; ++i) { as[i+1] = (s[i] == 'a') + as[i]; }
        for(int i = 0; i < n; ++i) { bs[i+1] = (s[i] == 'b') + bs[i]; }

        // l is substring of length l beautiful.
        // max l: n
        auto solve = [&](int l) {
            for(int start = 0; start < n; ++start) {
                // [0..end) - [0..start] = [start..end]
                int end = start+l;
                if (end > n) { break; }

                int nas = as[end] - as[start];
                int nbs = bs[end] - bs[start];
                assert(nas + nbs == l);
                if (nas <= k) { 
                    return true;
                }
                if (nbs <= k) { 
                    return true;
                }
            }
            return false;
        };

        // find largst index such that solve(ix) = true.
        // tttttfff
        // [l, r)
        // int l = 0, nbits = 12;
        // while(l < n && nbits >= 0) {
        //     int lnext = min(l+(1<<nbits), n);
        //     if (solve(lnext)) {
        //         l = lnext;
        //     } else {
        //         nbits--;
        //     }
        // }
        int left = 0, right = n;
        int best = -1;
        while(left <= right) {
            int mid = left + (right - left)/2;
            bool p = solve(mid);
            if (p) {
                best = max(best, mid);
                left = mid+1;
            } else {
                right = mid-1;
            }
        }
        cout << best;
        return 0;
    };
};

int main() { return forloop::main(); }

