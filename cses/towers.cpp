#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <assert.h>


using ll = long long;
using namespace std;
int main() { 
    int n; cin >> n;

    multiset<int> ks;
    for(int i = 0; i < n; ++i) {
        int k;
        cin >> k; 
        auto it = ks.upper_bound(k);
        if (it != ks.end()) { ks.erase(it); }
        ks.insert(k);
    }

    cout << ks.size() << "\n";
    return 0; 
}
