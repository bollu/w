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

static const int N = 10;

void solve(const string &s) {
    int minScore[2] = {0, 0};
    int maxScore[2] = {0, 0};

    // number of scores team can score i in turn [t..N]
    for(int i = 1; i <= 10; ++i) {
        int c = s[i-1];
        bool ix = i % 2;
        if (c == '1') {
            minScore[ix] += 1; maxScore[ix] += 1;
        } else if (c == '?') {
            maxScore[ix] += 1;
        }

        int gap = maxScore[ix] - minScore[1^ix];
        int nOpponentCanScore = 0;
        for(int j = i + 1; j <= 10; ++j) {
            if (j % 2 != ix) { nOpponentCanScore++; }
        }
        // cout << "\ts[" << s << "] i[" << i << "] gap[" << gap << "] nOpponentCanScore[" << nOpponentCanScore << "]\n";
        if (gap > nOpponentCanScore) {
            cout << i << "\n";
            return;
        }

        gap = maxScore[1^ix] - minScore[ix];
        int nWeCanScore = 0;
        for(int j = i + 1; j <= 10; ++j) {
            if (j % 2 == ix) { nWeCanScore++; }
        }
        if (gap > nWeCanScore) {
            cout << i << "\n";
            return;
        }

    }
    cout << 10 << "\n";
    return;

    assert(false && "should never reach here.");
};

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
        string s; cin >> s;
        solve(s);
    }
}

