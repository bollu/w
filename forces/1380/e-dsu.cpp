#include <iostream>
using namespace std;

#define ERR if(0) cerr

//in:
// 7 4
// 1 2 3 3 1 4 3
// 3 1
// 2 3
// 2 4
// out:
// 5
// 4
// 2
// 0


// in:
// 10 5
// 3 1 5 3 1 5 1 2 4 2
// 4 5
// 4 3
// 4 2
// 4 1
// out:
// 9
// 9
// 8
// 6
// 0


static const int MAXDISKS = 1000000;

int dsu_repr[10*MAXDISKS];
int dsu_sz[10*MAXDISKS];


int repr(int i) {
    int r = i;
    while(dsu_repr[r] != r) { r = dsu_repr[r]; }
    dsu_repr[i] = r;
    return r;
}

void merge(int i, int j) {
    int ri = repr(i);
    int rj = repr(j);

    //sz = size of subtree.
    if (dsu_sz[ri] > dsu_sz[rj]) {
        dsu_repr[rj] = ri; dsu_sz[ri] += dsu_sz[j]; // wrong?
        ERR <<"\t-" << "repr(" << j << ") := " << ri << "\n";
    } else {
        dsu_repr[ri] = rj; dsu_sz[rj] += dsu_sz[i];
        ERR <<"\t-" << "repr(" << i << ") := " << rj << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int n, m; cin >> n >> m;
    // each tower has an equivalence class
    for(int i = 1; i <= m; ++i) { dsu_repr[MAXDISKS+i] = MAXDISKS + i; dsu_sz[MAXDISKS+i] = 1; }
    for(int i = 1; i <= n; ++i) { dsu_repr[i] = i; dsu_sz[i] = 1; }

    for(int i = 1; i <= n; ++i) { 
        int i_disk_tower;
        cin >> i_disk_tower;
        // merge equivalence classes: towers are marked with MAXDISKS +i
        merge(i, MAXDISKS+i_disk_tower);
    }

    {
        int ndiff = 0;
        for(int ix = 1; ix <= n-1; ++ix) { ndiff +=  (repr(ix) != repr(ix+1)) ? 1 : 0; }
        cout << ndiff << "\n";
    }

    for(int i = 1; i <= m-1; ++i) {
        int a, b; cin >> a >> b;
        merge(MAXDISKS+a, MAXDISKS+b);
        int ndiff = 0;
        for(int ix = 1; ix <= n-1; ++ix) { 
            ERR << "- repr(" << ix << ") = " << repr(ix) << " | repr(" << ix + 1 << ") =  " << repr(ix+1) << "\n";
            ndiff += repr(ix) != repr(ix+1) ? 1 : 0;
        }
        cout << ndiff << "\n";
    }
    return 0;
}

