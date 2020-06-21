#include <iostream>
#include <vector>
using namespace std;

void solve() {
    int n; cin >> n;
    vector<int> as(n); 

    int badiodd = 0, badieven = 0;
    for(int i = 0; i < n; ++i) {
        cin >> as[i];
        if (i % 2 == 0 && as[i] % 2 == 1) badiodd += 1;
        if (i % 2 == 1 && as[i] % 2 == 0) badieven += 1;
    }

    if (badiodd == badieven) { cout << badiodd << "\n"; } else { cout << "-1\n"; }
}

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        solve();
    }
    return 0;
}
