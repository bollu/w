#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")

#include<bits/stdc++.h>
using namespace std;
#define lsb(x) (x & (-x))
const int maxix = 1<<20;
int a[5*maxix];
int cnt = 0;

const int INFTY = maxix+100;

void fnbump(int qix, int qval, int tguid, int tl, int tr) {
    // qix [l..r] ; [l..r] qix
    if (qix < tl || qix > tr) { return; }
    else {
        // printf("bump(%d, %d): [%d---%d---%d]\n", qix, qval, tl, tguid, tr);
        a[tguid] += qval;
        if (tl == tr) { return; }
        const int tmid = (tl + tr)/2;
        fnbump(qix, qval, tguid*2, tl, tmid);
        fnbump(qix, qval, tguid*2+1, tmid+1, tr);
    }
}

void fnbump(int qix, int qval) { return fnbump(qix, qval, 1, 1, maxix); }

int fnsum(int ql, int qr, int tguid, int tl, int tr) {
    // qr]...[tl; tr].. [ql
    if (qr < tl || tr < ql) { return 0; }

    // [ql..[tl---tr]....qr]
    if (ql <= tl && tr <= qr) { return a[tguid]; }

    const int tmid = (tl + tr)/2;
    return fnsum(ql, qr, tguid*2, tl, tmid) + fnsum(ql, qr, tguid*2+1, tmid+1, tr);
}

int fnsum(int r) { return fnsum(1, r, 1, 1, maxix); }



// returns non-zero number.
int nonzero(int tguid, int tl, int tr) {
    if (tl == tr) { return a[tguid] > 0 ? tl : -INFTY; }
    const int tmid = (tl+tr)/2;

    if (a[tguid*2] > 0) {
     return nonzero(tguid*2, tl, tmid);
    } else { return nonzero(tguid*2+1, tmid+1, tr); }
}

int nonzero() { return nonzero(1, 1, maxix); }

// decrement element with rank r
int find_ix_from_rank_segtree(int rnk, int tguid, int tl, int tr) {

    // invariant: summin <= rnk.
    const int tmid = (tl+tr)/2;

    // ----------------summine
    //                     |
    // 1.       rnk
    // 2.                      rnk
    if (tl == tr) { return a[tguid] > 0 ? tl : -INFTY; }

    if (rnk > a[tguid]) { return -INFTY; }
    if (rnk <= a[tguid*2]) {
        return find_ix_from_rank_segtree(rnk, tguid*2, tl, tmid);
    } else {
        return find_ix_from_rank_segtree(rnk - a[tguid*2], tguid*2+1, tmid+1, tr);
    }

}

int find_ix_from_rank_segtree(int rnk) {
    return find_ix_from_rank_segtree(rnk, 1, 1, maxix);
}


int fn_find_ix_from_rnk(int rnk) {
    int l = 0; int r = maxix;
    while (l < r) { 
        const int mid = (l + r) / 2; 
        // + 1: important!
        // why does this form of binary search work?
        // printf("%d-%d-%d: sum: %d\n", l, mid, r, fnsum(mid));
        if (rnk <= fnsum(mid))  { r = mid; } else { l = mid+1; }
    } 
    // assert(l == find_ix_from_rank_segtree(rnk));
    return l;  // return l: important!
} 


int main() {
    int n, q; scanf("%d %d", &n, &q);
    for(int i = 0; i < n; ++i) { int ix; scanf("%d", &ix); fnbump(ix, 1); cnt += 1;}
    for(int i = 0; i < q; ++i) { 
        int ix; scanf("%d", &ix); 
        if (ix > 0) { fnbump(ix, 1); cnt += 1;}
        else { fnbump(find_ix_from_rank_segtree(-ix), -1); cnt -=1;  };
    }
    if (!cnt) { printf("0\n"); }
    else { printf("%d\n", nonzero()); }
    return 0;
}
