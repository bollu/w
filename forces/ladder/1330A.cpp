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
        int n,x; cin >> n >> x;
        bool contests[501];
        for(int i = 1; i <= 500; ++i) { contests[i] = false; }
        for(int i = 1; i <= n; ++i) { int a; cin >> a; contests[a] = true; }
        for(int i = 1, xcur = 0; i <= 500 && xcur < x; ++i) { 
            if (!contests[i]) { contests[i] = true; xcur++; }
        }
        int ix = 1;
        while(ix <= 500 && contests[ix+1]) { ix++; }
        cout << ix << "\n";

    }
    return 0;
}

