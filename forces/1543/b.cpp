#include <assert.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
#include <queue>
#include <stack>
using namespace std;
using ll = long long;

static const int INF = 1e11;

void solve() {
    int n; cin >> n;
    vector<int> as(n);
    for(int i = 0; i < n; ++i) { cin >> as[i]; }
    std::sort(as.begin(), as.end());
    ll sum = 0; for(int i = 0; i < n; ++i) { sum += as[i]; }
    // PROOF?
    ll left = sum % n;
    cout << left * (n - left) << "\n";

}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) { solve(); }
}



