#include <iostream>
using namespace std;

// #1   #2    split
// 1    1       x
// 2    1      (2x[1$], 1x[2$])
// 3    1       x
// 4    1      (3x[1$], 1x[1$]+1x[2$])
// 1    2      x
// 2    2      (1x[1$] + 1x[2$], 1x[1$] + 1x[2$])
// 3    2      x
// 4    2      (2x[1$] + 1x[2$], 2x[1$] + 1x[2$])
// 1    3      x
// 2    3      (2x[1$] + 1x[2$], 2x[2$])
// 3    3      
// 4    3
// 1    4
// 2    4
// 3    4 
// 4    4

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        int n1s = 0, n2s = 0;
        for(int i = 0; i < n; ++i) {
            int a; cin >> a;
            if (a == 1) n1s++;
            else n2s++;
        }


        // number of candies of weight 2 to give to alice
        bool success = false;
        for(int i = 0; i <= n2s; ++i) {
            // number of candies of weight 1 to give to alice
            for(int j = 0; j <= n1s; ++j) {
                if (i*2 + j*1 == (n2s - i)*2 + (n1s - j)*1) {
                    cout << "YES\n";
                    success = true;
                    break;
                }
            }
            if (success) { break; }
        }
        if (!success) { cout << "NO\n"; }
    }
}
