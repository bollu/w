#include <iostream>
using namespace std;

int main() {
    long y;
    cin >> y;
    y += 1;
    while(1) {
        int z = y;
        int p1 = (z % 10) ; z -= p1;
        int p2 = (z % 100) / 10; z -= p2;
        int p3 = (z % 1000) / 100; z -= p3;
        int p4 = (z % 10000) / 1000; z -= p4;
        // cout << p4 << p3 << p2 << p1 << "\n";
        
        if (p1 != p2 && p1 != p3 && p1 != p4 &&
            p2 != p3 && p2 != p4 &&
            p3 != p4) {
            cout << p4 << p3 << p2 << p1; break;
        }
        y += 1;
    }

    return 0;
}
