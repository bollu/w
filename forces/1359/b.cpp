#include <iostream>
#include <string>
using namespace std;

int n, m;
int whites[105][1005];
bool covered[105][1005];
int x, y;

int main() {
    int t; cin >> t;
    while(t--) {
        cin >> n >> m >> x >> y;
        for(int i = 0; i < n; ++i) {
            string s; cin >> s;
            for (int j = 0; j < m; ++j) {
                whites[i][j] = s[j] == '.';
                covered[i][j] = false;
            }
        }

        if (y >= 2 * x) {
            int t = 0;
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < m; ++j) {
                    t += whites[i][j] ? x : 0;
                }
            }
            cout << t << "\n";
        } else {
            int total = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if (!whites[i][j]) { continue; }
                    if (covered[i][j]) { continue; }
                    bool jw = j + 1 < m && whites[i][j+1];
                    if (jw) {
                        covered[i][j+1] = true; total += y;
                    } else {
                        covered[i][j] = true;
                        total += x;
                    }
                }
            }

            cout << total << "\n";
        }
    }
}
