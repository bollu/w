#include<iostream>
#include<map>
using namespace std;

using ll = long long;
int main() {
    ios_base::sync_with_stdio(false);
    int t; cin >> t; // t <= 1e4
    while(t--) {
        int n; cin >> n; // 2 <= n <= 1e5
        // count |{ (i, j) : i < j /\ a[i] a[j] = i + j }|
        map<int, int> i2a, a2i;
        for(int i = 1; i <= n; ++i) {
            int a; cin >> a;
            i2a[i] = a;
            a2i[a] = i;
        }

        int pairs = 0;
        for(auto it : a2i) {
            int a = it.first; int i = it.second;
            for(int b = 1; a * b <= 2 * n; b++) {
                if (b == a) { continue; }
                auto it2 = a2i.find(b);
                if (it2 == a2i.end()) { continue; }
                int j = it2->second;
                if (a * b == i + j) { pairs++; }
            }
        }
        cout << pairs/2 << "\n";
    }
    return 0;
}


