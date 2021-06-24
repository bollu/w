#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <map>
using namespace std;



// greedy, naive
int main2() {
    int q; cin >> q;
    // Σn ≤ 200
    // q ≤ 200
    while(q--) {
        int n; cin >> n;
        vector<int> as(n);
        // 1 ≤ as[i] ≤ n
        for(int i = 0; i < n; ++i) { cin >> as[i]; }
        sort(as.begin(), as.end());

        // find injection f: [1..|t|] → N  to give
        // min[f] Σ[i] |t[i] - f[i]|
        static const int USED = 600;
        bool used[USED];
        int cost = 0;
        for(int i = 0; i < USED; ++i) { used[i] = false; }

        for(int i = 0; i < n; ++i) {
            int best = 1e9; int bestix = -1;
            for(int ix= 1; ix <= n; ++ix) {
                if (used[ix]) { continue; }
                int cost = abs(ix - as[i]);
                if (cost  < best) { bestix = ix; best = cost; };
            }
            used[bestix] = true;
            cost += best;
        }
        cout << cost << "\n";
    }
    return 0;
}



// proof?
// greedy, ""sophisticated""
int main3() {
    int q; cin >> q;
    // Σn ≤ 200
    // q ≤ 200
    while(q--) {
        int n; cin >> n;
        vector<int> as(n);
        // 1 ≤ as[i] ≤ n
        for(int i = 0; i < n; ++i) { cin >> as[i]; }
        sort(as.begin(), as.end());

        // find injection f: [1..|t|] → N  to give
        // min[f] Σ[i] |t[i] - f[i]|
        static const int USED = 600;
        bool used[USED];
        int cost = 0;
        for(int i = 0; i < USED; ++i) { used[i] = false; }

        for(int i = 0; i < n; ++i) {
            bool placed = false;
            for(int dist = 0; !placed; dist++) {
                if(as[i] - dist >= 1 && !used[as[i]-dist]) { 
                    // cerr << "placed " << as[i] << "  at " << as[i] - dist << "  cost " << dist << "\n";
                    used[as[i]-dist] = true; placed = true; cost += dist;
                } else if(!used[as[i]+dist]) { 
                    // cerr << "placed " << as[i] << "  at " << as[i] + dist << "  cost " << dist << "\n";
                    used[as[i]+dist] = true; placed = true; cost += dist;
                }
            }
        }
        cout << cost << "\n";
    }
    return 0;
}

