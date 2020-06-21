#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
static const int INFTY = 10000000;

enum S { FINDMID, FINDRIGHT };

void solve() {
    int n, k; cin >> n >> k;
    string s; cin >> s;
    vector<int> bs;
    bs.push_back(-(k+1));
    for(int i = 0; i < n; ++i) {
        if (s[i] == '1') bs.push_back(i); 
    }
    bs.push_back(n+k);
    int tot = 0;
    for(int i = 0; i < bs.size()-1; ++i) {
        tot += (bs[i+1] - bs[i] - 1) / (2*k+1);
    }
    // cerr << "tot: " << tot << "\n";
    cout << tot << "\n";


}

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        solve();

    }
    return 0;
}
