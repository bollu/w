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

const int N = int(1e3) + 5;
const int INFTY = 1e9 + 7;
int n, m;

int filled[N][N];
int mdist[N][N];
int pdist[N][N];
using coord = pair<int, int>;

bool mvisited[N][N];
bool pvisited[N][N];
queue<coord> mq;
queue<coord> pq;

coord start;
// E N W S
const coord dcoord[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };


coord pprev[N][N];

coord operator + (coord a, coord b) {
    return { a.first + b.first, a.second + b.second };
}
bool inbounds(coord a) {
    return a.first >= 1 && a.first <= n && a.second >= 1 && a.second <= m;
}

void check(int y, int x) {
    if (filled[y][x]) { return; }
    // TODO: > or >=?
    if (pdist[y][x] >= mdist[y][x] ) { return; }

    vector<char> moves;
    coord cur = {y, x};
    while(cur != start) {
        coord prev = pprev[cur.first][cur.second];
        if (prev.first + 1 == cur.first) {  moves.push_back('D'); }
        else if (prev.first - 1 == cur.first) { moves.push_back('U');  }
        else if (prev.second + 1 == cur.second) { moves.push_back('R'); }
        else if (prev.second - 1 == cur.second) { moves.push_back('L'); }
        cur = prev;
    }

    cout << "YES\n";
    cout << moves.size() << "\n";
    for(int i = moves.size() - 1; i >= 0; i--) {
        cout << moves[i]; 
    }
    cout << "\n";
    exit(0);

}
int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;

    for(int i = 0; i < N; ++i) {
        for(int j = 0; j < N; ++j) {
            mdist[i][j] = pdist[i][j] = INFTY;
        }
    }


    for(int y = 1; y <= n; ++y)  {
        for(int x = 1; x <= m; ++x) {
            char c;
            cin >> c;
            filled[y][x] = c == '#' ? 1 : 0;
            if (c == 'A') { start = {y, x}; pq.push({y, x}); pvisited[y][x] = true; pdist[y][x] = 0;} 
            if (c == 'M') { mq.push({y, x}); mvisited[y][x] = true; mdist[y][x] = 0; }
        }
    }

    while(!mq.empty()) {
        coord c = mq.front(); mq.pop();
        for(int i = 0; i < 4; ++i) {
            coord cnew = c + dcoord[i];
            if (filled[cnew.first][cnew.second]) { continue; }
            if (!inbounds(cnew) || mvisited[cnew.first][cnew.second]) { continue; }
            mdist[cnew.first][cnew.second] = mdist[c.first][c.second]+1;
            mvisited[cnew.first][cnew.second] = true;
            mq.push(cnew);
        }
    }

    while(!pq.empty()) {
        coord c = pq.front(); pq.pop();
        for(int i = 0; i < 4; ++i) {
            coord cnew = c + dcoord[i];
            if (filled[cnew.first][cnew.second]) { continue; }
            if (!inbounds(cnew) || pvisited[cnew.first][cnew.second]) { continue; }
            pdist[cnew.first][cnew.second] = pdist[c.first][c.second]+1;
            pprev[cnew.first][cnew.second] = c;
            pvisited[cnew.first][cnew.second] = true; 
            pq.push(cnew);
        }
    }

    // printf("pdist:\n");
    // for(int y = 1; y <= n; ++y) {
    //     for(int x = 1; x <= m; ++x) {
    //         printf("%5d ", pdist[y][x]);
    //     }
    //     printf("\n");
    // }

    // printf("mdist:\n");
    // for(int y = 1; y <= n; ++y) {
    //     for(int x = 1; x <= m; ++x) {
    //         printf("%5d ", mdist[y][x]);
    //     }
    //     printf("\n");
    // }

    for(int y = 1; y <= n; ++y) {
        check(y, 1);
        check(y, m);
    }

    for(int x = 1; x <= m; ++x) {
        check(1, x);
        check(n, x);
    }

    cout << "NO\n";
    return 0;
}
