#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <assert.h>

using ll = long long;
using namespace std;
namespace f0 {
int main() { 
    int n; cin >> n;
    vector<int> ks(n);
    for(int i = 0; i < n; ++i) { cin >> ks[i]; }
    
    set<int> uniques;
    int maxlen = 0;
    int l = 0, r = 0;
    while(r < n) {
        if (!uniques.count(ks[r])) {
            uniques.insert(ks[r]);
            r++;
            maxlen = max<int>(maxlen, r - l);
        } else {
            while (uniques.count(ks[r])) {
                auto it = uniques.find(ks[l]);
                assert(it != uniques.end());
                uniques.erase(it);
                ++l;
            }
        }
    }
    cout << maxlen << "\n";
    return 0;
}
}

namespace f1 {
int main() { 
    int n; cin >> n;

    map<int, int> last_occur;
    int maxlen = 0;
    int maxchopoff = 0;
    for(int i = 1; i <= n; ++i) {
        int k; cin >> k;

        auto it = last_occur.find(k);
        int chopoff  = it == last_occur.end() ? 0 : it->second;
        maxchopoff = max(chopoff, maxchopoff);

        int len = i - maxchopoff;
        maxlen = max(len, maxlen);
        last_occur[k] = i;
    }
    cout << maxlen << "\n";
    return 0;
}
}

int main() {
    // f0::main();
    f1::main();
}
