#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>
#include <bitset> // instead of bool[N];
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

// weighted interval scheduling: https://courses.cs.washington.edu/courses/cse521/13wi/slides/06dp-sched.pdf

struct P {
    ll a, b, p;
    // Must sort by finishing time!
    // Why? because when we recurse, we want to know that we are processing
    // previous jobs that have *finished*
    bool operator <(const P &other) const {
        return b < other.b;
    }
};

// find rightmost ix such that ps[ix].b < t
// TODO: how to write this with closed llervals?!
ll max_earlier(ll t, vector<P> &ps) {
    // cerr << "t: " << t << "\n";
    ll l = 0, r = ps.size();
    // closed llerval.
    while (1) {
        if (l + 1 == r) { break; }
        // l + 1 < r
        // r >= l + 2
        ll mid = (l + r)/2;
        // mid >= (l + l + 2)/2 >= l + 1
        // l < l+1 <= mid < l + 2 <= r
        // l < mid < r
        if (ps[mid].b >= t) {
            // [l, r) -> [l, mid) | mid < r
            r = mid;
        } else {
            // [l, r) -> [mid, r) | l < mid
            l = mid;
        }
    }
    // cerr << "\tl: " << l << " ps[l]: " << ps[l].a << " " << ps[l].b << " " << ps[l].p << "\n";
    assert(ps[l].b < t);
    if (l + 1 < ps.size()) { assert(ps[l+1].b >= t); }
    return l;
}

map<ll, ll> dp;

ll best(ll i, vector<P> &ps) {
    if (i == 0) { return ps[0].p; }
    // find last job that ends before this one begins.
    auto it = dp.find(i);
    if (it != dp.end()) { return it->second; }

    ll previ = max_earlier(ps[i].a, ps);
    assert(ps[previ].b < ps[i].a);
    ll out =  max(best(i-1, ps), ps[i].p + best(previ, ps));

    // if (best(i-1, ps) < ps[i].p + best(previ, ps)) { cerr << "pick[" << previ << " →" << i << "]!" << out << "\n"; }
    // else { cerr << i << " =COPY= " << i-1 << "!" << out << "\n"; }
    return dp[i] = out;
};


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n; cin >> n;
    vector<P> ps(n+1);
    ps[0].a = ps[0].b = -100; ps[0].p = 0;
    for(ll i = 0; i < n; ++i) {
        cin >> ps[i+1].a >> ps[i+1].b >> ps[i+1].p;
    }
    sort(ps.begin(), ps.end());

    // for(ll i = 0; i < ps.size(); ++i) {
    //     cerr << "ps[" << i << "]: " << ps[i].a << " " << ps[i].b << " " << ps[i].p << "\n";
    // }
    cout << best(ps.size()-1, ps) << "\n";


    return 0;
}

