#include <iostream>
#include <string>

using namespace std;
int main() {
    string s; cin >> s;
    char out[200]; int outlen = 0;

    for(int i = 0; i < s.size();) {
        if (s[i] == '.') {
            out[outlen++] = '0'; i += 1;
        } else if (s[i] == '-' && s[i+1] == '.') {
            out[outlen++] = '1'; i += 2;
        } else {
            out[outlen++] = '2'; i += 2;
        }
    }

    out[outlen] = '\0';
    cout << out;
    return 0;
}
