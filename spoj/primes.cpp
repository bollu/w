#include <stdio.h>
#include <math.h>
#include <vector>
using namespace std;
#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
using ll = long long;


// 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59

// stage 1 primes
#define N1 10000001
#define N1SQRT sqrt(N1)

#define N2 1000000000
#define N2SQRT sqrt(N2)

int p1s[N2]; int np1s; int bcomp1[N2];
// int p2s[N2-N1+1];
int np2s;
int bcomp2[N2];

int find_smaller_multiple(int n, int i) {
    return ((n + i - 1)/ i) * i;
}

int count_primes(int n) {
    const int S = 10000;

    vector<int> primes(0, 1000000);
    int nsqrt = sqrt(n);
    vector<char> is_prime(nsqrt + 1, true);
    for (int i = 2; i <= nsqrt; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            for (int j = i * i; j <= nsqrt; j += i)
                is_prime[j] = false;
        }
    }

    int result = 0;
    vector<char> block(S);
    for (int k = 0; k * S <= n; k++) {
        fill(block.begin(), block.end(), true);
        int start = k * S;
        for (int p : primes) {
            int start_idx = (start + p - 1) / p;
            int j = max(start_idx, p) * p - start;
            for (; j < S; j += p)
                block[j] = false;
        }
        if (k == 0)
            block[0] = block[1] = false;
        for (int i = 0; i < S && start + i <= n; i++) {
            if (block[i])
                result++;
        }
    }
    return result;
}



int main() {
    // 2, 3, 5, 7
    np1s = 0;
    p1s[np1s++] = 2;
    printf("%d\n", 2);
    for(int i = 3; i < N1; i += 2) {
        if (!bcomp1[i]) { 
            if (i <= N2SQRT) { p1s[np1s++] = i; }
        }
        for(int j = (i <= N1SQRT ? i*i : N1); j < N1; j += i) { bcomp1[j] = true; }
        if (np1s % 500 == 1) { printf("%d\n", i); }
    }

    np2s = np1s;

    for(int i = 0; i < np1s; ++i) {
        int p = p1s[i];
        for(int j = max(N1, (p <= N2SQRT ? p*p : N2)); j < N2; j += p) { bcomp1[j] = true; }
    }

    for(int i = N1; i < N2; i += 2) {
        if (!bcomp1[i]) { 
            np1s++;
            if (np1s % 500 == 1) { printf("%d\n", i); }
        }
    }


    // for(int i = 0; i < np1s; ++i) {
    //     // cannot safely start from i^2, is no cuaranteed to have been cancelled,
    //     // I think.
    //     int p = p1s[i];
    //     for(int j = find_smaller_multiple(N1, p); j < N2; j += p) { bcomp2[j-N1] = false; }
    // }

    // for(int i = N1; i < N2; ++i) {
    //     if (!bcomp2[i-N1]) { np2s++; }
    //     if (np2s % 500 == 1) { printf("%d\n", i); }
    // }

    return 0;
}
