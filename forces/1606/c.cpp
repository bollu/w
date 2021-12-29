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

// void solve() {
//     int n, k; cin >> n >> k;
//     int as[10];
//     for(int i = 0; i < n; ++i) { cin >> as[i]; }
// 
//     cout << k + 1;
//     for(int i = 0; i < as[n-1]; ++i) {
//         cout << "0";
//     }
//     cout << "\n";
// }


ll pow10(const ll n) {
  ll out = 1;
  for(int i = 0; i < n; ++i) { out *= 10; }
  return out;
}


void solve() {
    ll n, k; cin >> n >> k;
    ll as[10];
    for(ll i = 0; i < n; ++i) { cin >> as[i]; }

    ll leftk = k;
    string s = "";
    for(int ix = 0; ix < n - 1 && leftk > 0; ++ix) {
      ll space = pow10(as[ix + 1]) - pow10(as[ix]);
      ll delta = min(space, leftk);
      s = std::to_string(delta) + s;
      leftk -= delta;
    }
    if (leftk == 0) {
      cout << s << "\n";
      return;
    } else {
      s = std::to_string(leftk) + s;
      cout << s << "\n";
      return;
    }

}

int main() {
    int t; cin >> t; while(t--) { solve(); }
}
