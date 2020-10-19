#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n, m, k; cin >> n >> m >> k;
    vector<int> as(n);
    vector<int> bs(m);
    for(int i = 0; i < n; ++i) { cin >> as[i]; }
    for(int i = 0; i < m; ++i) { cin >> bs[i]; }
    std::sort(bs.begin(), bs.end());
    std::sort(as.begin(), as.end());

    int cnt = 0;
    int aix = 0, bix = 0;
    while(1) {
        if (aix >= n || bix >= m)  { break; }
        if (bs[bix] -  k <= as[aix] && as[aix] <= bs[bix] + k) {
            cnt++; aix++; bix++;
        } else if (bs[bix] - k < as[aix] ) {
            //house too small
            bix++;
        } else {
            // person wants something too small. [demand too small]
            aix++;
        }
    }
    cout << cnt << "\n";
}
