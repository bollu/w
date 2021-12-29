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
int vals[N][N]; // vals[w][d]

int ws[4*N];
int ds[4*N];


void setd(int d, int v, int tl, int tr, int tix) {
    assert(tl <= tr);
    if (tl == tr) {
        ds[tix] = v;
        return;
    }
    int tm = (tl + tr)/2;
    if (d <= tm) {
        setd(d, v, tl, tm, tix*2);
    } else {
        setd(d, v, tm+1, tr, tix*2+1);
    }
    ds[tix] = ds[tix*2] + ds[tix*2+1];
}

void setwd(int w, int d, int v, int tl, int tr, int tix) {
    assert(tl <= tr);
    if (tl == tr) {
        setd(d, v, 1, n, 1);
        ws[tix] = 
        return;
    }

    int tm = (tl + tr)/2;
    if (w <= tm) {
        setwd(w, d, v, tl, tm, tix*2);
    } else {
        setwd(w, d, v, tm+1, tr, tix*2+1);
    }
    ws[tix] = ws[tix*2] + ws[tix*2+1];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q; cin >> n >> q;
    for(int d = 1; d <= n; ++d){
        for(int w = 1; w <= n; ++w) {
            char c; cin >> c;
            vals[w][d] = c == '*' ? 1 : 0;
        }
    }
    while(q--) {
        int t; cin >> t;
        if (t == 1) {
            int d, w; cin >> d >> w;
            int delta = vals[w][d] == 1 ? -1 : 1;
        } else {

        }
    }
    cout << "\n";
    return 0;
}
