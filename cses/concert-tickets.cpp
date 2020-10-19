#include <assert.h>

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

// https://stackoverflow.com/questions/4212225/most-efficient-data-structure-fast-sorted-insertion-closest-value-searching
// https://stackoverflow.com/questions/37294267/c-set-find-value-smaller-but-closer-to-x


struct GtInt {
    int i; GtInt(int i) : i(i) {}
};
int main() {
    int n, m;
    cin >> n >> m;

    multiset<int> tickets;
    for(int i = 0; i < n; ++i) { int h; cin >> h; tickets.insert(h); }
    for(int i = 0; i < m; ++i) {
        int t; cin >> t;
        // lower bound: first (>= KEY)
        // upper bound: first (> KEY)
        //
        // find item that is *just after*. Decrement it to get item that is
        // just before. So we have:
        //
        //
        //       | lower  |upper
        //       | bound  |bound
        //       | v      |v
        // < < < | = = = =| > > > > >
        //
        // Case 2: no elements equal to search
        //       |upper     lower
        //       |bound     bound
        //       |v         v
        //       |v---------v
        //       |v
        // < < < | > > > > >
        auto it = tickets.upper_bound(t);
        if (it == tickets.begin()) {
            cout << -1 << "\n";
        } else {
            it--;
            // cout << "demand: " << t << " | closest: " << *it << "\n";
            cout << *it << "\n";
            tickets.erase(it);
        }
    }
    return 0;
}
