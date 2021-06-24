#include<iostream>
#include<vector>
#include<string>
using namespace std;


// conjecture: find lengths of runs of 1s. total# of swaps = Σ(len.run -1)
// wrong!
int main() {
    int t; cin >> t;
    while(t--) {
        int _; cin >> _;
        string s; cin >> s;
        int l = 0;
        int tot = 0;
        while(l < (int) s.size()) {
            if (s[l] != '1') { l++; continue; }
            int r = l + 1;
            while(r < (int) s.size() && s[r] == '1') { r++; }
            // interval [l, r)
            tot += (r - l) - 1;
            l = r;
        }

        l = 0;
        int tot2 = 0;
        while(l < (int) s.size()) {
            if (s[l] != '0') { l++; continue; }
            int r = l + 1;
            while(r < (int) s.size() && s[r] == '0') { r++; }
            // interval [l, r)
            tot2 += (r - l) - 1;
            l = r;
        }
        cout << std::max<int>(tot, tot2) << "\n";
    }
    return 0;
}

