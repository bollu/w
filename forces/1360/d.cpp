#include <string.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#define N 1000000007
#define SQRTN 100000
using namespace std;


int pow(int base, int exp) {
    if (exp == 0) { return 1; }
    if (exp == 1) { return base; }
    if (exp % 2 == 0) {
        const int half = pow(base, exp/2);
        return half * half;
    } else {
        const int half = pow(base, (exp-1)/2);
        return half * half * base;
    }
}

int main() {
    long long t; cin >> t;

    while(t--) {
        long long n, k; cin >> n >> k;
        // cout << "***n: " << n << " ***k: " << k << "\n";
        vector<long long> ps;
        map<long long, long long> pcount;
        long long x = n;
        for (long long i = 2; (long long)i * i <= n; i++) { 
            if (x == 1) { break; }
            while (x % i == 0) { 
                ps.push_back(i); 
                x /= i;
                // while (x % i == 0) { x /= i; pcount[i] += 1; }
            } 
        }

        if (x > 1) { ps.push_back(x); pcount[x] += 1; }

        long long ix = 0;
        // best candidate so far.
        long long maxd = 1;
        // brute over all subsets.
        for(long long mask = 0; mask < (1 << ps.size()); ++mask) {
            long long prod = 1;
            for(long long j = 0; j < ps.size(); ++j) {
                // if nth bit is set
                if (mask & (1 << j)) { prod *= ps[j]; }
            }
            if (prod <= k) { maxd = max<long long>(maxd, prod); }
        }
        cout << (n/maxd) << "\n";

        // while(maxd > k) {
        //     long long p = ps[ix];
        //     maxd /= p;
        //     mind *= p;
        //     pcount[p]--;
        //     if (pcount[p] == 0) { ix++; }
        // }
        // cout << mind << "\n";

    }
}

