using namespace std;
#include "assert.h"
#include <vector>
#include <iostream>

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> as(n+1);
        int ixs[2];
        for(int i = 1; i <= n; ++i) {
            cin >> as[i];
            if (as[i] == 1) { ixs[0] = i; }
            if (as[i] == n) { ixs[1] = i; }
        }
        if (ixs[0] > ixs[1]) {
            int temp = ixs[0];
            ixs[0] = ixs[1];
            ixs[1] = temp;
        }
        // ixs[0] < ixs[1].
        //            [4,     8]. length of closed-closed interval=r-l+1
        // ixs:[1 2 3 4 5 6 7 8] (n=8)
        //            ^
        //            4 5 6 7 8 (5)
        assert(ixs[0] < ixs[1]);
        std::cout << std::min<int>(ixs[1], std::min<int>(n - ixs[0]+1, ixs[0] + (n - ixs[1]+1))) << "\n";
    }
    return 0;
}
