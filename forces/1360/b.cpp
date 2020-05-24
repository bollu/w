#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int ss[100];
        for(int i = 0; i < n; ++i) { cin >> ss[i]; }
        sort(ss, ss+n);
        static const int INFTY = 5000;
        int minval = INFTY;
        for(int i = 0; i < n-1; ++i) {
            minval = min<int>(minval, abs(ss[i] - ss[i+1]));
        }
        cout << minval << "\n";
    }
    return 0;
}

