#include <iostream>
#include <string>
using namespace std;

int main() {
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        string b; cin >> b;
        char buf[512];
        int i = 0, j = 0;
        buf[i++] = b[j++];
        for(; j < b.size(); j += 2) {
            buf[i++] = b[j];
        }
        buf[i++] = 0;
        cout << buf << "\n";

    }
    return 0;
}
