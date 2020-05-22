// extended euclidian division
#include<iostream>
#include<utility>
#include<tuple>
#include<algorithm>
#include<assert.h>
#define A assert
#define I int
#define R return
#define II pair<I, I>
#define III tuple<I, I, I>
#define mt make_tuple
using namespace std;
// invariant: a>=b
// a = x b + r
// d = cb b + cr r
// d = cb b + cr (a - x b)
// d = (cb  - cr * x) b + cr a;
III euc(I a, I b);
III euc_(I a, I b){ A(a>=b); I x = a/b, r = a%b;  A(a == x * b + r);
  if (r==0) R mt(b,0,1);
  I d,cb,cr; tie(d,cb,cr)=euc_(b, r); A(d == cb * b + cr * r);
  R mt(d, cr, cb - cr * x); }
III euc(I a, I b) {
 if (a<b) { I d, ca, cb; tie(d,cb,ca)=euc_(b,a); R mt(d,ca,cb);} R euc_(a, b);}
void pr(I a, I b) { I d, ca, cb;tie(d, ca, cb)=euc(a,b);
  cout <<d<<"="<<ca<<" " <<a<<" + " << cb<<" "<<b<<"\n";
  A(d == ca * a + cb * b); A(a % d == 0); A(b % d == 0);
}
int main() { pr(10, 20); pr(15, 9); pr(9, 15); cout<<"\n";R 0; }
























