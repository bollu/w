#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

using namespace std;
int main() {
    int n, x;
    cin >> n >> x;
    
    map<int, int> v2i;
    bool done = false;
    for (int i = 1; i <= n; ++i) {
        int cur;
        cin >> cur;
        if (v2i.count(x - cur)) {
            cout << i << " " << v2i[x - cur] << "\n";
            done = true;
        }
        v2i[cur] = i;
        if (done) break;
    }
    if (!done) {
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}
