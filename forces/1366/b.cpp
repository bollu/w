#include <iostream>
#include <set>
#include <stdio.h>
using namespace std;

#define N 1500
#define NDIG 10


void solve() {
    set<int> ss;
    int n; cin >> n;
    for(int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        ss.insert(s);
        // for(int j = 0; j < NDIG; ++j) { parities[i*NDIG+j] = ((s & (1 << j)) > 0) ? 1 : 0; }
        // printf("%4d  :[", s);
        // for(int j = NDIG-1; j >= 0; j--) { printf("%d ", parities[i][j]); }
        // printf("]\n");
    }

    int num = -1;
    for(int i = 1; i <= (1 << NDIG); ++i) {

        bool valid = true;
        for(int s : ss) {
            const int k = s ^ i;
            if (!ss.count(k)) { valid = false; break; }
        }
        if (valid) { num = i; break; }
    }

    cout << num << "\n";
}

// s -> s (+) k (k > 0)
int main() {
    int t; cin >> t;
    while(t--) solve();
    return 0;
}
