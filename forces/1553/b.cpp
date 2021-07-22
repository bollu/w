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

bool trycase(const string &s, const string &t, int S, int R) {
    int ixs = S;
    int ixt = 0;
    for(int i = 0; i < R; ++i) {
        if (ixs >= s.size()) { return false; }
        if (s[ixs] != t[ixt]) {
            return false;
        }
        ixs++;
        ixt++;
    }

    ixs -= 2;

    for(int i  = 0; i < t.size()-R; ++i) {
        if (ixs < 0) { return false; }
        if (s[ixs] != t[ixt]) { return false; }
        ixt++;
        ixs--;
    }
    return true;

}

bool solve(string &s, string &t) {
    for (int S = 0; S < s.size(); ++ S) {
        for(int R = 0; R <= t.size(); ++R) {

            if (trycase(s, t, S, R)) { return true; }
        }
    }
    return false; 

}
int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        std::string s, t;
        cin >> s >> t;
        cout << (solve(s, t) ? "YES" : "NO") << "\n";
    }
}

