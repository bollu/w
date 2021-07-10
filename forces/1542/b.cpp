#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;

static const int N = 1000;


bool f(ll n, ll a, ll b) {
    if (a == 1) {
        return (n - 1) % b == 0;
    }
    // 1 ∈ S
    // x ∈ S => ax ∈ S
    // x ∈ S =>  x + b ∈ S
    //
    // 
    // 1. x := x + b
    // 2. x := x * a
    // will generate a(x + b) = ax + ab
    //
    // But this is equvalent to
    //
    // x := x * a
    // x := x + b
    // x := x + b
    // x := x + b
    //  ... (a times )...
    //
    // will generate x = ax + ab.
    // So there's really no point to adding first then multiplying.
    //
    //
    // --dubious stuff 1 ----
    // We can think of this in terms of horner's method. We have a polynomial of the form
    // p ∈ S
    // given some a^n, we can always get a^n + kb [by adding as]
    //
    // ---dubious stuff 2---
    // S = 1 + xS + b + S
    // S = (1 + b) + S + xS
    ll apow = 1;
    while (apow <= n) {
        if (apow % b == n % b) {
            // why? 
            return true;
        }
        apow *= a;

    }
    return false;
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n, a, b; cin >> n >> a >> b;
        bool out = f(n, a, b);
        if (out) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}


