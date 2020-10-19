#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
static const int INFTY = 10000000;

int as[1000000];

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n, x; cin >> n >> x;
        for(int i = 0; i < n; ++i) cin >> as[i];
        std::sort(as, as+n, [](int i, int j){ return i > j; });

        // this leads to all sorts of annoying corner cases.
        if (x == 1) { 
            cout << n << "\n";
        } else {
            bool picking = true; int start = 0, len = 0, c = 0;
            for(int i = 0; i < n; ++i) {
                if(picking) {
                    len = 1; picking = false;
                } else { len++; }
                if (len * as[i] >= x) { 
                    c++;
                    picking = true;
                }
            }
            cout << c << "\n";
        }
    }
    return 0;
}
