#include <assert.h>
#include <stdlib.h>  // for exit()

#include <algorithm>
#include <bitset>  // instead of bool[N];
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

// min priority queue. Useful for djikstras, or in general, to be
// explicit.
template <typename T>
using minqueue = priority_queue<T, vector<T>, greater<T>>;

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

using namespace std;

template <typename Fn>
void test_subseq(Fn f, Fn ref, int maxl, int nentries) {
    int nwrong = 0; int ntot = 0;
    for (int l = 0; l < maxl; l++) {
        for (int k = 0; k < pow(nentries, l); ++k) {
            cout << "### l:" << l << " k:" << k << " ###\n";
            ntot++;
            vector<int> xs(l, 0);
            int gen = k;
            for (int ix = 0; ix < l; ++ix) {
                xs[ix] = gen % nentries;
                gen = gen / nentries;
            }

            cout << "\txs:";
            for (int x : xs) {
                cout << x << " ";
            }
            cout << "\n";

            const int out = f(xs);
            const int ref_out = ref(xs);

            if (out != ref_out) {
                cout << "\tINCORRECT| f(xs):" << out << " | ref(xs):" << ref_out
                     << "\n";
                getchar();
                nwrong++;
            } 
        }
    }
    cout << "\n@@@ TOTAL: " << ntot << "| correct: " << ntot - nwrong << " | wrong: " << nwrong << " @@@\n";
}

int f(vector<int> &xs) {
    const int n = xs.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));
    int best = 0;

    for (int r = 0; r < n; ++r) {
        best = max<int>(best, 1);
        for (int m = 0; m < r; ++m) {
            best = max<int>(best, 2);
            dp[m][r] = 2;
            for (int l = 0; l < m; ++l) {
                if (2 * xs[m] < xs[l] + xs[r]) {
                    dp[m][r] = max<int>(dp[m][r], 1 + dp[l][m]);
                }
                best = max<int>(best, dp[m][r]);
            }
            cout << "\tdp["<<m<<"]["<<r<<"]=" << dp[m][r] << "\n";
        }
    }

    return best;
}

bool is_convex(vector<int> &xs, vector<int> &ixs) {
    const int n = ixs.size();
    vector<int> ys(n, 0);
    for(int i = 0; i < n; ++i) {
        ys[i] = xs[ixs[i]];
    }

    for (int r = 0; r < n; ++r) {
        for (int m = 0; m < r; ++m) {
            for (int l = 0; l < m; ++l) {
                bool conv = 2 * ys[m] < ys[l] + ys[r];
                if (!conv) {
                    return false;
                }
            }
        }
    }
    return true;
}

int ref(vector<int> &xs) {
    vector<int> best; // best indexes for subsequence.
    const int n = xs.size();
    for (int mask = 0; mask <= 1 << n; ++mask) {
        vector<int> is;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                is.push_back(i);
            }
        }
        if (is_convex(xs, is) && is.size() > best.size()) {
            best = is;
        }
    }
    cout << "\tref: ";
    for (int ix : best) {
        cout << "[" << ix << "]" << xs[ix] << "  ";
    }
    cout << "\n";
    return best.size();
};
int main() { test_subseq(f, ref, 7, 5); }

