#include <iostream>
using namespace std;
#define ll long long 

int main(int argc, char **argv) {
    ll t; cin >> t;

    while(t--) {
        ll a, b, c, d;
        cin >> a >> b >> c >> d;

        // a: total time needed to feel to sleep refreshed
        // b: time before first alarm goes off
        // c: time before every succeeding alarm goes off
        // d: time spend to fall asleep
        
        const ll t = a - b;
        if (t <= 0) {
            cout << b << "\n";
            continue;
        }

        const ll avail = c - d;
        if (avail <= 0) { 
            cout << -1 << "\n";  continue;
        }
        const ll ntimes = (t + (avail -1))/avail;
        cout << b + ntimes * c << "\n"; continue;

       // printf("%d %d %d %d", a, b, c, d);
    }
    return 0;
}
