#include<iostream>
#include<map>
#include<set>
using namespace std;
int main() { 
    int n; cin >> n;
    set<int> ns;
    int count = 0;
    for(int i = 0; i < n; ++i) {
        int x; cin >> x;
        if (ns.count(x)) continue;
        ns.insert(x);
        count++;
    }
    cout << count << "\n";
}
