#include <assert.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const ll INFTY = 1e5;
int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;

    while (t--) {
      int n; cin >> n;
      vector<pair<ll, ll>> as(n);

      int maxix = -1; int largest = -1;
      for(int i = 0; i < n; ++i) {
	as[i].second = i;
	cin >> as[i].first;
      }


      ll best = -1;
      for(int i = 0; i < n-1; ++i) {
	best = max<ll>(best, as[i].first * as[i+1].first);
      }
      cout << best << "\n";
    }
}

