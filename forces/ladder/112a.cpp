#include <iostream>
using namespace std;

int main() {
    string a, b;
    cin >> a >> b;

    bool lt = false, gt = false;
    for(int i = 0; i < a.size(); ++i) {
        char c = tolower(a[i]), d = tolower(b[i]);
        if (c == d) { 
            continue;
        }
        else if (c < d) { lt = true; break; }
        else { gt = true; break; }
    }

    cout << (lt ? -1 : gt ? 1 : 0);

    return 0;
}
