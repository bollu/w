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

// naive: correct but TLE
namespace f0 {

enum Choice { L, R };

int best_us_turn_enemy(int l, int r, const vector<int> &xs);
int best_us_turn_us(int l, int r, const vector<int> &xs);

int best_us_turn_enemy(int l, int r, const vector<int> &xs) {
    assert(l <= r);
    if (l == r) {
        return 0;
    }

    return std::min<int>(best_us_turn_us(l + 1, r, xs),
                         best_us_turn_us(l, r - 1, xs));
}

int best_us_turn_us(int l, int r, const vector<int> &xs) {
    assert(l <= r);
    if (l == r) {
        return xs[l];
    }
    return std::max<int>(xs[l] + best_us_turn_enemy(l + 1, r, xs),
                         xs[r] + best_us_turn_enemy(l, r - 1, xs));
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> xs(n);
    for (int i = 0; i < n; ++i) {
        cin >> xs[i];
    }
    cout << best_us_turn_us(0, n - 1, xs) << "\n";
    return 0;
}
}  // namespace f0

namespace f1 {

ll best_us_turn_enemy(ll l, ll r, const vector<ll> &xs);
ll best_us_turn_us(ll l, ll r, const vector<ll> &xs);

static const ll NMAX = 5000 + 5;
bool dpdus[NMAX][NMAX];
ll dpus[NMAX][NMAX];

bool dpdenemy[NMAX][NMAX];
ll dpenemy[NMAX][NMAX];

ll best_us_turn_enemy(ll l, ll r, const vector<ll> &xs) {
    // assert(l <= r);
    if (l == r) {
        return 0;
    }

    if (dpdenemy[l][r]) {
        return dpenemy[l][r];
    }

    dpdenemy[l][r] = true;
    dpenemy[l][r] = std::min<ll>(best_us_turn_us(l + 1, r, xs),
                                  best_us_turn_us(l, r - 1, xs));
    return dpenemy[l][r];
}

ll best_us_turn_us(ll l, ll r, const vector<ll> &xs) {
    // assert(l <= r);
    if (l == r) {
        return xs[l];
    }

    if (dpdus[l][r]) {
        return dpus[l][r];
    }
    dpdus[l][r] = true;
    dpus[l][r] = std::max<ll>(xs[l] + best_us_turn_enemy(l + 1, r, xs),
                               xs[r] + best_us_turn_enemy(l, r - 1, xs));

    return dpus[l][r];
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n;
    cin >> n;
    vector<ll> xs(n);
    for (ll i = 0; i < n; ++i) {
        cin >> xs[i];
    }
    cout << best_us_turn_us(0, n - 1, xs) << "\n";
    return 0;
}
}  // namespace f1

int main() { f1::main(); }
