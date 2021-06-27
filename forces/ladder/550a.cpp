#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
using namespace std;

static const int MAXN = 1e5+10;

// A B A B A

int main() {
    std::string s; cin >> s;
    {
        int abix = -1, baix = -1;

        for(int i = 1; i < s.size(); ++i){
            if (s[i-1] == 'A' && s[i] == 'B') {
                abix = i; break;
            }
        }

        for(int i = s.size()-1; i >= 1; i--){
            if (s[i-1] == 'B' && s[i] == 'A') {
                baix = i; break;
            }
        }
        if (abix + 1 < baix) { cout << "YES"; return 0; }
    }

    {
        int abix = -1, baix = -1;

        for(int i = 1; i < s.size(); ++i){
            if (s[i-1] == 'B' && s[i] == 'A') {
                baix = i; break;
            }
        }

        for(int i = s.size()-1; i >= 1; i--){
            if (s[i-1] == 'A' && s[i] == 'B') {
                abix = i; break;
            }
        }
        if (baix + 1 < abix) { cout << "YES"; return 0; }
    }

    cout << "NO"; return 0;
}

