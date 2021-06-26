#include<iostream>
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;

using ll = long long;

int ix(int i) { return i - 1; }
int main() {
    ios_base::sync_with_stdio(false);
    ll t; cin >> t; // t <= 1e4
    while(t--) {
        ll n; cin >> n; // n <= 1e5
        vector<ll> as(n);
        for(ll i = 0; i < n; ++i) {
            cin >> as[i];
        }

        std::sort(as.begin(), as.end());

        ll psum = 0;
        ll sum = 0;
        for(ll i = 2; i <= n; ++i) {
            ll delta = as[ix(i)] - as[ix(i-1)];
            psum += delta * ix(i);
            sum = sum + delta - psum;
        }
        cout << sum << "\n";

    }
    return 0; 
}
