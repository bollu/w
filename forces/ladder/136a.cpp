#include<iostream>
using namespace std;
int a[105];
int main() {
    std::ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    for(int i = 1; i <= n; ++i) { a[i] = i; }
    for(int i = 1; i <= n; ++i)  { int ix; cin >>  ix; a[ix] = i; }
    for(int i = 1; i <= n; ++i)  { cout << a[i] << " "; }

}
