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

const ll INFTY = 100000000000000;

void solve(){
  ll W, H; cin >> W >> H;
  ll x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
  ll wt = x2 - x1; ll ht = y2 - y1;
  assert(wt >= 0); assert(ht >= 0);
  
  ll w, h; cin >> w >> h;


  ll best = INFTY;
  // place left.
  if (h <= H && wt + w <= W)  {
    best = min<ll>(best, max<ll>(w - x1, 0));
  }

  // place right
  if (h <= H && wt + w <= W) {
    int right = W - w;
    int pierce = max<ll>(x2 - right, 0);
    best = min<ll>(best, pierce);
  }

  // place top
  if (w <= W && ht + h <= H) {
    int top = H - h;
    int pierce = max<ll>(y2 - top, 0);
    //                 
    //           --- H
    // ----- y2  |  | 
    //           |  |h
    // |         ---  H-h=top
    // |
    // -----
    best = min<ll>(best, pierce);
  }
  // place bot
  if (w <= W && ht + h <= H) {
    //|
    // ---- y1
    //
    // ----
    //|   |h
    //*----
    best = min<ll>(best, max<ll>(h - y1, 0));
  }

  if (best == INFTY) { cout << -1 << "\n"; }
  else { cout << best << "\n"; }

  
}
int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
      solve();
    }

}

