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

const int N = int(1e3) + 10;
int n;
int xs[N][N];
int tree[4*N][4*N];

void buildy(int *tarr, int *xsarr, int ty, int l, int r) {
    if (l == r) { tarr[ty] = xsarr[l]; return; }
    int mid = (l+r)/2;
    buildy(tarr, xsarr, ty*2, l, mid);
    buildy(tarr, xsarr, ty*2+1, mid+1, r);
    tarr[ty] = tarr[ty*2] + tarr[ty*2+1];
}

void buildx(int tx, int l, int r) {
    if (l == r) { buildy(tree[tx], xs[tx], 1, 1, n); }
    else { 
        int mid = (l+r)/2;
        buildx(tx*2, l, mid);
        buildx(tx*2+1, mid+1, r);
        for(int y = 1; y < 4*N; ++y) {
            tree[tx][y] = tree[tx*2][y] + tree[tx*2+1][y];
        }
    }
}

int queryy(int *tarr, int ty, int l, int r, int qyl, int qyr) {
    // q t t q
    if (qyl <= l && r <= qyr) { return tarr[ty]; }
    // t t q q | q q t t 
    if (r < qyl || qyr < l) { return 0; }
    int mid = (l + r)/2;
    return queryy(tarr, ty*2, l, mid, qyl, qyr) +
           queryy(tarr, ty*2+1, mid+1,r, qyl, qyr);
}

int queryx(int tx, int l, int r, int qxl, int qxr, int qyl, int qyr) {
    // q t t q
    if (qxl <= l && r <= qxr) {
        return queryy(tree[tx], 1, 1, n, qyl, qyr);
    }
    // t t q q | q q t t
    if (r < qxl || qxr < l) { return 0; }
    int mid = (l+r)/2;
    return queryx(tx*2, l, mid, qxl, qxr, qyl, qyr) +
           queryx(tx*2+1, mid+1, r, qxl, qxr, qyl, qyr);
}

void updatey(int *tarr, int ty, int l, int r, int qy, int delta) {
    tarr[ty] += delta;
    if (l == r) { return; }
    int mid = (l+r)/2;
    if (ty <= mid) { updatey(tarr, ty*2, l, mid, qy, delta); }
    else { updatey(tarr, ty*2+1, mid+1, r, qy, delta); }
    
}

void updatex(int tx, int l, int r, int qx, int qy, int delta) {
    // tarr[tx] += delta;
    if (l == r) { updatey(tree[tx], 1, 1, n, qy, delta); return; }
    int mid = (l+r)/2;
    if (qx <= mid) { updatex(tx*2, l, mid, qx, qy, delta); }
    else { updatex(tx*2+1, mid+1, r, qx, qy, delta); }
    // cannot spend O(n) updating, can I?
    // tree[tx][?] = tree[tx*2][?] + tree[tx*2+1][?]
    for(int y = 1; y < 4*N; ++y) { tree[tx][y] += tree[tx*2][y] + tree[tx*2+1][y]; }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> n >> q;
    for(int y = 1; y <= n; ++y){
        for(int x = 1; x <= n; ++x) {
            char c; cin >> c;
            xs[y][x] = c == '*' ? 1 : 0;
        }
    }
    while(q--) {
        int t; cin >> t;
        if (t == 1) {
            int y, x; cin >> y >> x;
            int delta = xs[y][x] == 1 ? -1 : 1;
            xs[y][x] = xs[y][x] ==  1  ? 0 : 1;
            updatex(1, 1, n, x, y, delta);
        } else {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << queryx(1, 1, n, x1, x2, y1, y2) << " ";
        }
    }
    cout << "\n";
    return 0;
}
