// https://codeforces.com/blog/entry/18051
#include <iostream>
#include <assert.h>
#define R return
#define A assert
#define D(x) cout<<__LINE__<<":"<<x<<"\n";
using I=int;using _=void; 
#define sc static const
using namespace std; sc I n=8;
I a[2*n];
I l(I i){R i<<1;} I r(I i){R i<<1|1;} I p(I i){R i>>1;} I sib(I i) { R i^i; }
I op(I a, I b){return a+b;} sc I e = 0;
// 1 2 3 [4 5 6 7] 8
// 2<- 4,5 | [0-2)
// 3<-6,7 | [2-4)
// 1<-2,3 | [0-4)
_ mk(){for(I i=n-1;i>=1;i--){a[i]=op(a[l(i)],a[r(i)]);}}
I rq_(I ql, I qr, I il, I ir, I i){
  A (ql <= qr); A (il <= ir);
  cout<<"rq_ q["<<ql<<" "<<qr<<"] i["<<i<<"] ["<<il<<" "<<ir<<"]"<<"\n";
  if (qr < il || ir < ql) R e;
  if (ql <= il && ir <= qr) {R a[i];}
  I im=(il+ir)/2; R op(rq_(ql, qr, il, im, l(i)), rq_(ql, qr, im+1, ir, r(i)));
}
I rq(I ql, I qr){ I v; cout<<"rq["<<ql<<" "<<qr<<"]="<<(v=rq_(ql, qr, 0, n-1, 1)) << "\n";
 R v;}
_ upd(I q, I v){ q+=n;  cout <<"upd q["<<q<<"] v["<<v<<"]\n";
 a[q]=op(a[q],v); q=p(q); while(q>=1) { a[q]=op(a[l(q)], a[r(q)]); q=p(q); }
}
_ pr(){for(I i=0;i<2*n;++i)cout<<a[i]<<" "; cout<<"\n";} 
I main(){for(I i=n;i<2*n;++i)a[i]=i-n; mk(); pr();
    rq(3, 4);
    rq(0, 1);
    pr(); upd(0, 1); pr();
    rq(0, 1);
    R 0;
}
