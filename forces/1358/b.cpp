#include <string.h>
#include <iostream>
#include <utility>
#include <functional>
#include <algorithm>
#include <cmath>
#include<vector>
using namespace std;

const int N = 3 * (100000 + 1);
int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) { // t=1e4
        int n; cin >> n; // n = 1e5 _total_
        int count[N+5];
        memset(count, 0, sizeof(count));
        for(int i = 0; i < n; ++i) { 
            int val; cin >> val; 
            count[val]++;
        }
        count[0]++;

        int cumsum = 0;
        int call = 0;
        for(int i = 1; i <= n+1; ++i) {
            cumsum += count[i-1];
            call = cumsum >= i ? i : call;
        }
        cout << call << "\n";

        // ith granny attends if  at time of appearance, there will be a[i]
        // grannies there.
        //


    }
    return 0;
}

