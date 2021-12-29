#include <algorithm>
#include <assert.h>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const int M = 300 + 10;
const int N = 300 + 10;
void solve() {
    int sight[N][M];
    int n; int m; cin >> n >> m;
    // name iterator over length N with Ni etc.
    for(int mi = 0; mi < m; ++mi) {
        for(int ni = 0; ni < n; ++ni) {
            cin >> sight[ni][mi];
        }
    }

}

int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--) { solve(); }

}
