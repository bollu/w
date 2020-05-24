#include <iostream>
#include <string.h>
#include <string>
#include <map>
#include <array>
#include <stdio.h>
using namespace std;

int n, m; 
char s[12][12];


pair<bool, string> solve(string cursol, int c, array<int, 12> freedom) {
    if (c == m) { return make_pair(true, cursol); }

    map<char, int> counts;
    for(int r = 0; r < n; ++r) {
        counts[s[r][c]]++;
    }

    // all columns agree, nothing to worry.
    if (counts.size() == 1) {
        // try setting all of the mismatches to be the 'correct' one
        // and seeing what happens.
        return solve(cursol + s[0][c], c+1, freedom);
    } else {
        for(auto it: counts) {
            const char match = it.first;

            bool skip = false;
            array<int, 12> nextfreedom = freedom;
            for(int r = 0; r < n; ++r) {
                if (s[r][c] == match) continue;
                if (!nextfreedom[r]) { skip = true; break; }
                nextfreedom[r] = false;
            }
            if (skip) { continue; }

            bool solved; string finalsoln;
            string nextsol = cursol;
            nextsol += match;
            tie(solved, finalsoln) = solve(nextsol, c+1, nextfreedom);
            if (solved) { return make_pair(true, finalsoln); }
        }
    }
    return make_pair(false, "");
}

int main() {
    int t; cin >> t;

    // cout << "===\n";
    while(t--) {
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            scanf("%s", s[i]);
        }
        bool solved; string s;
        array<int, 12> freedom; for(int i = 0; i < n; ++i) {freedom[i] = true; }
        tie(solved, s) = solve("", 0, freedom);
        if(solved) { cout << s << "\n"; } else { cout << -1 << "\n"; }

        // We want a string t such that
        // \forall r, \sum_c (t[c] != s[r][c]) <= 1
        //
        // we can enumerate characters in each column:
        //   chars[c] = set of characters that occur in column c.
        // - if chars[c] = 1 for some column, we need to do nothing more.
        // - if chars[c] > 1, then it is always safe to pick the character
        //                    that occurs most?
        //                    Wrong. we need to pick `c` here though it occurs
        //                    less frequently.
        //
        // (target) c p q
        //          b p q
        //          b p q
        //          b p q
        //          c p r
        //          c p r
        // 
        //

    }
    return 0;

}
