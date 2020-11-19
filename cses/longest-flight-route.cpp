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

const int INFTY = 1e9;
const int N = 1e5 + 10;
int pathnext[N];
ll dist[N];
bool visited[N];

vector<int> es[N];
int n, m;

void visit(int s) {
    if (visited[s]) { return; }
    visited[s] = true;
    dist[s] = s == n ? 0 : -INFTY;
    pathnext[s] = s;
    for(int t : es[s]) {
        visit(t);
        if (dist[s] < 1 + dist[t]) {
            dist[s] =  1+dist[t];
            pathnext[s] = t;
        } 
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        es[a].push_back(b);
    }

    for(int i = 1; i <= n; ++i) {
        visit(i);
    }


    // cout << "\n[";
    // for(int i = 1; i <= n; ++i) {
    //     cout << dist[i] << " ]"[i==n];
    // }
    // cout << "\n";

    vector<int> vs;
    int cur = 1;

    while(1) {
        vs.push_back(cur);
        if (cur == pathnext[cur]) { break; };
        cur = pathnext[cur];
    }

    if (dist[cur] == -INFTY) {
        cout << "IMPOSSIBLE\n"; exit(0);
    }

    cout << vs.size() << "\n";
    for(int i = 0; i < vs.size(); i++) {
        cout << vs[i] << " \n"[i+1==vs.size()];
    }
    return 0;
}
