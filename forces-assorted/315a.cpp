#include <iostream>
#include <map>
using namespace std;

int main() {
    int n; cin>>n;
    int brands[200];
    int opens[200];
    for(int i = 0; i < n; ++i) { 
        cin >> brands[i] >> opens[i];
    }

    int unopenable = 0;

    // find bottles whose brand does not occur as any other bottles brand
    for(int i = 0; i < n; ++i){
        bool canopen = false;
        for (int j = 0; j < n; ++j) {
            // check OTHER brands
            if (i == j) continue;

            if (opens[j] == brands[i]) {
                canopen = true; break;
            }
        }

        unopenable += canopen ? 0 : 1;
    }

    cout << unopenable;

    return 0;
}

