#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <optional>
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

// naive implementation using strings. TLE
namespace f0 {

const int N = int(1e3) + 10;
optional<string> shortestPath;
using coord = pair<int, int>;
queue<pair<coord, string>> q;
coord s, t;
int filled[N][N];
int n, m;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == 'A') {
                s = {i, j};
            } else if (c == 'B') {
                t = {i, j};
            }
            filled[i][j] = c == '#' ? 1 : 0;
        }
    }

    q.push({s, ""});

    while (!q.empty()) {
        coord c;
        string path;
        tie(c, path) = q.front();
        q.pop();

        if (c.first < 0 || c.second < 0 || c.first >= n || c.second >= m) {
            continue;
        }
        if (filled[c.first][c.second]) {
            continue;
        }

        filled[c.first][c.second] = true;  // visited

        q.push({{c.first + 1, c.second}, path + "D"});
        q.push({{c.first - 1, c.second}, path + "U"});
        q.push({{c.first, c.second + 1}, path + "R"});
        q.push({{c.first, c.second - 1}, path + "L"});

        if (c == t) {
            if (!shortestPath) {
                shortestPath = path;
            } else if (path.size() < shortestPath->size()) {
                shortestPath = path;
            }
        }
    }

    if (!shortestPath) {
        cout << "NO\n";
    } else {
        cout << "YES\n"
             << shortestPath->size() << "\n"
             << *shortestPath << "\n";
    }
    return 0;
}

}  // namespace f0

// BFS with back pointers. BFS is guaranteed to give shortest path in unweighted
// graph. https://www.youtube.com/watch?v=Xp6MwU5fGT8&feature=emb_logo ^ use DR
// = {1, 0, -1, 0}; DC = { 0, 1, 0, -1}; if directions ordered clockwise, use
// (dirix+2)%4 to flip direction stack<pair<char, int>>;
namespace f1 {
using coord = std::pair<int, int>;
const int N = int(1e4) + 10;
int n, m;
coord prevcoord[N][N];
coord s, t;
int filled[N][N];
// ESWN [clockwise from east.
const coord dirs[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
const char *dirnames = "RULD";

char buf[N*N];
int main() {
    cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == 'A') s = {i, j};
            if (c == 'B') t = {i, j};
            filled[i][j] = c == '#' ? 1 : 0;
        }
    }

    queue<coord> q;
    q.push(s);

    while (!q.empty()) {
        coord c = q.front(); q.pop();
        if (c == t) {
            cout << "YES\n";
            int len = 0;
            while (c != s) {
                coord cprev = prevcoord[c.first][c.second];
                coord delta = { c.first - cprev.first, c.second - cprev.second};
                if (delta.first == -1) {
                    buf[len++] = 'U';
                } else if (delta.first == 1) {
                    buf[len++] = 'D';
                } else if (delta.second == -1) {
                    buf[len++] = 'L';
                } else {
                    buf[len++] = 'R';
                }
                c = cprev;
            }
            cout << len << "\n";
            for (int i = len - 1; i >= 0; i--) { cout << buf[i]; }
            cout << "\n";
            return 0;
        } else {
            for (int i = 0; i < 4; ++i) {
                // STYLISTIC CHOICE: repeat letter for new version.
                coord cnext = {c.first + dirs[i].first, c.second + dirs[i].second};
                if (cnext.first < 0 || cnext.first >= n || cnext.second < 0 || cnext.second >= m) {
                    continue;
                } if (filled[cnext.first][cnext.second]) { continue; }
                filled[cnext.first][cnext.second] = true;
                prevcoord[cnext.first][cnext.second] = c;
                q.push(cnext);
            }
        }
    }
    cout << "NO\n";
    return 0;
}
}  // namespace f1

// use DFS, reconstruct string when necessary.
// very likely that performance cost is the string ops.
namespace f2 {}

int main() { f1::main(); }
