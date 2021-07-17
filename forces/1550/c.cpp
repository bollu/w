#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

struct Vertex {
    ll sum = 0;
    ll c, d; // children
};

static const int N = 2e5 + 10;
static const int LOGN = 20;

// Vertex: (8 byte * 3) = 24 byte
// array size: (4 * 2e5 * 20) = 16e5 < 2e6
// total: 24 byte * 2e6 = 48e6 < 100e6 = 1e8 = 100MB
Vertex vs[4 * N * LOGN];
ll nvs = 0;

// vertex controls region [s..t]
ll build(ll s, ll t) {
    assert(nvs < 4 * N * LOGN);
    assert(s <= t);
    const ll n = ++nvs;
    if (s == t) {
        vs[n].c = vs[n].d = -1;
        vs[n].sum = 0;
        return n;
    } else {
        const ll mid = (s + t) / 2;
        vs[n].c = build(s, mid);
        vs[n].d = build(mid + 1, t);
        vs[n].sum = 0;
        return n;
    }
}

// query: [q, r]
// tree: i
// tree node range: [s, t]
ll rangeq(ll q, ll r, ll i, ll s, ll t) {
    assert(q <= r);
    assert(s <= t);
    // [q..r][s..t]
    // [s..t][q..t]
    if (r < s || t < q) {
        return 0;
    }
    // [q..[s..t]..r]
    else if (q <= s && t <= r) {
        return vs[i].sum;
    } else {
        const ll mid = (s + t) / 2;
        return rangeq(q, r, vs[i].c, s, mid) +
               rangeq(q, r, vs[i].d, mid + 1, t);
    }
}

// update index: q
// update value: u
// tree: i
// tree range: [s, t]
ll upd(ll q, ll u, ll i, ll s, ll t) {
    assert(i != -1);
    assert(s <= t);
    assert(s <= q);
    assert(q <= t);

    const ll j = ++nvs;
    assert(nvs < 4 * N * LOGN);
    vs[j] = vs[i];
    if (s == t) {
        vs[j] = vs[i];
        vs[j].sum += u;
        return j;
    } else {
        ll mid = (s + t) / 2;
        if (q <= mid) {
            vs[j].c = upd(q, u, vs[j].c, s, mid);
        } else {
            vs[j].d = upd(q, u, vs[j].d, mid + 1, t);
        }
        vs[j].sum = vs[vs[j].c].sum + vs[vs[j].d].sum;
        return j;
    }
}

// [l..r] is good => in the range [l+1..r-1] there is no occurence of a value k
// with value vl and vr.

// goodAll[l][r]: tells us if all subranges of [l..r] are good(.., l, r).
// TODO: find out how many such pairs exist!
// 8 byte * 2 * N 
// = 16 byte * 2e5 = 32e5 byte < 100e5 byte  = 1e7 byte  = 10MB
ll goodAll[2][N];
// 4 byte * N
// = 4 * 2e5
// =  8e5 < 10e5 = 1e6 = 1MB  
int as[N];
ll n;

// = 1MB
ll roots[N];
// total: 100MB + 10MB + 1MB + 1MB << 256 MB 

ll good(map<int, int> &compress, ll l, ll r) {
    assert(l >= 0);
    assert(r >= 0);
    assert(l < n);
    assert(r < n);
    assert(r >= l);
    if (l == r) {
        return true;
    } else {
        assert(r > l);  // => r >= 1

        const ll vl = min(compress[as[l]], compress[as[r]]);
        const ll vr = max(compress[as[l]], compress[as[r]]);

        const ll nl = rangeq(vl, vr, roots[l], 0, N);
        const ll nr = rangeq(vl, vr, roots[r - 1], 0, N);
        bool out = (nr - nl) == 0;
        assert(nr >= nl);
        return out;
    }
}


int main() {
    ios::sync_with_stdio(false);
    // sum[n] = 1 + 2 + ... n
    // sum[0] = 0;
    // for (int i = 1; i < LEN; ++i) {
    //   sum[i] = i + sum[i - 1];
    // }
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        map<int, int> compress;
        for (int i = 0; i < n; ++i) {
            cin >> as[i];
            compress[as[i]];
        }

        int compressed = 0;
        for (auto it : compress) {
            compress[it.first] = compressed++;
        }

        // cerr << "***as: ";

        // for (int i = 0; i < n; ++i) {
        //   cerr << "[" << i << "]" << as[i] << " ";
        // }
        // cerr << "***\n";

        // --
        roots[0] = build(0, N);
        roots[0] = upd(compress[as[0]], 1, roots[0], 0, N);
        for (int i = 1; i < n; ++i) {
            roots[i] = upd(compress[as[i]], 1, roots[i - 1], 0, N);
        }

        // This fails for test case:
        //  - [10 1000 500 25] -> we have a bad subrange [1000 500 25].
        /// - But for the above, we count the entire range as
        //    good since we try to find a point in
        //    [10..25] to determine badness. There are no such points!
        // - So we must DP over subranges as well.
        // for (int l = 0; l < as.size(); ++l) {
        //   for (int r = l; r < as.size(); ++r) {
        //     if (good(roots, compress, as, l, r)) {
        //       cerr << "\tgood " << l << " " << r;
        //       cerr << "[";
        //       for(int k = l; k <= r; ++k) {
        //         cout << "[" << k << "]" << as[k] << " ";
        //       }
        //       cerr << "]\n";
        //       tot++;
        //     } else {
        //       break;
        //     }
        //   }
        // }
        ll tot = 0;
        bool buffer = 0;
        for (int l = 0; l < n; ++l) {
            goodAll[buffer][l] = 1;
            tot += 1;
        }

        for (int len = 1; len < n; ++len) {
            buffer = !buffer;
            for (int l = 0; l < n; ++l) {
                int r = l + len;
                if (r >= n) {
                    break;
                }
                goodAll[buffer][l] =
                    (l + 1 < n ? goodAll[!buffer][l + 1] : true) &&
                    (r - 1 >= 0 ? goodAll[!buffer][l] : true) &&
                    good(compress, l, r);
                tot += goodAll[buffer][l];
            }
        }

        cout << tot << "\n";
    }
}
