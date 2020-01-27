#include <assert.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define K 100001
using namespace std;
using I = long long int;
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    I h; cin >> h;
    I attack = 0; I n = 1;
    while (h >=1) {
        h = h/2; attack += n; n *= 2;
    }
    cout << attack;
}
