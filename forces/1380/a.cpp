#include <iostream>
#include <string>
using namespace std;

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t; 
    while(t--) {
        int n; cin >> n;
        int ps[2000];
        for(int i = 0; i < n; ++i) cin >> ps[i];

        bool success = false;
        for(int c = 0; c < n; ++c) {
            bool left = false;
            int leftix = -1;
            for(int i = 0; i < c; ++i) {
                if (ps[i] < ps[c]) { left = true; leftix = i; break; }
            }
            bool right = false; int rightix = -1;
            for(int i = c+1; i < n; ++i) {
                if (ps[i] < ps[c]) { right = true; rightix = i; break; }
            }
            if(left && right) { 
                success = true;
                cout << "YES\n" << leftix +1<< " " << c+1 << " " << rightix+1 << "\n";
                break;
            }
        }

        if (!success) { cout << "NO\n"; }

    }
    return 0;
}
