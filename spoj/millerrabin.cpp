#include <stdio.h>
#define N 10000000
using ss = int;
using ll = long long;

//Input #1: n > 3, an odd integer to be tested for primality
//Input #2: k, the number of rounds of testing to perform
//Output: “composite” if n is found to be composite, “probably prime” otherwise
//
//write n as 2^r·d + 1 with d odd (by factoring out powers of 2 from n − 1)
//WitnessLoop: repeat k times:
//   pick a random integer a in the range [2, n − 2]
//   x ← ad mod n
//   if x = 1 or x = n − 1 then
//      continue WitnessLoop
//   repeat r − 1 times:
//      x ← x2 mod n
//      if x = n − 1 then
//         continue WitnessLoop
//   return “composite”
//return “probably prime”


// return log2 if it is known that x is a power of 2
ss log2pot(ss x) {
    switch(x) {
        case 1<<0: return 0;
        case 1<<1: return 1;
        case 1<<2: return 2;
        case 1<<3: return 3;
        case 1<<4: return 4;
        case 1<<5: return 5;
        case 1<<6: return 6;
        case 1<<7: return 7;
        case 1<<8: return 8;
        case 1<<9: return 9;
        case 1<<10: return 10;
        case 1<<11: return 11;
        case 1<<12: return 12;
        case 1<<13: return 13;
        case 1<<14: return 14;
        case 1<<15: return 15;
        case 1<<16: return 16;
        case 1<<17: return 17;
        case 1<<18: return 18;
        case 1<<19: return 19;
        case 1<<20: return 20;
        case 1<<21: return 21;
        case 1<<22: return 22;
        case 1<<23: return 23;
        case 1<<24: return 24;
        case 1<<25: return 25;
        case 1<<26: return 26;
        case 1<<27: return 27;
        case 1<<28: return 28;
        case 1<<29: return 29;
        case 1<<30: return 30;
        case 1<<31: return 31;
    };
}
static const int NPS = 4;
int ps[NPS] = {2, 3, 5, 7};

int powmod(int base, int pow, int n) {
    // printf("powmod(%d, %d, %d)\n", base, pow, n);
    if (pow == 0) { return 1; }
    else if (pow == 1) { return base; }
    else if (pow % 2 == 0) {
        int k = powmod(base, pow/2, n);
        return (k * k) % n;
    } else {
        int k = powmod(base, pow/2, n);
        return (k * k * base) % n;
    }
}

// return true if n is prime
int millerabin(const int n) {
    int two_pow_r = n & (-n);
    int r = log2pot(two_pow_r);
    int d = n / two_pow_r;
    fprintf(stderr, "millerrabin(%d)\n", n);
    // fprintf(stderr, "\t%d=(%d=2^%d) * %d\n", n, two_pow_r,  r, d); getchar();

    int i = -1;
    witness_loop:
    i += 1;
    if (i == NPS) { return true; }

    int a = ps[i];
    int x = powmod(a, d, n);
    fprintf(stderr, "\t%d^%d (mod %d) = %d\n", a, d, n, x); getchar();
    if (x == 1 || x == n - 1) { goto witness_loop; }

    for(int j = 0; j < r-1; ++j) {
        fprintf(stderr, "\tx = x(%d) * x(%d) = %d\n", x, x, (x*x)%n);
        x = (x * x) % n;
        if (x == n - 1) { goto witness_loop; }
    }
    return false; 
}

int main() {
    int nprimes = 0;
    int printcount = 0;
    for(int i = 11; i < N; i+= 2) {
        if (millerabin(i)) { printf("%d\n", i); }
        getchar();

    }
    return 0;
}
