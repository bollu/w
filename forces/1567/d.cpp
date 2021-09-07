#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

vector<int> f(int sum, int n) {
    assert(sum >= n);
    vector<int> outs;
    while (n > 0) {
        if (n == 1) {
            // have used all numbers save 1.
            outs.push_back(sum);
            break;
        }
        int pow10 = 1;
        assert(pow10 <= sum);
        while (1) {
            const int nextpow10 = pow10 * 10;
            if (!(nextpow10 <= sum)) { break; }
            if (!(sum - nextpow10 >= n-1)) { break; }
            pow10 = nextpow10;
        }
        assert(pow10 <= sum);
        assert(sum - pow10 >= n-1);
        // assert(pow10 * 10 > sum);
        // [untrue; we may quit because we need to produce many numbers.
        // eg: sum = 10, n = 10. We will have pow10 = 1]
        outs.push_back(pow10);
        sum -= pow10;
        n--;
    }
    return outs;
}

void solve() {
    int s, n;
    cin >> s >> n;
    vector<int> outs = f(s, n);
    for (int i : outs) {
        cout << i << " ";
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;

    while (t--) {
        solve();
    }
}
