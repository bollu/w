#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;

struct info {
    ll t, lo, hi;
};

int n, m; 
int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        
        vector<info> vs(n);
        for(int i = 0; i < n; ++i) {
            cin >> vs[i].t >> vs[i].lo >> vs[i].hi;
        }

        bool success = true;
        // nice, use non-determinism!
        // we are in some sense exploring all paths.
        ll minv = m, maxv = m, tcur = 0;
        for(int i = 0; i < n; ++i) {

            ll dt = vs[i].t - tcur;
            minv -= dt;
            maxv += dt;

            // [miv...maxv][lo...hi]
            // [lo..hi][miv...maxv]
            if (maxv < vs[i].lo || vs[i].hi < minv) {
                success = false; break;
            }

            // (a) [minv..[lo..hi]..maxv]
            
            // (b)
            // [minv......maxv]
            //    [lo.............hi]


            // (c)
            // [lo.............hi]
            //       [minv......maxv]

            minv = max<ll>(minv, vs[i].lo);
            maxv = min<ll>(maxv, vs[i].hi);
	       tcur = vs[i].t;
        }

        if (success) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }

    }
    return 0;
}


