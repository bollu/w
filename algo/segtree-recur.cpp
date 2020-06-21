// segtree: https://codeforces.com/problemset/problem/1234/D
#include<iostream>
#include<utility>
#include<tuple>
#include<algorithm>
#include<assert.h>
#include<stdlib.h>
#include<sstream>
using namespace std;

struct segtree {
    int n;
    segtree(int n) : n(n) {}
    virtual void set(int ix, int val) = 0;
    // [l, r)
    virtual int rangeq(int l, int r) = 0;
};

struct segtree_dumb : public segtree {
    vector<int> as;
    segtree_dumb(int n) : segtree(n), as(n+1) { for(int &a: as) a = 0; }
    void set(int ix, int val) { assert(ix < as.size()); assert(ix >= 0); as[ix] = val; }
    int rangeq(int lix, int rix) { int s=0; for(int i=lix;i<=rix;++i) { s += as[i]; } return s; }
};

struct segtree_fancy : public segtree {
    vector<int> as;
    segtree_fancy(int n) : segtree(n), as(4*(n+1)) {
        for(int i = 0; i < 4*(n+1); ++i) as[i] = 0;
    }
    // closed intervals.
    void set_(int qix, int qval, int nl, int nix, int nr) {
        if (nl == nr) {
            if (qix == nl) { as[nix] = qval; }
        } else {
            int nmid = (nl + nr)/2;
            if (qix <= nmid) set_(qix, qval, nl, nix*2, nmid);
            else set_(qix, qval, nmid+1, nix*2+1, nr);
            as[nix] = as[nix*2] + as[nix*2+1];
        }
    }

    int rangeq_(int ql, int qr, int nl, int nix, int nr) {
        if (nl == nr) {
            if (ql <= nl && nr <= qr) { return as[nix]; } 
            return 0;
        } else {
            if (nr < ql || qr < nl) return 0;
            else if (ql <= nl && nr <= qr) { return as[nix]; }
            else {
                int nmid = (nl + nr)/2;
                return rangeq_(ql, qr, nl, nix*2, nmid) + rangeq_(ql, qr, nmid+1, nix*2+1, nr);
            }
        }
    }
    void set(int ix, int val) { set_(ix, val, 1, /*root=*/1, n); };
    int rangeq(int lix, int rix) { return rangeq_(lix, rix, 1, /*root=*/1, n); }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    srand(0);
    const int N = 100;
    const int TESTS = 1000;
    segtree_dumb dumb(N);
    segtree_fancy fancy(N);

    for(int i = 0; i < TESTS; ++i) {
        if (i % 2) {
            int ix = 1 + rand() % N;
            int val = (1+ rand() % 3) * (rand() % 2 ? 1 : -1);
            cout <<"as[" << ix << "] = " << val <<"\n";
            dumb.set(ix, val); fancy.set(ix, val);
        } else {
            int l = rand() % N; int r = min(l + rand() % N, N-1);
            cout << "as[[" << l << ", " << r <<"]]:\n";
            const int dumbrq = dumb.rangeq(l, r);
            const int fancyrq = fancy.rangeq(l, r); 
            cout << "\tdumb.rangeq = " << dumbrq << " | fancy.rangeq = " << fancyrq << "\n";
            cout.flush();
            assert(dumbrq == fancyrq);
        }
    }
}
