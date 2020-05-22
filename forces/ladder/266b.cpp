// http://codeforces.com/problemset/problem/266/B
#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    int n, t; cin >> n >> t;
    char cs[2][100];
    for(int i = 0; i < n; ++i) cin >> cs[0][i];

    int ix = 0;
    for (int i = 0; i < t; ++i) {
        for(int j = 0; j < n;) {
            if (j < n - 1 && cs[ix][j] == 'B' && cs[ix][j+1] == 'G') {
                cs[(ix+1)%2][j] = 'G'; cs[(ix+1)%2][j+1] = 'B';
                j += 2;
            } else {
                cs[(ix+1)%2][j] = cs[ix][j];
                j += 1;
            }
        }
        ix = (ix + 1) %2;
    }
    for(int i = 0; i < n; ++i) { cout << cs[ix][i]; }

    return 0;
}
