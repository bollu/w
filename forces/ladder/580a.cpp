#include<vector>
#include<iostream>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> as(n);
    for(int i = 0; i < n; ++i) {
        cin >> as[i];
    }
    int best = 1; int len = 1;
    for(int i = 1; i < n; ++i) {
        if (as[i] >= as[i-1]) { len++; } else { len = 1; }
        best = max(best, len);
    }
    cout << best << "\n";
}
