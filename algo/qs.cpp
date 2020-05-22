#include<iostream>
#define I int
#define V void
#define R return
#define DO(i,n,x){for(I i=0;i<n;++i){x;}}
using namespace std;
I A[]={3,2,1,4,5},n=5;
V s(I i,I j){I t=A[i];A[i]=A[j];A[j]=t;}
I part(I lo, I hi){
  I p=A[hi],i=lo;
  for(I j=lo;j<hi;++j){if(A[j]<p)s(i++, j);} s(i,hi);
  R i;
}
V qs(I lo, I hi){ if(hi-lo<=1)R; I p=part(lo,hi); qs(lo, p-1);qs(p+1,hi); }
I main(){qs(0,n-1);DO(i,n,cout<<A[i]<<" ");cout<<"\n";R 0;}
