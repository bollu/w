#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main() {
    int fx = 0, fy = 0, fz = 0, n;
    cin >> n;
    while(n--) {
        int curfx, curfy, curfz;
        cin >> curfx >> curfy >> curfz;
        fx += curfx; fy += curfy; fz += curfz;
    }
    if (fx == 0 && fy == 0 && fz == 0) {
        cout << "YES";
    } else { cout << "NO"; } 

    return 0;
}
