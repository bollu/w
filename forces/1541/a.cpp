#include<iostream>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t; // t <= 100
    while(t--) {
        int n; cin >> n;
        if (n%2 == 0) {
            for(int i = 1; i <= n; i += 2) {
                cout << i + 1 << " " << i << " ";
            }
        } else {
            for(int i = 1; i <= n - 3; i += 2) {
                cout << i + 1 << " " << i << " ";
            }
            cout << n << " " << n - 2 << " " << n - 1;

        }
        cout << "\n";
    }
    return 0;
}

