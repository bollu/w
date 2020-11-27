// TLE
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

const int N = 40;
const int M = N*N;
int n, m;
vector<int> es[N];
bool visited[N];
const int MOD = 1e9 + 7;
int tot;

int indent = 0;

int nvisited = 0;
void visit(int p, int v, int nvisited) {
    nvisited++;
    // cerr << std::string(indent++*3, ' ') << "|" << p << "->" << v << "\n";
    if (v == n && nvisited==n) { tot = (tot + 1) %MOD; }
    else {
        visited[v] = true;
        for(int w : es[v]) { 
            // cerr << std::string(indent*3, ' ') << "|" << v << "->" <<  w << "?\n";
            if (!visited[w]) { visit(v, w, nvisited); }
        }
        visited[v] = false;
    }
    indent--;
    nvisited--;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        es[a].push_back(b);

    }

    // for(int i = 1; i <= n; ++i) {
    //     cerr << i << ": [";
    //     for(int v : es[i]) { cerr << v << " "; }
    //     cerr << "]\n";
    // }
    visit(1, 1, 0);
    cout << tot << "\n";
    return 0;
}
