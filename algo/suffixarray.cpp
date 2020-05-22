// code form the stanford link that floats around:
// https://web.stanford.edu/class/cs97si/suffix-array.pdf also see:
// https://cs.stackexchange.com/questions/9447/algorithm-for-building-a-suffix-array-in-time-on-log2-n/9466
#include <cstring>
#include <algorithm>
#include <stdio.h>
#include<iostream>
using namespace std;
#define MAXN 65536
#define MAXLG 17

char A[MAXN];
struct entry {
    int nr[2], p;
} L[MAXN];

// position of Ai in the ordered array of A‘s character
int P[MAXLG][MAXN], N, i, stp, cnt;

int lex(struct entry a, struct entry b) {
    return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1] ? 1 : 0)
                              : (a.nr[0] < b.nr[0] ? 1 : 0);
}

int main(void) {
    cin >> A;
    for (N = strlen(A), i = 0; i < N; i++) P[0][i] = A[i] - 'a';
    // for (stp = 1, cnt = 1; cnt >> 1 < N; stp++, cnt <<= 1) {
    for (stp = 1, cnt = 1; cnt/2 < N; stp++, cnt*=2) {
        // loop over array, initialize L for this round.
        // L.p = index
        for (i = 0; i < N; i++) {
            L[i].nr[0] = P[stp - 1][i];
            L[i].nr[1] = i + cnt < N ? P[stp - 1][i + cnt] : -1;
            L[i].p = i;
        }
        // sort L by lex ordering: ascending?
        sort(L, L + N, lex);
        for (i = 0; i < N; i++)
            P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] &&
                                     L[i].nr[1] == L[i - 1].nr[1]
                                 ? P[stp][L[i - 1].p]
                                 : i;
    }

    printf("CORRECT:\n");
    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            if (P[stp-1][j] == i) {
                printf("%10s$", A + j);
                break;
            }
        }
    }
    return 0;
}

int lcp(int x, int y) {
    int k, ret = 0;
    if (x == y) return N - x;
    for (k = stp - 1; k >= 0 && x < N && y < N; k--)
        if (P[k][x] == P[k][y]) x += 1 << k, y += 1 << k, ret += 1 << k;
    return ret;
}
