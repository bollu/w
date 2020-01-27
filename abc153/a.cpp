#include<iostream>
#include<algorithm>
#define K 1001
using namespace std;
int main() {
std::ios_base::sync_with_stdio(false); cin.tie(NULL);
int h, a; cin >> h >> a; cout << (h+a-1)/a;
return 0;
}
