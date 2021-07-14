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

static const ll MOD = 1e9 + 7;
static const int LEN = 2e5 + 10;
ll add (ll a, ll b) {
    return (a + b) % MOD;
}
int sum[LEN];

ll count(vector<int> &as, ll l, ll r) {
    assert(r >= l);
    return sum[r-l];
}

// [l..r) is good.
ll good(multiset<int> &ss, vector<int> &as, ll l, ll r) {
    assert(l >= 0);
    assert(r >= 0);
    r = min<ll>(r, as.size() - 1);
    assert(l < as.size());
    assert(r < as.size());
    assert(l <= r);
    // find element in range [l, r]
    bool contains_elements_in_range = ss.lower_bound(as[l]) != ss.upper_bound(as[r]);
    // if it has an element in range, it's a bad array.
    return !contains_elements_in_range;
}

void addinfo(multiset<int> &ss, vector<int> &as, ll r) {
    if (r+1 >= as.size()) { return; }
    ss.insert(as[r+1]);
}

void reminfo(multiset<int> &ss, vector<int> &as, ll l) {
    if (l+1 >= as.size()) { return; }
    ss.erase(as[l+1]);
}

int main() {
    ios::sync_with_stdio(false);
    // sum[n] = 1 + 2 + ... n
    sum[0] = 0;
    for(int i = 1; i < LEN; ++i) { sum[i] = add(i, sum[i-1]); }
    int t;
    cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<int> as(n);
        for(int i = 0; i < n; ++i) { cin >> as[i]; }

        multiset<int> ss;
        // subarray [l..r] is good if there
        // is a point inside [l.i...r] such that a[l] <= a[i] <= a[r].
        // how to check this efficiently? :( 
        ll tot = 0;
        ll l = 0, r = 0;
        while(r < n) {
            while(r < n && good(ss, as, l, r)) {
                addinfo(ss, as, r);
                r++;
            }
            tot += count(as, l, r);
            while(l < r && !good(ss, as, l, r)) { 
                reminfo(ss, as, l);
                l++;
            }
        }
        cout << tot << "\n";
    }

}

