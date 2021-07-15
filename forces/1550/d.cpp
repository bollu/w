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

static const ll MOD = 1e9 + 7;

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while (t--) {
        ll n, l, r; cin >> n >> l >> r;
        // ai - i = const.
        // ai != i => ai - i != 0
        // l ≤ ai ≤ r ⇒ ai ∈ [l, r] ⇒ # vals is (r-l+1)
        // ai - i = k
        //
        // l <= ai <= r
        // 1 <= i <= n
        //
        // 1-l <= ai - i <= r - n
        //
        // ai - i ∈ [1-l, r-n]
        ll right = r - n;
        ll left = l - 1;

        ll ans = (right - left + 1) - 1;
        ans = max<ll>(ans, 0);

        cout << ans % MOD << "\n";
    }
}

