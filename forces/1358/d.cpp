// https://codeforces.com/contest/1358/problem/D
#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;
static const int NMAX = 10000000;

using ll = long long;

ll month2days[NMAX];
ll cumdays[NMAX];
ll cumhugs[NMAX];

ll s(ll n) { return (n * (n+1))/2; }

int main() {
    ll n, vacdays; cin >> n >> vacdays;

    for(ll i = 1; i <= n; ++i) {
        cin >> month2days[i]; month2days[i+n] = month2days[i];
    }

    n = 2*n;
    cumdays[0] = 0;
    cumhugs[0] = 0;
    for(ll i = 1; i <= n+1; ++i) {
        cumdays[i] = cumdays[i-1] + month2days[i];
        cumhugs[i] = cumhugs[i-1] + s(month2days[i]);
    }

    ll ans = 0;
    ll l = n;
    for(ll r = n+1; r >= 1; r--) {
        while(l >= 1 && cumdays[r] - cumdays[l] < vacdays) {
            if (cumdays[r] - cumdays[l-1] >= vacdays) break;
            l--;
        }
        ll months_days = cumdays[r] - cumdays[l];
        ll left = vacdays - months_days;
        ll months_hugs = cumhugs[r] - cumhugs[l];
        ll leftoverhugs = s(month2days[l]) - s(month2days[l] - left);
        ans = max(ans, months_hugs + leftoverhugs);
    }
    cout << ans << "\n";
    return 0;
}
