#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
// using ll = long long;

int counts[25*60];
int main() {
    cin.tie(NULL); ios::sync_with_stdio(false);
    int n; cin >> n;

    int v = 0;
    for(int i = 0; i < n; ++i) {
        int h, m; cin >> h >> m;
        counts[h*60+m]++;
        v = counts[h*60+m] > v ? counts[h*60+m]  : v;
    }
    cout << v;
    return 0;
}

