#include <iomanip>
#include <iostream>
using namespace std;
int main() {
    int h, n;
    cin >> h >> n;

    for (int i = 0; i < n; ++i) {
        int t; cin >> t; h -= t;
    }
    if (h <= 0) { cout << "Yes"; } else { cout << "No"; }
    return 0;
}
