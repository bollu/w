typedef char C;typedef long long I;
typedef struct a{I t,r,d[3],*p;}*A;
#define P printf
#define R return
#define V1(f) A f(w)A w;
#define V2(f) A f(a,w)A a,w;
#define DO(n,x) {I i=0,_n=(n);for(;i<_n;++i){x;}}
/*
conventions: 
 - r: rank (number of dimensions)
 - d: dimension (number of elements in each dimension)
 - p: pointer | t : type(?) / transpose(?)
 - a: 1st array param | w: 2nd array param | z: return array param
ma: malloc n ints and return ptr;
mv: move n bytes from int *s to int* d
*/
I *ma(n){R(I*)malloc(n*8);}mv(d,s,n)I *d,*s;{DO(n,d[i]=s[i]);}
/*tr: return product of first r elements of d. Why is this called tr?*/
tr(r,d)I *d;{I z=1;DO(r,z=z*d[i]);R z;}
/* ga: allocate an array of type t, rank r, dimensions d*/
A ga(t,r,d)I *d;{A z=(A)ma(sizeof(struct a));
  z->p=ma(tr(r,d));z->t=t,z->r=r,mv(z->d,d,r); R z;}
/*~:iota: allocate an array of rank 1, size n, with data [0..n-1] n = w->p[0] */
V1(iota){I n=*w->p;A z=ga(0,1,&n);DO(n,z->p[i]=i);R z;}
/*+:plus: add up input arrays. assume input arrays have same rank, dim */
V2(plus){I r=w->r,*d=w->d,n=tr(r,d);A z=ga(0,r,d);
 DO(n,z->p[i]=a->p[i]+w->p[i]);R z;}
/*{:from: create a new array of shape being the shape of the
  2nd array, stripped of outermost dimension.
  fill the array with data from second array.
  skip (n*a->p[0]) elements from w during
  filling of output array */
V2(from){I r=w->r-1,*d=w->d+1,n=tr(r,d);
 A z=ga(w->t,r,d);mv(z->p,w->p+(n**a->p),n);R z;}
/*<:box: create an array of (w->t=1)
  whose pointer wraps the input array */
V1(box){A z=ga(1,0,0);*z->p=(I)w;R z;}
/*,:cat: concatenate two arrays.  */
V2(cat){I an=tr(a->r,a->d),wn=tr(w->r,w->d),n=an+wn;
 A z=ga(w->t,1,&n);mv(z->p,a->p,an);mv(z->p+an,w->p,wn);R z;}
/*~:find:unimplemnted. As a challenge?  */
V2(find){}
/*#:rsh: ???*/
V2(rsh){I r=a->r?*a->d:1,n=tr(r,a->p),wn=tr(w->r,w->d);
 A z=ga(w->t,r,a->p);mv(z->p,w->p,wn=n>wn?wn:n);
 if(n-=wn)mv(z->p+wn,z->p,n);R z;}
/*#:shape:a 1D array whose values are the dimensions of w */
V1(sha){A z=ga(0,1,&w->r);mv(z->p,w->d,w->r);R z;}
/*+:id:identity function*/
/*{:size:number of elements in outermost dimension */
V1(id){R w;}V1(size){A z=ga(0,0,0);*z->p=w->r?*w->d:1;R z;}
/* pi: print an integer | nl: print a newline */
pi(i){P("%d ",i);}nl(){P("\n");}
/* pr: print an array */
pr(w)A w;{I r=w->r,*d=w->d,n=tr(r,d);DO(r,pi(d[i]));nl();
 if(w->t)DO(n,P("< ");pr(w->p[i]))else DO(n,pi(w->p[i]));nl();}
C vt[]="+{~<#,";
A(*vd[])()={0,plus,from,find,0,rsh,cat},
 (*vm[])()={0,id,size,iota,box,sha,0};
struct a *st[26]; qp(a){R  a>='a'&&a<='z';}qv(a){R a<'a';}
A ex(e)I *e;{I a=*e;
 if(qp(a)){if(e[1]=='=')R st[a-'a']=ex(e+2);a= st[ a-'a'];}
 R qv(a)?(*vm[a])(ex(e+1)):e[1]?(*vd[e[1]])(a,ex(e+2)):(A)a;}
/*noun: return 0 if not a number.
  If a number, create array containing number */
I noun(c){A z;if(c<'0'||c>'9')R 0;z=ga(0,0,0);*z->p=c-'0';R z;}
/*verb: return i such that vt[i] = c */
I verb(c){I i=0;for(;vt[i];)if(vt[i++]==c)R i;R 0;}
/*wd: parse input and return array of noun()/verb()/char */
I *wd(s)C *s;{I a,n=strlen(s),*e=ma(n+1);C c;
 DO(n,e[i]=(a=noun(c=s[i]))?a:(a=verb(c))?a:c);e[n]=0;R e;}
/*main: parse, execute, print*/
main(){C s[99];while(gets(s))pr(ex(wd(s)));}

