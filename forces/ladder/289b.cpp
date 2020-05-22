#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;

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

    ll l = ds[0], r = ds[0];
    for(int i = 0; i < n*m; ++i) { l = std::min<ll>(l, ds[i]); r = std::max<ll>(r, ds[i]); }


    if(1) {
        ll  mincost = cost(l);
        for(int i = 0; i <= r+1; ++i) {
            const ll c = cost(i);
            mincost = std::min<ll>(c, mincost);
        }  
        cout << mincost; return 0;
    }
    
    /*
    while(l != r) {
        const ll m1 = l + (r - l)/4, m2 = l + 2 * (r - l) / 4, m3 = l + 3*(r-l)/4;

        if(1) {
            cerr << "cost[" << d*m1 << "] := " << cost(m1) << 
                " |cost[" << d*m2 << "] := " << cost(m2) <<
                " |cost[" << d*m3 << "] := " << cost(m3) << "\n";
        }

        if (cost(m1) <= cost(m2)) {
            if (cost(m2) <= cost(m3)) { r = m3; }
            else { l = m1; r = m3; }
        } 
        else { 
            // cost(m1) >= cost(m2)
            if (cost(m2) < cost(m3)) { assert(false && "impossible."); }
            // m1 > m2 > m3
            else { l = m3; }
         }
    }

    ll mincost = cost(l);
    for(int i = l; i <= r; ++i) {
        mincost = min(mincost, cost(i)); 
    }
    cout << mincost;

    */

    return 0;
}

