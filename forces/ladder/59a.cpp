#include <iostream>
using namespace std;

int main() {
    string s; cin >> s;
    int nl = 0, nu = 0;
    for(int i = 0; i < s.size(); ++i) {
        if (s[i] >= 'a' && s[i] <= 'z') nl++; else nu++;
    }
    if (nu > nl) {
        for(int i = 0; i < s.size(); ++i) {
            cout << (char)(s[i] >= 'A' && s[i] <= 'Z' ? s[i] : s[i] - 'a' + 'A');
        }
    } else {
        for(int i = 0; i < s.size(); ++i) {
            cout << (char)(s[i]  >= 'a' && s[i] <= 'z' ? s[i] : s[i] - 'A' + 'a');
        }
    }
    return 0;
}
