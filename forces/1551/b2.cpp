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
// elements are either painted or unpained.
// no equal values are painted same color.
// each color is painted with equal # of element.
// total number of painted elements is maximum.


int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> as(n);
    vector<int> assigns(n, 0);
    for (int i = 0; i < n; ++i) {
      cin >> as[i].first;
      as[i].second = i;
    }

    sort(as.begin(), as.end());
    int cur = -1;
    int curcount = 0;
    int turn = 1;

    int npaints = 0;
    
    // last index such that [0..i) color is sealed (ie, all became equal.)
    set<int> lastset;

    for(auto it : as) {
        if (cur == it.first) {
            curcount++;
        } else {
            curcount = 0;
        }
        cur = it.first;        
        if (curcount >= k) {
            continue;
        }
        assigns[it.second] = turn;
        lastset.insert(it.second);
        turn++;
        if (turn > k) { turn = 1; lastset.clear(); npaints++; }
    }

    for(auto i: lastset) {assigns[i] = 0; }

    for(int i = 0; i < n; ++i) {
        cout << assigns[i] << " ";
    }
    cout << "\n";
  }
}
