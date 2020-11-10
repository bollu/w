#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

template <typename T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename K, typename V>
using ordered_map =
    __gnu_pbds::tree<K, V, less<K>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename T1, typename T2>
ostream &operator<<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}
static const int N = 1000 + 5;
int n, q;
int xs[N][N];
int tree[4*N][4*N];

void buildy_leaf(int *treey, int *xsy, int y, int yl, int yr) {
    if (yl == yr) { treey[y] = xsy[yl]; return; }
    int ymid = (yl + yr)/2;
    buildy_leaf(treey, xsy, y*2, yl, ymid);
    buildy_leaf(treey, xsy, y*2+1, ymid+1, yr);
    treey[y] = treey[y*2] + treey[y*2+1];
}

void buildx(int x, int xl, int xr) {
    if (xl == xr) {
        buildy_leaf(tree[x], xs[xl], 1, 1, n); return;
    } else {
        int xmid = (xl + xr)/2;
        buildx(x*2, xl, xmid);
        buildx(x*2+1, xmid+1, xr);
        // combine y nodes. Can make this faster by creating a custom version
        // of buildy_leaf that only visits the necessary indices?
        for(int i = 1; i < 4*N; ++i) { tree[x][i] = tree[x*2][i] + tree[x*2+1][i]; }
    }
}

int queryy(int *treey, int y, int yl, int yr, int qyl, int qyr) {
    // q t t q
    if(qyl <= yl && yr <= qyr) { return treey[y]; }
    // q q t t | t t q q 
    if (qyr < yl || yr < qyl) { return 0; }
    else {
        int ymid = (yl + yr)/2;
        return queryy(treey, y*2, yl, ymid, qyl, qyr) +
            queryy(treey, y*2+1, ymid+1, yr, qyl, qyr);
    }
}

int query(int x, int xl, int xr, int qxl, int qxr, int qyl, int qyr) {
    // cerr << "\tq(" << x << " " << y << " " << xl << " " << xr << " " << yl << " " << yr << " " << qxl << " "
    //      << qxr << " " << qyl << " " << qyr << ")\n";
    // q t t q
    if (qxl <= xl && xr <= qxr) {
        return queryy(tree[x], 1, 1, n, qyl, qyr);
    }
    // q q t t | t t q q
    else if (qxr < xl || xr < qxl) { return 0; }
    else {
        int xmid = (xl + xr)/2;
        return query(x*2, xl, xmid, qxl, qxr, qyl, qyr) +
               query(x*2+1, xmid+1, xr, qxl, qxr, qyl, qyr);
    }
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    cin >> n >> q;
    for(int y = 1; y <= n; ++y) {
        for(int x = 1; x <= n; ++x) {
            char c; cin >> c;
            xs[x][y] = c == '*';
        }
    }


    buildx(1, 1, n);
    /*
    cerr << "\n===\n";

    printf("%4d|", 0);
    for(int x = 1; x < 3*n; ++x) {
        printf("%4d", x);
    }
    printf("\n");

    for(int y = 1; y < 3*n; ++y) {
        printf("%4d|", y);
        for(int x = 1; x < 3*n; ++x) {
            printf("%4d", tree[x][y]);
        }
        printf("\n");
    }
    printf("\n===\n");
    
    for (int y = 1; y <= n; y++) {
        for(int x = 1; x <= n; x++) {
            cerr << xs[x][y] << ":" << query(1, 1, 1, n, 1, n, x, y, x, y) << " ";
        }
        cerr << "\n";
    }
    cerr << "==\n";
    */
    
    while(q--) {
        int x1, y1, x2, y2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << query(1, 1, n, x1, x2, y1, y2) << "\n";
    }

    return 0;
}
