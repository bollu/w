#include <iostream>
using namespace std;

int a[1001][1001];
bool lft[1001][1001];
bool rit[1001][1001];
bool up[1001][1001];
bool dwn[1001][1001];

// AC, but long
int main2() {
    int r, c;
    cin >> r >> c;
    for(int rr = 0; rr < r; ++rr) {
        for(int cc = 0; cc < c; ++cc) {
            cin >> a[rr][cc];
        }
    }


    // <--
    for(int rr = 0; rr < r; ++rr) {
        for(int cc = 0; cc < c; ++cc) {
            lft[rr][cc] = (cc == 0 ? false : lft[rr][cc-1]) || a[rr][cc];
        }
    }

    // -->
    for(int rr = 0; rr < r; ++rr) {
        for(int cc = c-1; cc >= 0; --cc) {
            rit[rr][cc] = (cc == c-1 ? false : rit[rr][cc+1]) || a[rr][cc];
        }
    }

    // v
    for(int cc = 0; cc < c; ++cc) {
        for(int rr = 0; rr < r; ++rr) {
            dwn[rr][cc] = (rr == 0? false : dwn[rr-1][cc]) || a[rr][cc];
        }
    }

    // ^
    for(int cc = 0; cc < c; ++cc) {
        for(int rr = r-1; rr >= 0; --rr) {
            up[rr][cc] = (rr == r-1? false : up[rr+1][cc]) || a[rr][cc];
        }
    }

    int cnt = 0;
    for(int rr = 0; rr < r; ++rr) {
        for(int cc = 0; cc < c; ++cc) {
            if(a[rr][cc]) { continue; }
            cnt += lft[rr][cc] + rit[rr][cc] + up[rr][cc] + dwn[rr][cc];
        }
    }
    cout << cnt << "\n";
    return 0; 
}

// === fastest soln to implement, nice idea of using partial sums==
// int a[maxn][maxn];
const int maxn = 1005;
int s[maxn][maxn];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
 
	int n, m;
	cin >> n >> m;
 
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			cin >> a[i][j];
            // partial sum of top-left. subrectangle.
			s[i][j] = a[i][j] + s[i-1][j] + s[i][j-1] - s[i-1][j-1];
		}
	}
 
	int ans = 0;
 
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(a[i][j]) continue;
            // check if anything in row `i` exists
			if(s[i][j]-s[i-1][j] > 0) ans++;;
            // check if anything in column `i` exists
			if(s[i][j]-s[i][j-1] > 0) ans++;;

            // check if anything in row `i` exists
            //       j
            //   * * * * * *
            //   * * * * * *
            //   * * * * * *
            // i * * # * * *
            //   * * * * * *
            //   * * * * * *
            //   * * * * * *
            //   * * * * * *
            //       nj
            //
            //       j       nj        ij          n(j-1)     i(j-1)
            //   ------    @@@---    @@@---       @@----    @@----
            //   ------    @@@---    @@@---       @@----    @@----
            //   ------ =  @@@---    @@@---       @@----    @@----
            // i --#---    @@#--- -  @@#---  -    @@#--- +  --#---
            //   --@---    @@@---    ------       @@----    ------
            //   --@---    @@@---    ------       @@----    ------
            //   --@---    @@@---    ------       @@----    ------
            //   --@---    @@@---    ------       @@----    ------
			if((s[n][j]-s[i][j])-s[n][j-1]+s[i][j-1] > 0) ans++;;
			if((s[i][m]-s[i][j])-s[i-1][m]+s[i-1][j] > 0) ans++;;
		}
	}
 
	cout << ans;
 
	return 0;
}

