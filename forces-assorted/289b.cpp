#include <iostream>
#include <assert.h>
using namespace std;
using ll = long long;
int as[10000 + 5];
int asd[10000 + 5];
int n;
ll x, y; 
int d; 


int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    cin >> x >> y; n = x * y;
    cin >> d;
    for(int i = 0; i < n; ++i) {
        cin >> as[i];
    }

    const int res = as[0] % d;
    // a[i] + alpha d = a[k] = beta d.
    // a[i] = a[k] (mod d)
    for(int i = 1; i < n-1; ++i) { 
        if (as[i] % d != res) { cout << -1; return 0; }
    }

    for(int i = 0; i < n; ++i) {
        asd[i] = (as[i] - res) / d;
    }

    // OK, residues are all equal.
    // it will be monotonic, so we can "ternary search"? use two samples,
    // and then move to the smallest segment.
    int l, r; l = r = asd[0];
    for(int i = 1; i < n; ++i) {
        l = min(l, asd[i]); r = max(r, asd[i]);
    }

    int mid = (l + r) / 2;

    // we want l^ m_ r^
    while(l != r) {
        int m1 = (l + mid) / 2; int m2 = (mid + r) / 2;
        int errm1 = 0; int errm2 = 0;
        for(int i = 0; i < n; ++i) {
            errm1 += abs(asd[i] - m1);
            errm2  += abs(asd[i] - m2);
        }

        if (errm1 < errm2
    }
    return 0;
}

