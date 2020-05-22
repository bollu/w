#include<iostream>
#include<algorithm>
#define K 1001
using namespace std;
vector<int> as; 
int main() {
std::ios_base::sync_with_stdio(false); cin.tie(NULL);
int t; cin>>t;
while(t--){
    int n,s,k; cin>>n>>s>>k;
    as.clear(); as.resize(k);
    for (auto &z: as) cin >> z;

    int ix=0;
    while(1) {
        if(s-ix>=1 && find(as.begin(),as.end(),s-ix) == as.end()) {
            cout<<ix<<"\n";
            break;
        }

        if(s+ix<=n&&find(as.begin(),as.end(),s+ix) == as.end()) {
            cout<<ix<<"\n";
            break;
        }
        ix++;
    }
}
return 0;
}
