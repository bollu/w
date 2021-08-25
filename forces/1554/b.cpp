#include <assert.h>
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>


// slow:
// 2^N.2^N 
// for(int mask = 0;mask < (1<<N); ++mask){
// 	for(int i = 0;i < (1<<N); ++i){
// 		if((mask&i) == i){
// 			F[mask] += A[i];
// 		}
// 	}
// }

// fast:
// `msk & msk = msk`
// for(int msk = 0; msk<(1<<N); ++msk) {
// 	F[msk] = A[msk]; // (i is always a submask of i)
// }
//
// build up `(mask & bit)` in `bit` th iteration
// N (2^N)
// for(int bit = 0; bit < N; ++bit) {
//     for(int msk = 0; msk < (1<<N); ++msk){
//      	if(mask & (1<<bit)) {
// 	        	F[msk] += F[msk^(1<<bit)];
//              }
//     }
// }


// mark-whole-buffer
using namespace std;
using ll = long long;

const ll INFTY = 1e5;
int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;

    while (t--) {
      int n, k; cin >> n >> k;
      vector<int> as(n);
      for(int i = 0; i < n; ++i) {
	cin >> as[i];
      }
      
    }
}

