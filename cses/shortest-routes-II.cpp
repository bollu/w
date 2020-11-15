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

// use max + semiring for all pairs shortest, TLE.
namespace f0 {

const int N = 500 + 10;
const int C = int(1e9) + 7;
const int INFTY = 1e9;
int es[N*N];
int dists[N*N];
int n, m, q;

// A = B . C
void muldistt(int *out, const int *in1, const int *in2) {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            out[i*N+j] = in1[i*N+j];
            for(int k = 1; k <= n; ++k) {
                out[i*N+j] = min<int>(out[i*N+j], in1[i*N+k] + in2[k*N+j]);
            }
        }
    }
}



void printarr(int *arr) {
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            cout << arr[i*N+j] << " ";
        }
        cout << "\n";
    }
    cout << "---\n";
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> q;   

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            es[i*N+j]  = dists[i*N+j] =  INFTY;
        }
    }


    while(m--) {
        int a, b, c; cin >> a >> b >> c;
        es[a*N+b] = dists[a*N+b] = min<int>(es[a*N+b], c);
        es[b*N+a] = dists[b*N+a] = min<int>(es[b*N+a], c);
    }

    // printarr(dists[0]);

    bool ixin = 0;
    for(int i = 1; i <= 10; ++i) {
        muldistt(dists, dists, dists);
    }

    while(q--) {
        int a, b;
        cin >> a >> b;
        int d =  dists[a*N+b];
        if (d == INFTY) { cout << "-1\n"; }
        else { cout << d << "\n"; }
    }


    return 0;
}

}

int main() { return f0::main(); }