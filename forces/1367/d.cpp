#include <iostream>
#include <assert.h>
#include <map>
#include <vector>
using namespace std;

char buf[2000];

void solve() {
    string s; cin >> s;

    map<int, char> lsmap;
    for(int i = 0; i < s.size(); ++i) {
        int tot = 0;
        for(int j = 0; j < s.size(); ++j) { if (s[j] > s[i]) { tot += abs(i - j); } }
        lsmap[tot] = s[i];

    }

    cerr << "\nvvv\n";
    for(auto it : lsmap) {
        cerr << it.first << " = " << it.second << "\n";
    }
    cerr << "^^^\n";

    int n; cin >> n;
    for(int i = 0; i < n; ++i) {
        int ix; cin >> ix;
        assert(lsmap.find(ix) != lsmap.end());
        buf[i] = lsmap[ix]; 
    }
    buf[n] = 0;
    cout << buf << "\n";
    cerr << "ANSWER:" << buf << "\n";


}

int main() {
    int t; cin >> t;
    while(t--) solve();
    return 0;
}
