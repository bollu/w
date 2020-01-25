// https://www.spoj.com/problems/BRCKTS/
#include<iostream>
#include<tuple>
using I=int;struct B { I l; I r; B() : l(0), r(0) {}; B(I l, I r) : l(l), r(r) {} }; const I N = 2*32768;
using namespace std;
B flip(B b) { return B {.l = b.r, .r  = b.l }; }

B join(B a, B b) {  I c = min(a.r, b.l); return B (a.l + b.l - c, a.r + b.r - c); } 
// keep pair of int: num unmatched )), num unmatched ((
B a[N];
int n;

void test() {
    cin >> n;
    // 1 -> n | (i - 0 + n)
    for(int i = n; i < 2*n; ++i) { 
        char c; cin >> c; a[i] = B(int(c == ')'), int(c =='('));
    }


    // build
    for(int i = n-1; i >= 1; i--) {
        a[i] = join(a[i*2], a[i*2+1]);
    }

    // for(int i = n; i < 2*n; ++i) cout << (a[i].l == 1 ? ')' : '('); cout << "\n";

    int m; cin>>m; // cout << "M: " << m << "\n";
    while(m--) {
        int k; cin >> k;
        if (k == 0) {
            if (a[1].l == 0 && a[1].r == 0) { cout << "YES\n"; } 
            else { cout << "NO\n"; }
        } else {
            k -= 1; k += n; a[k] = flip(a[k]); 
            while(k >= 1) { k /= 2; a[k] = join(a[k*2], a[k*2+1]); }
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
