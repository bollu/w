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

static const int N = 1e5 + 1;
// [si][ti]: can create string t[0, ti) using s[0, si). 
bool dp[3][N+1];

inline int positive_mod(int i, int n) {
    return (n + (i % n)) % n;
}


bool solve() {
    string s, t;
    cin >> s >> t;

    // vector<vector<bool>> dp(s.size()+1, vector<bool>(t.size()+1));


    for(int ti = 1; ti < t.size(); ++ti) {
        dp[0][ti] = false; // cannot create non-empty string t[0, ti) using empty string s[0, 0) = ""
    }

    for(int si = 0; si < s.size(); ++si) {
        dp[si%3][0] = true; // is always possible to create empty string t[0, 0) = "" from s[0, _).
    }


    dp[1][1] = s[0] == t[0]; // string s[0, 1) = s[0] can match t[0, 1) = t[0] if string match.
    for(int ti = 2; ti < t.size(); ++ti) {
        dp[1][ti] = false; // s[0, 1) cannot create longer strings t[0, ti) for ti > 1.
    }


    bool success = false;
    for(int si = 2; si <= s.size(); ++si) {
        for(int ti = 1; ti <= t.size(); ++ti) {
            // 1. erase a character, use that si-2 can match ti.
            // 2. use current character and match.
            dp[positive_mod(si, 3)][ti] = dp[positive_mod(si-2, 3)][ti] || 
                (s[si-1] == t[ti-1] && dp[positive_mod(si-1, 3)][ti-1]);

            // cerr << "\t-si: " << si << " | s: [";
            // for(int k = 0; k < si; ++k) { cerr << s[k]; }
            // cerr << "] | ";
            // cerr << "ti: " << ti << " | t: [";
            // for(int k = 0; k < ti; ++k) { cerr << t[k]; }
            // cerr << "] | dp: " << dp[si][ti] << "\n";

        }
    }
    return dp[positive_mod(s.size(), 3)][t.size()];
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        cout << (solve() ? "YES" : "NO") << "\n";        
    }
}

