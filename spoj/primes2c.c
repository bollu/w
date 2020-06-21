#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define N (1000000000 + 1)
#define SQRTN (1000000000 + 1)

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
int nprimes;

int main() {
    primes[0] = 2; 
    primes[1] = 3;
    primes[2] = 5;
    primes[3] = 7;
    nprimes = 4;
    printf("2\n");

    for(int i = 9; i < N; i += 2) {
        int prime = 1;
        for(int j = 0; j < SQRTN; ++j) {
            const int p = primes[j];
            // j > sqrt(i)
            if (j*j > i) break;
            if (i % p == 0) { prime = 0; break; }
        }

        if (prime) {
            primes[nprimes] = i;
            // if (nprimes % 500 == 0) { printf("%d\n", i);  }
            // printf("%d\n", i); 
            nprimes++;

        }
    }
    return 0;
}
