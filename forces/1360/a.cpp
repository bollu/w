#include <iostream>
using namespace std;

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int a, b; cin >> a >> b;
        int sums = a + a;
        sums = min(sums, a + b);
        sums = min(sums, b + b);
        sums = max(sums, a);
        sums = max(sums, b);
        cout << sums * sums << "\n";
    }
    return 0;
}
