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
    // map<int, map<char, int>> col2char2count;
    map<char, int> cs;
    map<char, int> pcs;

    for(int i = 0; i < n; ++i) {
        cin >> ss[i];
        for(char c : ss[i]) { cs[c]++; }
    }

    for(int i = 0; i < n-1; ++i) {
        cin >> pss[i];
        for(char c : pss[i]) { pcs[c]++; }
    }


    // check if this is possible.
    for(string &s : ss) {
        map<char, int> scs;
        bool success = true;
        for(char c : s) { scs[c]++; }
        for (auto it : scs) {
            if (cs[it.first] - pcs[it.first] >= it.second) { continue; }
            success = false; break;
        }
        if (success) { cout << s << std::endl; cout.flush(); break; }
    }
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) { solve(); }
}



