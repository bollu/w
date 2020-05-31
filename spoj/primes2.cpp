#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
using ll = long long;
static const long long N = 1000000000 + 1;
static const long long SQRTN = 10000000 + 1;

// Input: n > 1, an odd integer to be tested for primality
// Output: “composite” if n is composite, “prime” otherwise
// 
// write n as 2r·d + 1 with d odd (by factoring out powers of 2 from n − 1)
// WitnessLoop: for all a in the range [2, min(n−2, ⌊2(ln n)2⌋)]:
//    x ← ad mod n
//    if x = 1 or x = n − 1 then
//       continue WitnessLoop
//    repeat r − 1 times:
//       x ← x2 mod n
//       if x = n − 1 then
//          continue WitnessLoop
//    return “composite”
// return “prime”
// static const int NP = 4;
// int primes[NP] = { 2, 3, 5, 7 };
// int primesq[NP] = { 4, 9, 25, 49 };

// compute a^pow (mod n)
/*
int powmod(int a, int pow, int n) {
    int ans = a;
    while (pow > 0) {
        if (pow % 2 == 0) {
            ans = (ans * ans) % n;
            pow /= 2;
        } else { 
            ans = (ans * a) % n;
        }
    }
    return (ans % n);
}
bool isprime(int n) {
    n -= 1;
    const int twopow = n & (-n);
    const int r = log2exact(twopow);
    const int d = n / twopow;
    for(int i = 0; i < NP; ++i) {
        const int p = primes[i];
        // int x = powmod(p, d, n);
        int x = 1;
        if (x == 1  || x == (n - 1)) { continue; }
        else {
            for(int i = 0; i < r - 1; ++i) {
            }
        }
    }
}
*/

int primes[SQRTN];
ll primesq[SQRTN];
int nprimes;
int nprimes_to_check;

int main() {
    primes[0] = 2; primesq[0] = 4;
    primes[1] = 3; primesq[1] = 9;
    primes[2] = 5; primesq[2] = 25;
    primes[3] = 7; primesq[3] = 49;
    nprimes = 4;
    nprimes_to_check = 2;
    printf("2\n");

    for(int i = 9; i < N; i += 2) {
        bool prime = true;
        if (i == primesq[nprimes_to_check]) { nprimes_to_check = min(nprimes_to_check+1, nprimes); }
        for(int j = 0; j < nprimes_to_check; ++j) {
            if (i % primes[j] == 0) { prime = false; break; }
        }

        if (prime) {
            primes[nprimes] = i;
            primesq[nprimes] = i * i;
            // if (nprimes % 500 == 0) { printf("%lld\n", i); }
            printf("%lld\n", i); 
            nprimes++;

        }
    }
    return 0;
}
