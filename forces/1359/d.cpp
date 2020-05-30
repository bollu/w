#include <iostream>
using namespace std;

static const int INFTY = 1e4;

int a[100009];
int cum[100009];

int mt[3*100009];
int st[3*100009];
int n;


void build(int tl, int tr, int tix) {
    if (tl == tr) { mt[tix] = a[tl]; st[tix] = a[tl]; return;  }
    int tmid = (tl + tr)/2;
    build(tl, tmid, tix*2); build(tmid+1, tr, tix*2+1);
    mt[tix] = max(mt[tix*2], mt[tix*2+1]);
    st[tix] = st[tix*2] + st[tix*2+1];
}
void build() { build(1, n, 1); }

int maxval(int ql, int qr, int tl, int tr, int tix) {
    //[ql qr] [tl tr]   |  [tl tr] [ql qr]
    if (qr < tl  || tr < ql) { return -INFTY; }
    // [ql -- tl -- tr -- qr --]
    if (ql <= tl && tr <= qr) { return mt[tix]; }
    int tmid = (tl + tr)/2;
    return max<int>(maxval(ql, qr, tl, tmid, tix*2), maxval(ql, qr, tmid+1, tr, tix*2+1));
}

int maxval(int ql, int qr) { maxval(ql, qr, 1, n, 1); }
int sumval(int ql, int qr, int tl, int tr, int tix) {
    //[ql qr] [tl tr] [ql qr]
    if (qr < tl  || tr < ql) {
        // cout << "Q:[" << ql << ", " << qr << "]: T[" << tl << ", " << tr << "]  TIX" << tix << " | SUM SET TO " << 0 << "\n";
        return 0; 
    }
    // [ql -- tl -- tr -- qr]
    if (ql <= tl && tr <= qr) { 
        // cout << "Q:[" << ql << ", " << qr << "]: T[" << tl << ", " << tr << "]  TIX" << tix << " | RETSUM " << st[tix] << "\n";
        return st[tix];
    }
    int tmid = (tl + tr)/2;
    const int s = sumval(ql, qr, tl, tmid, tix*2) + sumval(ql, qr, tmid+1, tr, tix*2+1);
    // cout << "Q:[" << ql << ", " << qr << "]: T[" << tl << ", " << tr << "]  TIX" << tix << " | SUM: " << s << "\n";
    return s; 
}

int sumval(int ql, int qr) { sumval(ql, qr, 1, n, 1); }


int main() {
    cin >> n;
    bool haspos = false;
    for(int i = 1; i <= n; ++i) { 
        cin >> a[i];
        if (a[i] > 0) haspos = true;
    }

    cum[0] = a[0];
    for(int i = 1; i < n; ++i) { cum[i] += a[i]; }

    build();

    int maxout = 0;                   
    if (!haspos) {
        cout << 0 << "\n";
    } else {
        int l = 1; int r = 1;
        cout << "sum: " << sumval(1, 1) << "\n";
        while(l <= n && r <= n) {
            // catch up
            if (l < r) {
                maxout = max<int>(maxout, sumval(l, r) - maxval(l, r));
                l++;
                cout << "line:" << __LINE__ << " | l : " << l << " | r: " << r << "| sum: " << sumval(l, r) << " | max: " << maxval(l, r) << "\n";
            } else if (a[r] <= 0) {
                while(a[r] <= 0 && r < n) { r++; }
                l = r;
                cout << "line:" << __LINE__ << " | l : " << l << " | r: " << r << "| sum: " << sumval(l, r) << " | max: " << maxval(l, r) << "\n";
            } else {
                if (r == n+1) { break; }
                // l == r, a[r] > 0
                int sum = a[r];
                while(sum + a[r+1] >= 0 && r <= n) { sum += a[r+1]; r += 1; }
                maxout = max<int>(maxout, sumval(l, r) - maxval(l, r));
            }
        }
        cout << maxout << "\n";
    }
}
