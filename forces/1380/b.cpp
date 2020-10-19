// https://codeforces.com/contest/1380/problem/B
#include <iostream>
#include <vector>
using namespace std;

int t[1000000];

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        int rs = 0, ps = 0, ss = 0;
        for(int i = 0; i < s.size(); ++i) {
            if (s[i] == 'R') rs++;
            if (s[i] == 'P') ps++;
            if (s[i] == 'S') ss++;
        }

        char out = ' ';
        if (rs >= ps && rs >= ss) { out = 'P'; }
        else if (ps >= rs && ps >= ss) { out = 'S'; }
        else { out = 'R'; }

        for(int i = 0; i < s.size(); ++i) { cout << out; }
        cout << "\n";

    }
    return 0;
}
