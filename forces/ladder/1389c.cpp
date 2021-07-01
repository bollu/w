#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

// fabcde = bcdefa
// 123456   123456
//
// f=b (1=3)
// a=c (2=4)
// b=d (3=5)
// c=e (4=6)
// d=f (5=1)
// e=a (6=2)
//
// tpqrs = qrstp
// 12345   12345
//
// t=q (1=3)
// p=r (2=4)
// q=s (3=5)
// r=t (4=1)
// s=p (5=2)
static const int N = 2e5 + 10;
int dp[N][2]; 
// dp[i][X]: min # of chars to delete to
// make string become XYXYXYXYXY...X
int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    // total length of strings: 2e5
    // odd: greedy
    // even: choose two characters such that #other chars is smallest: 10^2
    while (t--) {
        string s;
        cin >> s;
        // even.
        static const int I = 0;
        static const int J = 1;
        int best = 1e9;
        for (int i = 0; i <= 9; ++i) {
            for (int j = 0; j <= 9; ++j) {
                // cerr << "dp[" << i << " " << j << "]\n";
                for (int ix = 0; ix < s.size(); ++ix) {
                    dp[ix][I] = 1e9;
                    dp[ix][J] = 1e9;
                    const char c = s[ix];
                    if (c - '0' == i) {
                        if (ix == 0) {
                            dp[ix][I] = min(dp[ix][I], 0);
                        } else {
                            dp[ix][I] = min(dp[ix][I], dp[ix - 1][J]);
                        }
                    }
                    if (c - '0' == j) {
                        if (ix == 0) {
                            dp[ix][J] = min(dp[ix][J], 0);
                        } else {
                            dp[ix][J] = min(dp[ix][J], dp[ix - 1][I]);
                        }
                    }
                    if (ix == 0) {
                        // delete current char.
                        // vacuously create string ending with I, J.
                        dp[ix][I] = min(dp[ix][I], 1);
                        dp[ix][J] = min(dp[ix][J], 1);
                    } else {
                        // delete current char.
                        // use prev. string ending with I ,
                        // with one extra cost to delete.
                        dp[ix][I] = min(dp[ix][I], dp[ix - 1][I] + 1);
                        dp[ix][J] = min(dp[ix][J], dp[ix - 1][J] + 1);
                    }
                    // cerr << "\tdp[" << ix << "] = " << 
                    //  dp[ix][I] << " " << dp[ix][J] << "\n";
                }

                // if odd, then we need to delete one more characer to make it even.
                if (i != j && (s.size() - dp[s.size()-1][I]) % 2 == 1) {
                    dp[s.size()-1][I] += 1;
                }

                if (i != j && (s.size() - dp[s.size()-1][J]) % 2 == 1) {
                    dp[s.size()-1][J] += 1;
                }

                best = min(min(best, dp[s.size()-1][I]), dp[s.size()-1][J]);

                // cerr << "\tbest [" << i << " " << j << "] = " << best << "\n";
            }
        }
        cout << best << "\n";
    }  // end t--

    return 0;
}

