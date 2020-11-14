#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <queue>

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

// search
namespace f0 {

const int N = int(1e3) + 10;
bool filled[N][N];
int n, m;


// consider this. If we do not choose to walk left,
// we will miss the '.' in the cranny at index '2'.
// #######
// ###.###
// ##..###
// ###.###
// 012
      

void flood_fill(int x0, int y0) {
    queue<pair<int, int>> q;
    q.push({x0, y0});

    while(!q.empty()) {
        int x, y; 
        tie(x, y) = q.front(); q.pop();
        if (x >= n || y >= m || x < 0 || y < 0) { continue; }
        if (filled[x][y]) { continue; }
        filled[x][y] = 1;
        q.push({x, y+1});
        q.push({x, y-1});
        q.push({x+1, y});
        q.push({x-1, y});
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            char c; cin >> c;
            filled[i][j] = c == '#' ? 1 : 0;
        }
    }

    int tot = 0;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            if (filled[i][j]) { continue; }
            tot++;
            flood_fill(i, j);

        }
    }
    cout << tot << "\n";
    return 0;
}

}

// dsu
namespace f1 {
    const int N = int(1e3) + 5;
    int parents[N*N];
    int filled[N][N];
    int n, m;

    // ESWN
    int di[4] = {1, 0, -1, 0};
    int dj[4] = {0, -1, 0, 1};

    int root(int i) { if (i == -1) { return -1; } if (i == parents[i]) { return i; } return root(parents[i]); }

    void unite(int i, int j) {
        int ri = root(i), rj = root(j);
        if (ri == -1 || rj == -1) { return; }
        // expected log height?
        if (rand() % 2) { parents[rj] = ri; }
        else { parents[ri] = rj; }
    }

    int main() {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cin >> n >> m;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                char c; cin >> c;
                filled[i][j] = c == '#' ? 1 : 0;
            }
        }



        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                // create DSU nodes.
                if (filled[i][j]) { parents[i*N+j] = -1;  continue; }
                else  { parents[i*N+j] = i*N+j; }
            }
        }

        // for(int i = 0; i < n; ++i) {
        //     for(int j = 0; j < m; ++j) {
        //         fprintf(stderr, "%5d", root(i*N+j));
        //     }
        //     fprintf(stderr, "\n");
        // }
        // fprintf(stderr, "\n===\n");

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                for(int d = 0; d < 4; ++d) {
                    int ii = i + di[d], jj = j + dj[d];
                    if (ii < 0 || ii >= n || jj < 0 || jj >= m) { continue; }
                    unite(i*N+j, ii*N+jj);
                }
            }
        }

        // for(int i = 0; i < n; ++i) {
        //     for(int j = 0; j < m; ++j) {
        //         fprintf(stderr, "%5d", root(i*N+j));
        //     }
        //     fprintf(stderr, "\n");
        // }

        set<int> rs;
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                int r = root(i*N+j);
                if (r == -1) { continue; }
                rs.insert(r);
            }
        }
        cout << rs.size() << "\n";
        return 0; 
    }
}

int main() { 
    f1::main();
}
