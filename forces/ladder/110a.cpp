#include <iostream>
using namespace std;

int main() {
    cin.tie(NULL); ios::sync_with_stdio(false);
    string s; cin >> s;
    int n = 0;
    for(int i = 0; i < s.size(); ++i) { n += (s[i] == '4' || s[i] == '7'); }
    int m = 0;
    while(n != 0) {
        const int d = (n % 10);
        const bool lucky =  (d == 4 || d == 7);
        if (lucky) { m = 1; }
        else { m = 0; break; }
        n /= 10;
    }
    
    cout << (m > 0 ? "YES" : "NO"); 
}
