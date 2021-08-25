#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> vs(n);
        for(int i =  0; i < vs.size(); ++i) { cin >> vs[i]; }
        int out = vs[0];
        for(int i = 1; i < vs.size(); ++i) { out &= vs[i]; }
        cout << out << "\n";
    }
    return 0;
}


