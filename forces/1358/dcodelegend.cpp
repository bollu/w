#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using PII = pair<int, int>;
using VI = vector<int>;
 
ll sumn(ll n) {
  if (n <= 0) return 0;
  return (n * (n + 1)) / 2;
}
 
int main() {
#ifdef LOCAL_EXEC
//	freopen("sample.in", "r", stdin);
//	freopen("sample.out", "w", stdout);
#else
  ios_base::sync_with_stdio(false); cin.tie(NULL);
#endif
 
  int n; ll x; cin >> n >> x;
  vector<int> d(n);
  for (int& y: d) cin >> y;
 
  for (int i = 0; i < n; i++) {
    d.push_back(d[i]);
  }
 
  ll ans = 0;
  // for (auto _: {0, 1}) {
  for (auto _: {0}) {
    (void)_;
    deque<ll> sizes;
    ll cur = 0, tot = 0;
    for (int i = 0; i < 2 * n; i++) {
      cur += d[i]; // number of days.
      tot += sumn(d[i]);
      sizes.push_back(d[i]);
      while (cur > x) {
        int sz = sizes.front();
        if (cur - sz >= x) {
          cur -= sz;
          tot -= sumn(sz);
          sizes.pop_front();
        } else {
          break;
        }
      }
      ans = max(ans, tot - sumn(cur - x));
    }
    reverse(d.begin(), d.end());
  }
 
  cout << ans << endl;
 
  return 0;
}

