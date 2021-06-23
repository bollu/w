#include<iostream>
#include<vector>
using namespace std;

char b[1000+5][1000+5];

int main2() {
    int t; cin>> t; 
    while(t--) {
        int R, C; cin >> R >> C;
        int c1, c2; cin >> c1 >> c2;
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                cin >> b[r][c];
            }
        }

        // always use 1x1. 1x2 is useless.
        if (2*c1 <= c2) {
            int tot = 0;
            for(int r = 0; r < R; ++r) {
                for(int c = 0; c < C; ++c) {
                    tot += b[r][c] == '.' ? c1 : 0;
                }
            }
            cout << tot << "\n";
        } else {
            // useful to use as many 1x2 as possible per row.
            int tot = 0;
            for(int r = 0; r < R; ++r) {
                for(int c = 0; c < C;) {
                    if (b[r][c] == '.' && c+1 < C &&  b[r][c+1] == '.') {
                        tot += c2; c += 2;
                    } else {
                        if (b[r][c] == '.') { tot += c1; }
                        c += 1;
                    }
                }
            }

            cout << tot << "\n";
        }
    }
    return 0;
}
// nicer way to implement solution:
// 1. set price of 1x2 to be min(price of 1x1, 1x2)
// 2. Find strips of contiguous segments of length `k` in row, and paint them with `(k//2)*2` 1x2 tiles and a `k%2` 1x1 tile.
int main() {
    int t; cin>> t; 
    while(t--) {
        int R, C; cin >> R >> C;
        int c1, c2; cin >> c1 >> c2;
        // 1. set price of 1x2
        c2 = min(c2, 2*c1);
        for(int r = 0; r < R; ++r) {
            for(int c = 0; c < C; ++c) {
                cin >> b[r][c];
            }
        }

        int tot = 0;
        for(int r = 0; r < R; ++r) {
            // [left, right)
            int left = 0, right = 0;
            while(left < C) {
                if (b[r][left] != '.') { left++; continue; }
                right = left+1;
                while (right < C && b[r][right] == '.') { right++; }
                const int l = right - left;
                tot += (l/2)*c2 + (l%2)*c1;
                left = right;
            }
        }
        cout << tot << "\n";
    }
}
