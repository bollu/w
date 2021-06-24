#include<map>
#include<utility>
using namespace std;
using ll = long long;

map<pair<ll, ll>, pair<ll, ll>> M;
 
pair<ll, ll> Solve(ll n, ll mn = 0) {
	if (M.count(make_pair(n, mn)) != 0) {
		return M[make_pair(n, mn)];
	}

    // ???
	if (n <= 0) { return make_pair(0, -n); }

	ll nn = n;
    // 18?
	ll mx = 1000000000000000000LL;
	ll ret = 0;
	for (int i = 0; i < 19; ++i) {
		if (n / mx > 0) {
   			while (n / mx > 0) {
				pair<ll, int> par = Solve(n % mx, max(mn, n / mx));
				ret += par.first;
				n -= n % mx + par.second;
				if (par.second == 0) {
					++ret;
					n -= max(mn, n / mx);
				}
			}
		}
		mx /= 10;
	}
	if (n < 0) {
		n = -n;
	}
	return M[make_pair(nn, mn)] = make_pair(ret, n);
}
 

