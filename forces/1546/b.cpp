#include <assert.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
#include <queue>
#include <stack>
using namespace std;
using ll = long long;

static const int INF = 1e11;

void solve() {
    int n, m; cin >> n >> m;

    vector<string> ss(n);
    vector<string> pss(n-1);
    map<int, map<char, int> > col2char2count;

    for(int i = 0; i < n; ++i) {
        cin >> ss[i];
        for(int j = 0; j < m; ++j) {
            col2char2count[j][ss[i][j]]++;
        }
    }
    // cout << __LINE__ << "\n";

    for(int i = 0; i < n-1; i++) {
        cin >> pss[i];
        for(int j = 0; j < m; ++j) {
            col2char2count[j][pss[i][j]]--;
        }
    }
    // cout << __LINE__ << "\n";

    for(int i = 0; i < n; ++i) {
        bool correct = true;
        for(int j = 0; j < m; ++j) {
            if (col2char2count[j][ss[i][j]] > 0) { continue; }
            correct = false;
        }
        if (correct) {
            cout << ss[i] << std::endl;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) { solve(); }
}



