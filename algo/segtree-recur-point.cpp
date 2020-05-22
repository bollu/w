#include<iostream>
#include<tuple>
#include<algorithm>
using I=int;struct B { I l; I r; }; const I N = 30000 + 100;
using namespace std;
B join(B a, B b) {
    int c = min(a.r, b.l); return B { a.l + b.l - c, a.r + b.r - c };
} 
// https://www.spoj.com/problems/BRCKTS/
// keep pair of int: num unmatched )), num unmatched ((
B a[N];
int main() { return 0; }

