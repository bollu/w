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

const int N = 1e5 + 10;
int ps[N];
ll compSize[N];
int subtreeHeight[N];

// want max(subtree size) to be bounded.
int root(int i) {
    if (i == ps[i]) { return i; }
    return i = root(ps[i]);
}

pair<bool, int> unite(int i, int j) {
    i = root(i); j = root(j);
    if (i == j) { return {false, 0}; }

    if (subtreeHeight[i] > subtreeHeight[j]) {
        ps[j] = i; compSize[i] += compSize[j];
        return {true, compSize[i]};
    } else if (subtreeHeight[i] < subtreeHeight[j]) {
        ps[i] = j; compSize[j] += compSize[i];
        return {true, compSize[j]};
    } else {
        ps[i] = j; compSize[j] += compSize[i]; subtreeHeight[j]++;
        return {true, compSize[j]};
    }
}

int n, m;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i = 1; i < N; ++i) { ps[i] = i; compSize[i] = 1; }

    int ncomp = n;
    ll maxCompSz = 1;
    for(int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;
        bool joined;
        ll newCompSz;
        tie(joined, newCompSz) =  unite(a, b);
        maxCompSz = max<ll>(maxCompSz, newCompSz);
        ncomp = joined ? ncomp - 1 : ncomp;
        cout << ncomp << " " << maxCompSz << "\n";
    }
    
    return 0;
}
