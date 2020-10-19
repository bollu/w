#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <assert.h>

namespace f0 {

struct interval {
    int start, end;
};

bool covered(const interval &i, const interval &j) { return i.end < j.start; }

std::ostream &operator<<(std::ostream &o, const interval &i) {
    return o << "[" << i.start << " " << i.end << "]";
}

using namespace std;
int main() {
    int n;
    cin >> n;
    vector<interval> es(n);
    vector<int> ixs_start(n);
    vector<int> ixs_end(n);
    vector<int> chain_len(n);

    for (int i = 0; i < n; ++i) {
        cin >> es[i].start >> es[i].end;
        ixs_start[i] = ixs_end[i] = i;
        chain_len[i] = 0;
    }
    std::sort(ixs_start.begin(), ixs_start.end(),
              [&es](int i, int j) { return es[i].start < es[j].start; });

    std::sort(ixs_end.begin(), ixs_end.end(),
              [&es](int i, int j) { return es[i].end < es[j].end; });

    // pick the job that ends last, since that's going to be
    // the final event.
    chain_len[ixs_end[n-1]] = 1;

    set<int> seen;
    stack<pair<int, int>> stack_ixlen;

    // process from end
    for(int i = n - 1; i >= 0; i--) {
        if (seen.count(ixs_end[i])) { continue; }
        stack_ixlen.push({ixs_end[i], 1});
        while (!stack_ixlen.empty()) {
            int ix, len;
            std::tie(ix, len) = stack_ixlen.top();
            stack_ixlen.pop();
            if (seen.count(ix)) { continue; }
            seen.insert(ix);

            // find all things that start where this ends.
            int lo = 0, hi = n;
            while(hi - lo > 1) {
                int mid = (lo + hi)/2;
                if (ixs_start[mid] < ixs_start[ix]) { lo = mid; }
                else { hi = mid; }
            }
            assert(lo == hi);
        }
    }


    return 0;
}
}  // namespace f0

int main() { return f0::main(); }
