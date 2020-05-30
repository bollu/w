#include <iostream>
using namespace std;

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n, m; cin >> n >> m;
        int total = 0;
        if (n % 2 == 1) {
            cout << (m+1)/2 + (n/2)*m << "\n";
        } else {
            cout << (n/2)*m << "\n";
        }
    }
    return 0;
}
