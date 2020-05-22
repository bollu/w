#include<iostream>
#include <iomanip>
using namespace std;
#define R return
using I=int;using F=double;
#define DO(i,n,x) for(I i =0;i<n;++i) {x;}
I main(){ std::ios_base::sync_with_stdio(false); cin.tie(NULL); 
I t; cin>>t;
F s = 0; for(int i = t; i >= 1; i--) { s+=1.0/i; } cout<< setprecision(12)<< s;
R 0;
}
