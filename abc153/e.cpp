#include <assert.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define K 100001
#define INF 1e7
using namespace std;
using I = long long int;
I a[10001], b[10001];
I dp[10001];
I h; I n;  
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    cin >> h >> n;
    for(int i = 0; i < n; ++ i) { cin >> a[i] >> b[i]; }
     dp[0] = 0;
     for (int i = 1; i <= h; ++i) {
         dp[i] = INF;
         for(int j = 0; j < n; ++j) {
             dp[i] = min<I>(dp[i], dp[max<I>(0, i - a[j])] + b[j]);
         }
     }
    cout << dp[h];
}
