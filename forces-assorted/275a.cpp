#include <iostream>
using namespace std;

// 0-initialized
int toggles[5][5];
int main() {
    for(int y = 1; y <= 3; ++y) {
        for(int x = 1; x <= 3; ++x) {
            cin >> toggles[x][y];
        }
    }

    for(int y = 1; y <= 3; ++y) {
        for(int x = 1; x <= 3; ++x) {
            bool light = 1;
            for(int stx = -1; stx <= 1; ++stx) {
                for(int sty = -1; sty <= 1; ++sty) {
                    if (stx != 0 && sty != 0) continue;
                    light = light ^ (toggles[x+stx][y+sty] % 2);
                }
            }

            cout << light;
        }
        cout << "\n";
    }


    return 0;
}
