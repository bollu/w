#include <iostream>
#include <string>
using namespace std;

int n, m;
int whites[105][1005];
int icum[105][1005];
int jcum[105][1005];
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
            for(int i = 0; i < n; ++i) {
                jcum[i][0] = whites[i][0];
                for(int j = 1; j < m; ++j) {
                    jcum[i][j] = jcum[i][j-1] + whites[i][j];
                }
            }

            for(int j = 0; j < m; ++j) {
                icum[0][j] = whites[0][j];
                for(int i = 1; i < n; ++i) {
                    icum[i][j] = icum[i-1][j] + whites[i][j];
                }
            }

            int total = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < m; j++) {
                    if (!whites[i][j]) { continue; }
                    if (covered[i][j]) { continue; }
                    bool iw = i + 1 < n && whites[i+1][j];
                    bool jw = j + 1 < m && whites[i][j+1];

                    if (iw && jw) {
                        // need to decide to use iw or kw
                        if (icum[i+1][j] % 2 == 0) { 
                            covered[i][j] = covered[i][j+1] = true;
                            total += y;
                        } 
                        else {
                            covered[i][j] = covered[i+1][j] = true;
                            total += y;
                        }
                    } else if (iw) {
                        covered[i+1][j] = true; total += y;
                    } else if (jw) {
                        covered[i][j+1] = true; total += y;
                    } else { 
                        covered[i][j] = true; total += x;
                    }
                }
            }

            cout << total << "\n";
        }
    }
}
