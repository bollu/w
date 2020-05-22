#include  <iostream>
#include  <stdlib.h>

using namespace std;
int main() {
    for(int i = 1; i <= 5; ++i) {
        for(int j = 1; j <= 5; ++j) {
            int x; cin >> x;
            if (x == 1) {
                cout << abs(i - 3) + abs(j - 3);
            }
        }
    }
    return 0;
}
