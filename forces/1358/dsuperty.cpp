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
  ll maxdays;
  cin >> n >> maxdays;
  int m2days[2000006];
  ll cumdays = 0, cumhugs = 0;
  for (int i = 0; i < n; i++) {
    cin >> m2days[i];
    m2days[n + i] = m2days[i];
  }
  // n *= 2;
  ll ans = 0;
  int l = 0;
  for (int i = 0; i < n*2; i++) {
    cumdays += m2days[i]; cumhugs += val(m2days[i]);

    // if on removal of the month, we still are larger than max days, then
    // remove the month. We want to find the "tighest" block of legal
    // months.
    while (cumdays - m2days[l] >= maxdays) { 
        cumdays -= m2days[l];
        cumhugs -= val(m2days[l]);
        l++;
    }

    // if we have leftover days
    // (that don't fit in a month; if they did, we would have removed it)
    // then remove them before accumulating the answer. We remove them from
    // the _first_ segment, so we remove `val(cumdays - maxdays)`.
    if (cumdays >= maxdays) { 
        ans = max(ans, cumhugs - val(cumdays - maxdays));
    }
  }
 
  cout << ans << '\n';
 
	return 0;
}

