#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n; std::cin >> n;
    vector<int> as(n);
    for(int i = 0; i < n; ++i) { cin >> as[i]; }
    int best = 1, len = 1;
    for(int i = 1; i < n; ++i) {
        if (as[i-1] < as[i]) {
            len++;
        } else {
            len = 1;
        }
        best = max<int>(best, len);
    }
    std::cout << best << "\n";
}
