#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
 
const ll mod = 1e9 + 7;
 
ll val(ll n) { return (n * (n + 1))/2; }
 
int main() {
#ifdef LOCAL_EXEC
//    freopen("sample.in", "r", stdin);
#else
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#endif
 
  int n;
  ll x;
  cin >> n >> x;
  int d[2000006];
  ll tot = 0, sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> d[i];
    d[n + i] = d[i];
  }
  n *= 2;
  ll ans = 0;
  int l = 0;
  for (int i = 0; i < n; i++) {
    tot += d[i];
    sum += val(d[i]);
    while (tot - d[l] >= x) {
      tot -= d[l];
      sum -= val(d[l]);
      l++;
    }
    if (tot >= x) {
      ans = max(ans, sum - val(tot - x));
    }
  }
 
  cout << ans << '\n';
 
	return 0;
}

