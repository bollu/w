// https://www.spoj.com/problems/BRCKTS/
#include<iostream>
#include<tuple>
#include<math.h>
using I=int;struct B { I l; I r; B() : l(0), r(0) {}; B(I l, I r) : l(l), r(r) {} }; const I N = 2*32768;
using namespace std;
B flip(B b) { return B {.l = b.r, .r  = b.l }; }
B join(B a, B b) {  I c = min(a.r, b.l); return B (a.l + b.l - c, a.r + b.r - c); } 
// keep pair of int: num unmatched )), num unmatched ((
B a[N];
B aseg[N];
int n;

void build(int nl, int nr, int segix) {
  if (nl == nr) { aseg[segix] = a[nl]; return;}
  int mid = (nl + nr) / 2;
  build(nl, mid, segix*2); build(mid+1, nr, segix*2+1);
  aseg[segix] = join(aseg[segix*2], aseg[segix*2+1]);
}

B query(int ql, int qr, int nl, int nr, int segix) {
  if (qr < nl || nr < ql) { return B(); }
  if (ql <= nl && nr <= qr) { return aseg[segix]; }
  int mid = (nl + nr) / 2;
  join(query(ql, qr, nl, mid, segix*2), query(ql, qr, mid+1, nr, segix*2+1));

}

void flipseg(int q, int nl, int nr, int segix) {
  if (q < nl || nr < q) { return; }
  if (nl == nr) { if (q == nl) { aseg[segix] = flip(aseg[segix]); } return; }
  int mid = (nl + nr) / 2;
  if (q <= mid) { flipseg(q, nl, mid, segix*2); }
  else { flipseg(q, mid+1, nr, segix*2+1); }
  aseg[segix] = join(aseg[segix*2], aseg[segix*2+1]);
}

void test() {
    cin >> n;
    for(int i = 1; i <= n; ++i) {
        char c; cin >> c; a[i] = B(int(c == ')'), int(c =='('));
    }
    build(1, n, 1);

    int m; cin>>m; // cout << "M: " << m << "\n";
    while(m--) {
        int k; cin >> k;
        if (k == 0) {
            if (aseg[1].l == 0 && aseg[1].r == 0) { cout << "YES\n"; } 
            else { cout << "NO\n"; }
        } else {
          flipseg(k, 1, n, 1);
        }
    }
}

int main() { 
    std::ios::sync_with_stdio(false); cin.tie(NULL);
    for(int i = 1; i <= 10; ++i) {
        cout << "Test " << i << ":\n";
        test();
    }
    return 0;
}
