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

static const int NMAX = 2 * int(1e5) + 10;
int tree[4*NMAX+10];
int dp[NMAX+10];

// half-open: nr == nl + 1 \/ nr >= nl + 2
// [nl, nr): nr >= nl + 2
// (nl + nr)/2 >= nl + 1
// nl < nl + 1 <= mid < nr

// closed-closed:
// sum of adjacent numbers is always odd...
// [nl, nr]: nl == nr or nr >= nl + 1
// [nl, mid-1] [mid, nr]


// find max value in range [ql..qr]. Node is at [nl...nr].
int rangeq(int ql, int qr, int nix, int nl, int nr) {
    // int out = -1;
    // for(int i = ql; i <= qr; i++) {
    //     out = max(out, tree[i]);
    // }
    // cout << "rangeq[" << ql << ".." << qr << "]=" << out << "\n";
    // return out;


    if (qr < nl || nr < ql) { return -100; }
    if (ql <= nl && nr <= qr) { return tree[nix]; }
    int nmid = (nl + nr)/2;
    return max(rangeq(ql, qr, 2*nix, nl, nmid), rangeq(ql, qr, nix*2+1, nmid+1, nr));
}

void setq(int ix, int val, int nix, int nl, int nr) {
    // cout << "setq(" << ix << "=" << val << ")\n";
    // tree[ix] = val;
    // return;

    // cerr << ix << "=" << val << " | " << nix << "[" << nl << ", " << nr << "]\n";
    if (ix < nl || nr < ix) { return; }
    if (nl == nr) { tree[nix] = val; return; }
    int nmid = (nl + nr)/2;
    if (ix <= nmid) { setq(ix, val, nix*2, nl, nmid); }
    else { setq(ix, val, nix*2+1, nmid+1, nr); }
    tree[nix] = max(tree[nix*2], tree[nix*2+1]); 
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n; cin >> n;
    vector<int> xs(n);
    std::set<int> uniqs;
    for(int i = 0; i < n; ++i) { 
        cin >> xs[i];
        uniqs.insert(xs[i]); 
    }

    // create compressed version that has the right size.
    map<int, int> compress;
    for(int i : uniqs) { compress[i] = compress.size(); }

    int best = 0;
    for(int i = 0; i < n; ++i) {
        if (i == 0) { 
            setq(compress[xs[i]], 1, 1, 0, NMAX);
            best = 1;
        }
        else {
            // >>> math.log(1e5)
            // 11.512925464970229
            int nlt = rangeq(0, compress[xs[i]]-1, 1, 0, NMAX); 
            setq(compress[xs[i]], 1 + nlt, 1, 0, NMAX);
            best = max(best, 1 + nlt);
        }
    }

    cout << best << "\n";


    return 0;
}
