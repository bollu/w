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


    int *rs[2];
    // 0, 1
    // move 0 <- 1; 1 <- NEW
    rs[0] = new int[N]; rs[1] = new int[N];
    for(int i = 0; i < N; ++i) { rs[1][i] = str[i] == '$' ? 0 : 1 + str[i] - 'a'; rs[0][i] = 0; }

    for(int pot = 1; pot <= N; pot++) {
        for(int i = 0; i < N; ++i) {
            rs[0][i] = rs[1][i];
            rs[1][i] = (i + (1 << pot)) < N ? rs[1][i + (1 << pot)] : (-1);
        }
        // rank rs
        int *out = new int[N]; 
        for(int i = 0; i < N; ++i) { 
            out[i] = 0;
            for(int j = 0; j < N; ++j) {
                out[i] += (rs[0][j] < rs[0][i]) || (rs[0][j] == rs[0][i] && rs[1][j] < rs[1][i]);
            }
        }
        for(int i = 0; i < N; i++) { rs[1][i] = out[i]; }
    }

    int *out = new int[N], *sorted = new int[N]; 
    for(int i = 0; i < N; ++i) { 
        out[i] = 0;
        for(int j = 0; j < N; ++j) {
            out[i] += (rs[0][j] < rs[0][i]) || (rs[0][j] == rs[0][i] && rs[1][j] < rs[1][i]);
        }
    }
    for(int i = 0; i < N; ++i) { sorted[out[i]] = i; }

    cout << "\nsorted (suffixarr):\n";
    for(int i = 0; i < N; ++i) { printf("%d | %s\n", i, str + sorted[i]); }
}
