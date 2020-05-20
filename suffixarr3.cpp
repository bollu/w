// 3. remove O(n^2) rank computation to have it at O(n . log n . log n)
// 2. Improve suffixarr1 by getting rid of rs[2]. Keep only one array.
// 1. O(n^2) naive 
// https://www.cs.helsinki.fi/u/tpkarkka/teach/15-16/SPA/lecture10-2x4.pdf
#include <assert.h>
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;

struct S { int rs[2], ix; char dbg[512]; }; using R = int;
bool operator < (const S &s, const S&t) {
    return (s.rs[0] < t.rs[0]) || (s.rs[0] == t.rs[0] && s.rs[1] < t.rs[1]);
}
bool operator != (const S &s, const S&t) {
    return !((s.rs[0] == t.rs[0]) && (s.rs[1] == t.rs[1])); 
}

int main(int argc, const char **argv) {
    const char *str = "banana$";
    const char *strcirc = "banana$banana$";
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
    printf("sorted (naive):\n");
    for(int i = 0; i < N; ++i) { std::cout << i << ": " << suffixes[i] << "\n"; }

    // sort
    printf("suffixarr:\n");
    S ss[N], ts[N];
    R rs[N];

    // Step 1
    for(int i = 0; i < N; ++i) { ss[i].ix = i; ss[i].rs[0] = str[i]; ss[i].rs[1] = 0; sprintf(ss[i].dbg, "%c", str[i]); }
    sort(ss, ss+N);
    for(int i = 0, cnt=0; i < N; ++i) { cnt += i == 0 ? 0 : (ss[i] != ss[i-1] ); rs[ss[i].ix] = cnt; }
    printf("==\n");
    for(int i = 0; i < N; ++i) {
        printf("%d: (ix:%d, val:(%d, %d), dbg:%s)\n", rs[ss[i].ix], ss[i].ix, ss[i].rs[0], ss[i].rs[1], ss[i].dbg);
    }
    // Step 2
    for(int i = 0; i < N; ++i) {
        ts[i].ix = i;
        ts[i].rs[0] = rs[(i - 1 + N) % N];
        ts[i].rs[1] = rs[i] % N;

        for(int j = 0; j < 100; ++j) { ts[i].dbg[j] = 0; }
        for(int j = 0; j < 2; j++) { ts[i].dbg[j] = strcirc[j + N + i - 1 ]; }
    }
    sort(ts, ts+N);
    for(int i = 0, cnt=0; i < N; ++i) { cnt += i == 0 ? 0 : (ts[i] != ts[i-1] ); rs[ts[i].ix] = cnt; }
    printf("==\n");
    for(int i = 0; i < N; ++i) {
        printf("%d: (ix:%d, val:(%d, %d), dbg:%s)\n", rs[ts[i].ix], ts[i].ix, ts[i].rs[0], ts[i].rs[1], ts[i].dbg);
    }
    // Step 3
    for(int i = 0; i < N; ++i) {
        ss[i].ix = i;
        ss[i].rs[0] = rs[(i - 2 + N) % N];
        ss[i].rs[1] = rs[i] % N;

        for(int j = 0; j < 100; ++j) { ss[i].dbg[j] = 0; }
        for(int j = 0; j < 4; j++) { ss[i].dbg[j] = strcirc[j + N + i - 3 ]; }
    }
    sort(ss, ss+N);
    for(int i = 0, cnt=0; i < N; ++i) { cnt += i == 0 ? 0 : (ss[i] != ss[i-1] ); rs[ss[i].ix] = cnt; }
    printf("==\n");
    for(int i = 0; i < N; ++i) {
        printf("%d: (ix:%d, val:(%d, %d), dbg:%s)\n", rs[ss[i].ix], ss[i].ix, ss[i].rs[0], ss[i].rs[1], ss[i].dbg);
    }
    // Step 4
    for(int i = 0; i < N; ++i) {
        ts[i].ix = i;
        ts[i].rs[0] = rs[(i - 4 + N) % N];
        ts[i].rs[1] = rs[i] % N;

        for(int j = 0; j < 100; ++j) { ts[i].dbg[j] = 0; }
        for(int j = 0; j < min(N, 8); j++) { ts[i].dbg[j] = strcirc[j + N + i - 7 ]; }
    }
    sort(ts, ts+N);
    for(int i = 0, cnt=0; i < N; ++i) { cnt += i == 0 ? 0 : (ts[i] != ts[i-1] ); rs[ts[i].ix] = cnt; }
    printf("==\n");
    for(int i = 0; i < N; ++i) {
        printf("%d: (ix:%d, val:(%d, %d), dbg:%s)\n", i, ts[i].ix, ts[i].rs[0], ts[i].rs[1], ts[i].dbg);
    }

}
