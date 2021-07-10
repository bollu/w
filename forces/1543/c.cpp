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
using ld = long double;
static const ld prec = 1e-9;

// https://codeforces.com/contest/1543/submission/121580908
ld simBranchAccumProb(const ld c, const ld m, const ld p, const ld v, const ld branchp, const int n) {
    // c: cash slip
    // m: marker
    // p: pink slip

    // assert(c >= 0);
    // assert(m >= 0);
    // assert(p >= 0);
    // assert(fabs(c+m+p-1) <= 1e-2);
    // printf("%*s | %4.2f | %4.2f | %4.2f\n", 2*n, "", c, m, p);
    // cout << "(" << c+m+p << " | " << c << " " << m << " " << p << ")\n";
    if (c < 0 && m < 0) {
        return branchp * n;
    }
    else if (c < 0) {
        ld e = 0;
        // pick m
        {
            const ld mm = m > v ? m - v : -1;
            const ld pp = m > v ? p + v : p + m;
            e += simBranchAccumProb(-1, mm, pp, v, m * branchp, n+1);
        }
        // pick p
        e += branchp*p*n;
        return e;
    } else if (m < 0) {
        ld e = 0;
        // pick c
        {
            const ld cc = c > v ? c - v : -1;
            const ld pp = c > v ? p + v : p + c;
            e += simBranchAccumProb(cc, -1, pp, c, c*branchp, n+1);
        }
        // pick p
        e += branchp*p*n;
        return e;
    } else {
        ld e = 0;
        e += branchp*p*n;
        // pick c
        {
            const ld cc = c > v ? c - v : -1;
            const ld mm = c > v ? m + v/2 : m + c/2;
            const ld pp = c > v ? p + v/2 : p + c/2;
            e += simBranchAccumProb(cc, mm, pp, v, c * branchp, n+1);
        }
        // pick m
        {
            const ld mm = m > v ? m - v : -1;
            const ld cc = m > v ? c + v/2 : c + m/2;
            const ld pp = m > v ? p + v/2 : p + m/2;
            e += simBranchAccumProb(cc, mm, pp, v, m * branchp, n+1);
        }
        // pick p
        return e;
    }
}

const ld eps = 1e-9;
ld simAccumLength(const ld c, const ld m, const ld p, const ld v) {
    // c: cash slip
    // m: marker
    // p: pink slip
 
    // assert(c >= 0);
    // assert(m >= 0);
    // assert(p >= 0);
    // assert(fabs(c+m+p-1) <= 1e-2);
    // printf("%*s | %4.2f | %4.2f | %4.2f\n", 2*n, "", c, m, p);
    // cout << "(" << c+m+p << " | " << c << " " << m << " " << p << ")\n";
    if (c < eps && m < eps) {
        return 1;
    }
    else if (c < eps) {
        ld e = 0;
        // pick m
        {
            const ld mm = m > v ? m - v : -1;
            const ld pp = m > v ? p + v : p + m;
            e +=  m * (1 + simAccumLength(-1, mm, pp, v));
        }
        // pick p
        e += p;
        return e;
    } else if (m < eps) {
        ld e = 0;
        // pick c
        {
            const ld cc = c > v ? c - v : -1;
            const ld pp = c > v ? p + v : p + c;
            e += c * (1 + simAccumLength(cc, -1, pp, v));
        }
        // pick p
        e += p;
        return e;
    } else {
        ld e = 0;
        // pick c
        {
            const ld cc = c > v ? c - v : -1;
            const ld mm = c > v ? m + v/2 : m + c/2;
            const ld pp = c > v ? p + v/2 : p + c/2;
            e += c*(1 + simAccumLength(cc, mm, pp, v));
        }
        // pick m
        {
            const ld mm = m > v ? m - v : -1;
            const ld cc = m > v ? c + v/2 : c + m/2;
            const ld pp = m > v ? p + v/2 : p + m/2;
            e += m*(1 + simAccumLength(cc, mm, pp, v));
        }
        // pick p
        e += p;
        return e;
    }
}

void solve() {
    ld c, m, p, v;
    cin >> c >> m >> p >> v;
    // cout << std::setprecision(20) << sim2({c}, {m}, p, v, 1) << "\n";
    cout << fixed << std::setprecision(20) << simAccumLength(c, m, p, v) << "\n";
}
int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        solve();
    }
}




