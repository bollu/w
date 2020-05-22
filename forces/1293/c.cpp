#include<iostream>
#include<assert.h>
#include<algorithm>
#define K 100001
using I=int; 
#define S set
bool on[3][K];
int nblocks=0;
int n,q;
using namespace std;
void pr() {
    for(int r=1;r<=2;++r) { for(int c=1;c<=n;++c) { cout<< on[r][c] <<" ";} cout<<"\n"; }
}
int main() {
    std::ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin>>n>>q; 
    for(int i = 0; i < q; ++i) {
        int r,c; cin>>r>>c;
        int s = r == 1?2:1;
         on[r][c]= !on[r][c];
        // block was toggled on
        if (on[r][c])  {
            if (c+1<=n&&on[s][c+1]) {nblocks++;}
            if (on[s][c]){nblocks++;}
            if (c-1>=0&&on[s][c-1]) {nblocks++;}
        }
        // block was toggled off
        else {
            if (c+1<=n&&on[s][c+1]) {nblocks--;}
            if (on[s][c]){nblocks--;}
            if (c-1>=0&&on[s][c-1]) {nblocks--;}
        }
        // printf("%5s | nblocks: %3d | %3d %3d:%4d\n", on[r][c]?"ON":"OFF", nblocks, r, c, nblocks);
        // pr();
        if (nblocks==0){cout<<"Yes\n";}else {cout<<"No\n";};
    };
    return 0;
}
