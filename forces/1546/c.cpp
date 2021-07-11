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

struct v {
    int ix = -42; int val = -42;
    v() : ix(-42), val(-42) {}
    v(int ix, int val) : ix(ix), val(val) {}
    bool operator < (const v &other) const {
        return this->val < other.val || (this->val == other.val && this->ix < other.ix);
    }
};

void solve() {
    int n; cin >> n;
    vector<v> as(n);
    for(int i = 0; i < n; ++i){ 
        as[i].ix = i;
        cin >> as[i].val;
    }

    map<int, int> nodd;
    std::sort(as.begin(), as.end());
    for(int i = 0; i < n; ++i) {
        if ((as[i].ix - i)%2 != 0) {
            nodd[as[i].val]++;
        }
    }
    bool success = true;
    for(auto it : nodd) {
        if (it.second % 2 != 0) {
            cout << "NO\n";
            success = false;
            break;
        }
    }

    if (success) {
        cout << "YES\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        solve();
    }
}




