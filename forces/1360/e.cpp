#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;

// 00101001
// 00111101
// 00101001
// 00101001

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        bool a[n][n];

        bool allzeros = true;
        for(int i =0; i < n; ++i) {
            string s; cin >> s;
            for(int j = 0; j < n; ++j) {
                a[i][j] = s[j] == '1';
                allzeros &= !a[i][j];
            }
        }
        if (allzeros) { cout << "YES" << "\n"; continue; }

        bool success = true;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if (a[i][j]  && !((!(j+1<n) || a[i][j+1]) || 
                                 ((!(i+1<n) || a[i+1][j])))) { 
                    success = false;
                    break;
                }
            }
        }

        cout << (success ? "YES\n" : "NO\n");
    }
}
