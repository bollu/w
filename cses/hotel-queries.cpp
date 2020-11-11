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
int n, m;
static const int N = 2 * int(1e5) + 10;
int xs[N];
int tree[4*N];

void print() {
    int sz = 1, cursz = 0;
    cout << "\n[";
    for(int i = 1; i < 3*n; ++i) {
        cout << tree[i] << " ";
        cursz++;
        if (cursz == sz/2) { cout << ";"; }
        if (cursz == sz) { cout << "|"; cursz = 0; sz = sz* 2;}
    }
    cout << "]\n";
}
void build(int t, int tl, int tr) {
    if (tl == tr) { tree[t] = xs[tl]; return; }
    int tmid = (tl + tr)/2;
    build(t*2, tl, tmid); build(t*2+1, tmid+1, tr);
    tree[t] = max<int>(tree[t*2], tree[t*2+1]);
}

int query(int t, int tl, int tr, int minval) {
    // cout << "\t-query(" << t << ")\n";
    if (tl == tr) {
        // cout << "\t\t-tree[tl:" << tl << "] = " << tree[tl] << " >= " << minval << "\n";
        if (tree[t] >= minval) { 
            tree[t] -= minval;
            // cout << "\t\t-return: " << tl << "\n";
            return tl;
    }
        else { return 0; }
    }
    int tmid = (tl + tr)/2;
    int out = 0;
    
    if (tree[t*2] >= minval) { out = query(t*2, tl, tmid, minval); }
    else { out = query(t*2+1, tmid+1, tr, minval); }
    tree[t] = max<int>(tree[t*2], tree[t*2+1]);
    return out;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i <= n; ++i) { cin >> xs[i]; }
    build(1, 1, n);
    while(m--) {
        // print();
        int r; cin >> r;
        int ix = query(1, 1, n, r);
        cout << ix << " ";
    }
    cout << "\n";
    return 0;
}
