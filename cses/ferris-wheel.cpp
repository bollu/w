#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, x; cin >> n >> x;
    vector<int> ps(n);
    for(int i = 0; i < n; ++i) { cin >> ps[i]; }
    std::sort(ps.begin(), ps.end());

    int out = 0;
    int l = 0, r = n-1;
    while(l <= r) {
        if (l < r && ps[l] + ps[r] <= x) { 
            out += 1; l++; r--;
        } else {
            out += 1; r--; 
        }
    }
    cout << out << "\n";
}
