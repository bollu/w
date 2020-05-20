// 2. Improve suffixarr1 by getting rid of rs[2]. Keep only one array.
// 1. O(n^2) naive 
// https://www.cs.helsinki.fi/u/tpkarkka/teach/15-16/SPA/lecture10-2x4.pdf
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

int main(int argc, const char **argv) {
    const char *str = "banana$";
    const int N = strlen(str);
    char **suffixes = new char* [N];
    for(int i = 0; i < N; ++i) {
        suffixes[i] = new char[N+1];
        strcpy(suffixes[i], str + i);
    }

    for(int i = 0; i < N; ++i) { std::cout << i << ": " << suffixes[i] << "\n"; }
    std::sort(suffixes, suffixes+N, [N](const char *a, const char *b) {
            for(int i = 0; i < N; ++i) {
                if (a[i] == '$') return true; // a < b 
                if (b[i] == '$') return false; // a > b
                if (a[i] - 'a' < b[i] - 'a') return true;
                if (a[i] - 'a' > b[i] - 'a') return false;
            }
            assert(false && "unreachable");
    });
    cout << "sorted (naive):\n";
    for(int i = 0; i < N; ++i) { std::cout << i << ": " << suffixes[i] << "\n"; }


    int *rs;
    // 0, 1
    // move 0 <- 1; 1 <- NEW
    rs = new int[N];
    for(int i = 0; i < N; ++i) { rs[i] = str[i] == '$' ? 0 : 1 + str[i] - 'a'; }

    for(int pot = 1; pot <= N; pot++) {
        // rank rs
        int *out = new int[N]; 
        for(int i = 0; i < N; ++i) { 
            out[i] = 0;
            const int vi1 = rs[i];
            const int vi2 = (i + (1 << pot) < N) ? rs[i + (1<<pot)] : (-1);

            for(int j = 0; j < N; ++j) {
                const int vj1 = rs[j];
                const int vj2 = (j + (1 << pot) < N) ? rs[j + (1<<pot)] : (-1);
                out[i] += (vj1 < vi1) || (vj1 == vi1 && vj2 < vi2);
            }
        }
        for(int i = 0; i < N; i++) { rs[i] = out[i]; }
    }

    // int *out = new int[N], *sorted = new int[N]; 
    // for(int i = 0; i < N; ++i) { 
    //     out[i] = 0;
    //     for(int j = 0; j < N; ++j) {
    //         out[i] += (rs[j] < rs0][i]) || (rs[0][j] == rs[0][i] && rs[1][j] < rs[1][i]);
    //     }
    // }
    int *sorted = new int[N];
    for(int i = 0; i < N; ++i) { sorted[rs[i]] = i; }

    cout << "\nsorted (suffixarr):\n";
    for(int i = 0; i < N; ++i) { printf("%d | %s\n", i, str + sorted[i]); }
}
