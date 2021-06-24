#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int n, m; cin >> n >> m;
    vector<int> as(n);
    for(int i = 0; i < n; ++i) { cin >> as[i]; }

    std::set<int> xs;
    vector<int> uniqs(n); 
    // li == uniqs[i] = distinct numbers in a[i], a[i+1]... a[n]. INCLUSIVE
    for(int i = n - 1; i >= 0; i--) {
        xs.insert(as[i]);
        uniqs[i] = xs.size();
    }

    for(int i = 0; i < m; ++i) {
        int l; cin >> l;
        cout << uniqs[l-1] << "\n";
    }

}
