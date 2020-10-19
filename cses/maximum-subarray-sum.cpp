#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

// f0: using the classical kedane's solution

using ll = long long;
static const ll INFTY = 1000000000 + 7;

using namespace std;
namespace f0 {
int main() {
    ll n;
    cin >> n;
    vector<ll> xs(n);
    for (ll i = 0; i < n; ++i) {
        cin >> xs[i];
    }
    ll best_sum = -INFTY;
    ll sum = 0;

    // nonempty
    for (ll i = 0; i < n; ++i) {
        best_sum = max(best_sum, xs[i]);
    }
    for (ll i = 0; i < n; ++i) {
        if (sum + xs[i] <= 0) {
            sum = 0;
        } else {
            sum += xs[i];
            best_sum = max(sum, best_sum);
        }
    }

    cout << best_sum << "\n";
    return 0;
}
}  // namespace f0

namespace f1 {
int main() {
    ll n;
    cin >> n;
    vector<ll> xs(n);
    for (ll i = 0; i < n; ++i) {
        cin >> xs[i];
    }

    ll best = -INFTY;
    ll lowest = 0;
    ll height = 0;
    for(int i = 0; i < xs.size(); ++i) {
        height += xs[i];
        best = max(best, height - lowest);
        lowest = min(lowest, height);
    }
    cout << best << "\n";
    return 0;
}

}  // namespace f1
int main() {
    // f0::main();
    f1::main();
}
