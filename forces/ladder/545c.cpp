#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

// max { it :  ix2count[it] < x }
template <typename K, typename V>
auto max_lt(std::map<K, V> &m, int ix) {
    // find it* = min { it : ix2count[it] >= x }
    // if it* is begin, then there is no element < x.
    auto it = m.lower_bound(ix);
    assert(it != m.begin());
    return std::prev(it);
}

// Q: In case the tree falls in right direction, then it may cover more than one
// tree? Why is it safe to greedily look
//   only at the previous tree?
// Key observation: felling to the right can't cover more than one tree.
// A: A tree falling to the right can't cover *any* tree; Consider what the
// condition says about tree `i` that falls to the right
//    wrt tree `i+1`. The tree `i` cannot cover `i+1` if `i+1` falls to left,
//    stays up, moves to right. The intersection of all 3 of these cases for the
//    `i+1` tree is that the location `x[i+1]` is occupied. So if we make the
//    tree `i` fall right, it cannot ever touch `x[i+1]`. So if we now consider
//    tree `i+2`, the tree `i` cannot interfere with tree `i+2`; (a) a tree `i`
//    that falls to the left clearly does not interfere with three `i+2` (b) A
//    tree `i` that falls to the right is "blocked" by tree `i+1`, and thus does
//    not interfere with tree `i+1`.
//

namespace greedy {

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<ll, ll>> ts(n);
    for (ll i = 0; i < n; ++i) {
        ll x, h;
        cin >> x;
        cin >> h;
        ts[i] = {x, h};
    }

    if (n == 0) {
        cout << 0;
        return 0;
    }
    if (n == 1) {
        cout << 1;
        return 0;
    }
    if (n == 2) {
        cout << 2;
        return 0;
    }

    sort(ts.begin(), ts.end());
    ll tot = 2;              // first tree leans left, last tree leans right.
    ll sweep = ts[0].first;  // rightmost occupied location so far.

    for (ll i = 1; i < n - 1; ++i) {
        ll x = ts[i].first;
        ll h = ts[i].second;
        ll xr = ts[i + 1].first;

        // Let O* be optimal solution.
        // 1. If x[i]+h[i] + h[i+1] < x[i+1], then we can make tree i lean
        // right, tree i+1 lean left for optimal solution.
        // 2. It is always optimal to make x[0] lean left
        // 2. It is always optimal to make x[-1] lean right
        if (sweep < x - h) {  // can lean left.
            tot++;            // always better to lean left.
            sweep = x;        // create range [x-h, x]. Rightmost = x.
        } else if (sweep < x && x + h < xr) {  // can lean right.
            // it's always optimal to lean right if possible.
            // In the worst case, we both the next tree from leaning left.
            tot++;
            sweep = x + h;  // create range [x, x+h]. Rightmost = x+h.
        } else {
            sweep = x;  // standing tree creates a point at [x].
        }
    }
    cout << tot;

    return 0;
}

}  // namespace greedy

namespace dp {

static const int N = 1e5 + 10;
int best[N][3];

struct p {
    int x; int h;
    bool operator < (const p&other) const {
        return this->x < other.x;
    }
};

void main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<p> ts(n);
    for (ll i = 0; i < n; ++i) {
        cin >> ts[i].x >> ts[i].h;
    }
    sort(ts.begin(), ts.end());

    static const int L = 0, U = 1, R = 2;
    best[0][L] = 1; best[0][U] = 0; best[0][R] = 0;
    for(int i = 1; i < n-1; ++i) {
        // == us: l ==
        best[i][L] = 0;
        // them: l|u
        if (ts[i-1].x + ts[i].h < ts[i].x) {  // L takes care of space when creating.
            best[i][L] = max(best[i][L], best[i-1][L]+1);
            best[i][L] = max(best[i][L], best[i-1][U]+1);
        }
        // them: r
        if (ts[i-1].x + ts[i-1].h  + ts[i].h < ts[i].x) { 
            best[i][L] = max(best[i][L], best[i-1][R] + 1);
        } 
        // == us: U ==
        best[i][U] = 0;
        // them: l | u | r
        if (ts[i-1].x < ts[i].x) { // always true?
            best[i][U] = max(best[i][U], best[i-1][L]);
            best[i][U] = max(best[i][U], best[i-1][U]);
            best[i][U] = max(best[i][U], best[i-1][R]);
        } 
        // us: R
        best[i][R] = 0;
        if (ts[i].x + ts[i].h < ts[i+1].x) { // R takes care of space when creating.
            // them: L|U
            best[i][R] = max(best[i][R], best[i-1][L]+1);
            best[i][R] = max(best[i][R], best[i-1][U]+1);
            best[i][R] = max(best[i][R], best[i-1][R]+1);
            // them: r
            // if (ts[i-1].x + ts[i-1].h < ts[i].x) {
            //     best[i][R] = max(best[i][R], best[i-1][R]+1);
            // }
        }
    }

    // cout << "arr ";
    // for(int i = 0; i < n; ++i) {
    //     cout << "([" << i << "] " << ts[i].x << " " << ts[i].h << ") ";
    // }
    // cout << "\n";
    // for(int i = 0; i < n-1; ++i) {
    //     cout << "best " << i << " | " << best[i][L] << " " << best[i][U] << " " << best[i][R] << "\n";
    // }

    int b = std::max(std::max(best[n-2][L], best[n-2][U]), best[n-2][R]) + 1;
    cout << b << "\n";
}
}  // namespace dp

int main() {
    dp::main();
    return 0;
}

