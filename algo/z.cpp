#include <iostream>
#include <string>
#include <assert.h>
#include <vector>
using namespace std;

// Z[i] = longest value such that such that s[0...Z[i]-1] = s[i..i+Z[i]-1]
// So Z[i] = length of substring: s[0, 0+l) = s[i, i+l)

vector<int> calcz(std::string s) {
    const int n = s.size();
    vector<int> z(n);
    z[0] = 0;
    for(int i = 1; i < s.size(); ++i) {
        z[i] = 0;
        while(i + z[i] < n && s[i+z[i]] == s[z[i]]) { z[i]++; }
    }

    return z;
}

vector<int> myz(std::string s) {
    const int n = s.size();
    vector<int> z(n);
    for(int i = 0; i < n; ++i) { z[i] = 0; }

    int l = 0;
    for(int i = 1; i < n; ++i) {
        // shade: (l + z[l]) - i
        // guess from start: z[i-l]
        z[i] = max(0, min(l + z[l] - i, z[i-l]));

        // compare with initial portion of string.
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) { z[i]++; }

        // we exceed the current shade. Begin ruling.
        if (i + z[i] >= l + z[l]) { l = i; }
    }

    return z;
}
// 0-1 prnciple for string algorithms?
int main() {
    static const int NBITS = 12;
    for(int i  = 0; i < 1 << NBITS; ++i) {
        std::string s(NBITS, '0');
        for(int j  = 0; j < NBITS; ++j) {
            s[j] = (i & (1 << j)) ? '1' : '0';
        }
        const int n = s.size();
        vector<int> z = calcz(s);
        vector<int> z2 = myz(s);
        std::cout << "\n" << s << "\n";
        std::cout << "\t";
        assert(z.size() ==n);
        assert(z2.size() ==n);
        for(int i = 0; i < n; ++i) {
            cout << "[" << i << "]" << z[i] << " ";
        }
        cout << "\n";
        std::cout << "\t";
        for(int i = 0; i < n; ++i) {
            cout << "[" << i << "]" << z2[i] << " ";
        }

        for(int i = 0; i < n; ++i) {
            if (z[i] != z2[i]) {
                cout << "\tmismatch at i[" << i << "] z[i][" << z[i] << "] z2[i][" << z2[i] << "]\n";
                return 1;
            }
        }
    };
    return 0;

}

