// D using binary indexed tree. 
// Understand how the fuck this binary search works properly.
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include<bits/stdc++.h>
using namespace std;
#define lsb(x) (x & (-x))
const int maxix = 1<<20;
int a[maxix+5];
int cnt = 0;

// sum up values
int fnsum(int ix) {
    int tot = 0; while(ix > 0) { tot += a[ix]; ix -= lsb(ix); } return tot;
}

// bump up value
void fnbump(int ix, int val) {
    // printf("a[%d] += %d\n", ix, val);
    while (ix < maxix) { a[ix] += val; ix += lsb(ix); } 
}

int fn_find_ix_from_rnk(int rnk) {
    int l = 0; int r = maxix;
    while (l < r) { 
        const int mid = (l + r) / 2; 
        // + 1: important!
        // why does this form of binary search work?
        if (rnk <= fnsum(mid))  { r = mid; } else { l = mid+1; }
    } 
    return l;  // return l: important!
} 


int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 0; i < n; ++i) { int ix; scanf("%d", &ix); fnbump(ix, 1); cnt += 1;}
    for(int i = 0; i < q; ++i) { 
        int ix; scanf("%d", &ix); 
        if (ix > 0) { fnbump(ix, 1); cnt += 1;}
        else { fnbump(fn_find_ix_from_rnk(-ix), -1); cnt -=1;  };
    }
    if (!cnt) { printf("0\n"); }
    else { printf("%d\n", fn_find_ix_from_rnk(1)); }
    return 0;
}
