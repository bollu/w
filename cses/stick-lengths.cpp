#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <assert.h>

// https://math.stackexchange.com/questions/113270/the-median-minimizes-the-sum-of-absolute-deviations-the-ell-1-norm

using ll = long long;
const ll INFTY = INT64_MAX;
using namespace std;
int main() { 
    int n; cin >> n;
    vector<ll> ps(n);

    for(int i = 0; i < n; ++i) { cin >> ps[i]; }

    std::sort(ps.begin(), ps.end());

    ll best = INFTY;
    for(int i = max<int>(0, ps.size()/2-1); i < min<int>(ps.size()/2+1, ps.size()); ++i) {
        ll dist  = 0;
        for(int j = 0; j < n; ++j) { dist += abs(ps[j] - ps[i]); }
        best = min<ll>(best, dist);
    }
    cout << best << "\n";
    return 0;
}
