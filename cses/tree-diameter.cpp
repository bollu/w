#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <stdlib.h> // for exit()

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update

using ll = long long;
using namespace std;

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template<typename T>
using minqueue = priority_queue<T,vector<T>,greater<T>>;

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


// naive implementation
namespace f0 {
const int N = 2 * 1e5 + 10;
int d1[N];
int d2[N];
bool vis1[N], vis2[N];

vector<int> es[N];
int n;

void bfs(int v, int *ds, bool *vis) {
    queue<pair<int, int>> q;
    q.push({v, 0});
    while(!q.empty()) {
        int vcur, dcur; tie(vcur, dcur) = q.front(); q.pop();
        vis[vcur] = true;
        ds[vcur] = dcur;
        for(int w: es[vcur]) { 
            if (vis[w]) continue; 
            q.push({w, dcur+1});
         }
    }
}

int vmaxdist(const int *ds) {
    // cerr << "ds: [";
    // for(int i = 1; i <= n; ++i) {
    //     cerr << ds[i] << " ";
    // }
    // cerr << "]\n";

    int vmax = 0, dmax = -1;
    for(int v = 1; v <= n; ++v) {
        if (ds[v] >= dmax) { dmax = ds[v]; vmax = v; }
    }
    return vmax;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        es[a].push_back(b); es[b].push_back(a);
    }


    bfs(1, d1, vis1);
    int v = vmaxdist(d1);
    // cerr << "v:" << v << "\n";
    bfs(v, d2, vis2);
    int w = vmaxdist(d2);
    cout << d2[w] << "\n";
    return 0;
}

} 

// remove `visited` by keeping track of who parent is.
namespace f1 {
const int N = 2 * 1e5 + 10;
int d1[N];
int d2[N];
bool vis1[N], vis2[N];

vector<int> es[N];
int n;

void bfs(int v, int *ds) {
    queue<tuple<int, int, int>> q;
    q.push({v, v, 0});
    while(!q.empty()) {
        int vprev, vcur, dcur; tie(vprev, vcur, dcur) = q.front(); q.pop();
        ds[vcur] = dcur;
        for(int w: es[vcur]) { 
            if (w == vprev) continue; 
            q.push({vcur, w, dcur+1});
         }
    }
}

int vmaxdist(const int *ds) {
    int vmax = 0, dmax = -1;
    for(int v = 1; v <= n; ++v) {
        if (ds[v] >= dmax) { dmax = ds[v]; vmax = v; }
    }
    return vmax;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for(int i = 0; i < n - 1; i++) {
        int a, b; cin >> a >> b;
        es[a].push_back(b); es[b].push_back(a);
    }
    bfs(1, d1); int v = vmaxdist(d1);
    bfs(v, d2); int w = vmaxdist(d2);
    cout << d2[w] << "\n";
    return 0;
}
}

int main() { return f1::main(); }