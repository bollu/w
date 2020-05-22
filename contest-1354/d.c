#include <stdio.h>

#define LSB(x) x&(-x)
#define MAXN 1000000

int a[MAXN+5];
int cnt[MAXN+5];
int cumsum(int i) {
 int s = 0;
 while (i > 0) { s += a[i]; i -= LSB(i); }
 return s;
}
int upd(int i, int v) {
    while (i < MAXN) { a[i] += v; i += LSB(i); }
}



int main() {
    int N, Q; scanf("%d %d", &N, &Q);
    for(int i = 0; i < N; ++i) {
        int val;
        scanf("%d", &val);
        upd(val, 1);
    }

    // printf("cumsum: "); for(int i = 0; i < N; ++i) { printf("%d, ", cumsum(i));} printf("\n");

    for(int i = 0; i < Q; ++i) {
        int query;
        scanf("%d", &query);
        if (query >= 1) {
            upd(query, 1);
        } else {
            query = -query;

            int l = 1;
            int r = MAXN;

            while(1) {
                const int m = (l + r)/2;
                if (cumsum(m) >= query && (m == 0 || cumsum(m-1) < query)) {
                    upd(m, -1);
                    break;
                } else if (cumsum(m) < query) { l = m; }
                else { r = m; }
            }
        }
    }


    int found = 0;
    int l = 1;
    int r = MAXN;

    if (cumsum(N) == 0) {
        printf("0\n");
    } else {
        while(1) {
            const int m = (l + r)/2;
            if (cumsum(m) >= 1 && (m == 0 || cumsum(m-1) < cumsum(m))) {
                // printf("delete query: rank(%d)  | deleting: %d\n", query, m);
                printf("%d\n", m);
                found = 1;
                break;
            }
            else if (cumsum(m) == cumsum(l)) { l = m; }
            else { r = m; }
        }
    }

    /*
    int found = 0;
    for(int i = 1; i < N; ++i) {
        const int v = cumsum(i) - cumsum(i-1);
        if (v > 0) {
            printf("%d\n", i);
            found = 1;
            break;
        }
    }
    if (!found) { printf("0\n"); }
    */
}

