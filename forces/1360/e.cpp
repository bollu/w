#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <functional>
using namespace std;

// 00101001
// 00111101
// 00101001
// 00101001

int main() {
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        bool a[n][n];
        bool b[n][n];

        for(int i = 0; i < n; ++i) { for(int j = 0; j < n; ++j) { b[i][j] = 0; } }

        for(int i = 0; i < n; ++i) {
            string s; cin >> s;
            for(int j = 0; j < n; ++j) {
                a[i][j] = s[j] == '1';
            }
        }

        queue<pair<int, int>> frontier;
        for(int i = 0; i < n; ++i) {
            if(a[0][i]) { frontier.push(make_pair(0, i)); }
            if(a[i][0]) { frontier.push(make_pair(i, 0)); }
        }

        while(frontier.size()) {
            int i, j; tie(i, j) = frontier.front();
            frontier.pop();
            b[i][j] = true;

            //  *-----*---------*
            // /     /         /|
            // *<----*<-------*.|
            // ^     |        |.|
            // |     |        |.|
            // |     |        |.|
            // <-----*        |.|
            // |      \       | *
            // |       \      v/|
            // |        *---->*.|
            // |        |     ^.|
            // |        |     |.*
            // v        |     |/
            // *<-------*-----*
            if (i < n-1 && a[i+1][j]) { frontier.push(make_pair(i+1, j)); }
            if (j < n-1 && a[i][j+1]) { frontier.push(make_pair(i, j+1)); }
        }

        bool success = true;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if (a[i][j] && !b[i][j]) { success = false; break; }
            }

            if (success) { break; }
        }
        
        cout << (success ? "YES" : "NO") << "\n";

    }
}
