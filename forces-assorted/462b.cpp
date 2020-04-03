#include <iostream>
#include <algorithm>
using namespace std;
using ll = long long;

ll counts[26];
int main() {
    int n, k; cin >> n >> k;
    for(ll i = 0;  i < n; ++i) { char c; cin >> c; counts[c - 'A']++; }
    sort(counts, counts+26, [](ll a, ll b) { return a > b; });

    ll score = 0, kleft = k, ix = 0;
    while(ix < 26 && kleft > 0) {
        const ll take = min(kleft, counts[ix]);
        kleft -= take;
        score += take * take;
        ix++;
    }

    cout << score;

    return 0;
}
