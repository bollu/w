#include<iostream>
#include<algorithm>
#include<assert.h>
#include<algorithm>
using I = long long int;
using namespace std;
int H[300001]; 
int main() {
    std::ios_base::sync_with_stdio(false); cin.tie(NULL);
    I n, k; cin >> n >> k;
    for(int i = 0; i < n; ++ i) cin >> H[i];
    sort(H, H+n);
    // for(int i = 0; i < n; ++ i) cout << H[i] << " ";

    I tot = 0;
    const int start = n-(k+1); // cout << "start: " << start << "\n";
    for(int i = start; i >= 0; i--) { tot += H[i]; }
    cout << tot;
    return 0;
}
