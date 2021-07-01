#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;

void printmat(const ll m[4][4]) {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
}

static const ll MOD = 1e9 + 7;
ll add(ll a, ll b) {
    return (a + b) % MOD;
}

ll mul(ll a, ll b) {
    return (a * b) % MOD;
}

void eye(ll out[4][4]) {
    for(ll i = 0; i < 4; ++i) {
        for(ll j = 0; j < 4; ++j) {
            out[i][j] = i == j ? 1 : 0;
        }
    }
}

void copy(const ll m[4][4], ll out[4][4]) {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            out[i][j] = m[i][j];
        }
    }
}

void matmul(const ll a[4][4], const ll b[4][4], ll out[4][4]) {
    for(ll i = 0; i < 4; ++i) {
        for(ll j = 0; j < 4; ++j) {
            out[i][j] = 0;
            for(ll k = 0; k < 4; ++k) {
                out[i][j] = add(out[i][j], mul(a[i][k], b[k][j]));
            }
        }
    }
}


void pow(const ll m[4][4], int n, ll out[4][4]) {
    if (n == 0) {
        eye(out);
        return;
    }
    else if (n == 1) {
        copy(m, out);
        return; 
    } 
    else if (n % 2 == 0) {
        ll half[4][4];
        pow(m, n/2, half);
        matmul(half, half, out);
        return;
    } else {
        ll half[4][4];
        pow(m, n/2, half);
        ll full[4][4];
        matmul(half, half, full);
        matmul(full, m, out);
    }
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int n; cin >> n;
    ll adj[4][4];
    ll out[4][4];
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < 4; ++j) {
            adj[i][j] = i == j ? 0 : 1;
        }
    }

    pow(adj, n, out);
    // printmat(out);
    cout << out[3][3] << "\n";
    return 0;
}

