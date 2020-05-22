#include <iostream>
// it's far easier to _check_ if the array is ascending
// than go through some torturous process of tracking
// invariants....
// https://codeforces.com/contest/451/submission/7221249
using namespace std;
int a[100000 + 3];
int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);
    int n; cin >> n;
    for(int i = 1; i <= n; ++i) cin >> a[i];

    bool found_decreasing = false; 
    int ix_decreasing_begin = -1;
    for(int i = 1; i < n; ++i) {
        if (a[i] > a[i+1]) {
            found_decreasing = true;
            ix_decreasing_begin = i;
            break;
        }
    }

    if (!found_decreasing) {
        cout << "yes\n1 1"; return 0;
    }

    // segment [ix_decreasing_begin...ix_decreasing_end]
    int ix_decreasing_end = ix_decreasing_begin;
    for(int i = ix_decreasing_begin; i < n; ++i) { 
        if (a[i] > a[i+1]) { ix_decreasing_end = i + 1; }
        else { break; }
    }

    bool can_be_ascending = true;
    if (ix_decreasing_begin > 1) {
        can_be_ascending = can_be_ascending && 
            (a[ix_decreasing_end] > a[ix_decreasing_begin-1]);
    }

    if (ix_decreasing_end < n) {
        can_be_ascending = can_be_ascending && 
            (a[ix_decreasing_begin] < a[ix_decreasing_end+1]);
    }

    // we have another segment...
    for(int i = ix_decreasing_end; i < n; ++i) {
        if (a[i] > a[i+1]) { cout << "no"; return 0; }
    }

    if (can_be_ascending) {
        cout <<"yes\n" << ix_decreasing_begin << " " << ix_decreasing_end;
    } else {
        cout <<"no";
    }


    return 0;
}
