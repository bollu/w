// https://codeforces.com/contest/289/submission/3547435
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;
const ll INF = (ll) 1e9;

ll as[100L*100L + 5];
ll ds[100L*100L + 5];
int n, m, d; 

ll myabs(ll x) { return x >= 0 ? x : -x; }
ll cost(ll ix) {
    ll c = 0;
    for(int i = 0; i < n*m; ++i) { c += myabs(ds[i] - ix); }
    return c;
}

int main() {
    // cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> n >> m >> d;
    for(int i = 0; i < n*m; ++i) { cin >> as[i];  }
    for(int i = 0; i < n*m; ++i) { if (as[i] % d != as[0] % d) { cout << -1; return 0; }}
    for(int i = 0; i < n*m; ++i) { ds[i] = as[i]/d; assert(as[i] == ds[i]*d + (as[0]%d)); }
    const ll nelem = n * m;
    sort(as, as + nelem);
    ll sum = 0; for(int i = 0; i < n*m; ++i) { sum += as[i]; }
    ll res = INF;
    for (int i = 0; i < nelem; i++) {
        // (i + 1) + (n - i - 1) = n
        res = min(res, sum - nelem * ds[i]);
    }
    printf("%d\n", res);
		//break;


    return 0;
}

