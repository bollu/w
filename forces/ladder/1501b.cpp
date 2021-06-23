#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct interval { 
    int l; int r;
    bool operator < (const interval &other) {
        return l < other.l || (l == other.l && r < other.r);
    }
};

// Sliding window: sort pancake drench ranges and check if current index is drenched.
int main2() {
    int t; cin >> t; // 200_000
    // n over all tests does not exceed 2e5.
    while(t--) {
        int n; cin >> n; // 2e5
        vector<interval> lrs(n);
        for(int i = 0; i < n; ++i) {
            int a; cin >> a;
            // closed intervals, number of elements will be `i - (i-a+1) + 1 = a-1+1 = a`.
            lrs[i].l = std::max(0, i-a+1); lrs[i].r = i;
        }
        std::sort(lrs.begin(), lrs.end());
        int lrix = 0;
        int i = 0;
        while(i < n && lrix < (int)lrs.size()) {
            // 1----i--[l   r]---------
            if (i < lrs[lrix].l) { cout << "0 "; i++;  continue; }
            else {
               // i >= lrs[i].l
               // 2a ---[l-i---r]
               if (i <= lrs[lrix].r) { cout << "1 "; i++; continue; }
               else {
                   // 2b ---[l---r]--i
                   // pop.
                   lrix++; continue;
               }
            }
        }
        // fill remaining zeroes.
        while(i < n) { cout <<"0 "; i++; }
        cout << "\n";

    }
    return 0;
}

// Idea: go in reverse, start from top down towards bottom.
int main() {
    int t; cin >> t; // 200_000
    while(t--) {
        int n; cin >> n; // 2e5
        vector<int> as(n);
        for(int i = 0; i < n; ++i) { cin >> as[i]; }
        vector<int> out(n);

        // lower index upto which we have drenched. Closed [includes this index]
        int drenchedupto = n;
        for(int i = n - 1; i >= 0; i--) {
            // sanity: if as[i] = 0, exclude this index, so we need i+1
            drenchedupto = std::min(drenchedupto, i - as[i]+1);
            if (drenchedupto <= i) { out[i] = 1; }
            else { out[i] = 0; }
        }
        for(int i= 0; i < n; ++i) { cout << out[i] << " "; }
        cout << "\n";
    }
    return 0;

}
