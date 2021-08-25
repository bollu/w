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


int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while (t--) {
    vector<int> counts(5, 0);
    int n; cin >> n;
    vector<string> xs(n);
    for(int i = 0; i < n; ++i) {
        cin >> xs[i];
        for(char c : xs[i]) {
            counts[c - 'a']++;
        }
    }
    int sum = 0;
    for(int i = 0; i < 5; ++i) { sum += counts[i]; }

    int best = -1; int bestmargin = -1;
    for(int i = 0; i < 5; ++i) {
        int rest = sum - counts[i];
        int margin = counts[i] - rest;
        if (margin > 0 && margin > bestmargin ) { best = i; bestmargin = margin; } 
    }

    if (best == -1) {
        cout << 0 << "\n";
    } else {
        vector<int> xs;
    }
  }
}
