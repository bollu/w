#include <iostream>
using namespace std;

int main() {
    // floor(x/a) packs with discount
    // buys (x mod a) one by one
    // if (x mod a) > a/2 then buys (x/a) + 1  packs [with discount]
    //
    // find a such that for all x ∈ [l, r] customer has (x mod a) > a/2
    // a/2 <= l <= r < a
    // a = r+1
    // implicit assumption; a is integer
    int t;
    cin >> t;
    while (t--) {
        int l, r;
        cin >> l >> r;
        r++;
        if ((double)r / 2 <= l) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}
