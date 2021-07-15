#include <assert.h>
#include "math.h"
#include<iostream>
#include<iomanip>
#include<vector>
#include<map>
#include<optional>
#include<set>
#include<utility>
#include<numeric> // for LCM
#include<algorithm>
#include <queue>
#include <stack>
using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<int> as(n);
    // invariant: after sorting, number of values in odd and even locations must be the same,
    // since upon travelling, odd ixed values go to odd ixed values (R -> L -> R ⇒ ±2 index) and
    // similarly for even.
    map<int, int> nOdd;
    map<int, int> nEven;
    for(int i = 0; i < n; ++i){ 
        as[i] = i;
        cin >> as[i];
        if (i % 2 == 1) {
            nOdd[as[i]]++;
        } else {
            nEven[as[i]]++;
        }
    }

    std::sort(as.begin(), as.end());
    for(int i = 0; i < n; ++i) {
        if (i % 2 == 1) {
            nOdd[as[i]]--;
        } else {
            nEven[as[i]]--;
        }
    }
    bool success = true;
    for(auto it : nOdd) {
        if (it.second != 0) { success = false; break; }
    }
    for(auto it : nEven) {
        if (it.second != 0) { success = false; break; }
    }
    if (success) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        solve();
    }
}




