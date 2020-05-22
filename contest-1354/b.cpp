#include <iostream>

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        char t[200000 + 10];
        int tixl[ 200000 + 10];
        int tixr[ 200000 + 10];

        const int INFTY = 300000 + 10;

        int tlen = 1; t[0] = s[0]; tixl[0] = 0; tixr[0] = 0;
        for(int i = 1; i < s.size(); ++i) {
            if (t[tlen-1] == s[i]) { 
                tixr[tlen-1] = i;
                continue;
            }
            else { 
                t[tlen] = s[i];
                tixl[tlen] = i;
                tixr[tlen] = i;
                tlen++;
            }
        }

        // for(int i = 0 ; i < tlen; ++i) { cout << t[i] << " [" << tixl[i] << ", " << tixr[i] << "]\n"; }


        int minv = INFTY;
        for(int i = 0; i + 2 < tlen; ++i) {
            bool vals[3] = {false, false, false};
            vals[t[i] - '1'] = true;
            vals[t[i+1] - '1'] = true;
            vals[t[i+2] - '1'] = true;
            if (vals[0] && vals[1] && vals[2]) {
                minv = min(minv, tixl[i+2] - tixr[i] + 1); // +1?
            }
        }

        if (minv == INFTY) { cout <<0<< "\n"; }
        else { cout << minv << "\n"; }

    }
}
