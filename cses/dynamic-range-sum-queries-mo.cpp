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

const ll N = 2 * ll(1e5) + 10;
ll arr[N];
ll bsz;
ll block[N];

void debug(int n) {
    cout << "\n====vv===\n";
    for(int i = 0; i < n; ++i) { cout << "[" << i << "]" << arr[i] << " "; }
    cout << "\n";
    cout << "bsz: " << bsz << "   " ;
    for(int i = 0; i < n; ++i) {
        cout << "[" << i*bsz << "-" << (i+1)*bsz << "):" << block[i] << " ";
    }
    cout << "\n====^^===\n";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n, q; cin >> n >> q;
    bsz = sqrt(n);
    for(ll i = 0; i < n; ++i) { 
        cin >> arr[i];
        block[i/bsz] += arr[i];
    }
    // debug(n);



    // n = 10, block size = sqrt(10) = 3
    // 
    // i   | 0 1 2 | 3 4 5 | 6 7 8 | 9
    // i/3 | 0 0 0 | 1 1 1 | 2 2 2 | 3
    //
    // block k holds values of [k*sz, (k+1)*sz)
    // 1...7 => blocks: 1/3 -- 7/3 ->  0...2 BLOCKS 


    while(q--) {
        ll ty; cin >> ty;
        if (ty == 1) {
            ll k, u; cin >> k >> u;
            k--;
            // cout << "upd(k=" << k << " u=" << u << ")\n";
            ll delta = u - arr[k];
            arr[k] += delta;
            block[k/bsz] += delta;
            // debug(n);

        } else {
            ll ql, qr; cin >> ql >> qr; ql--; qr--;
            ll out = 0;
            // cout << "query(ql=" << ql << " qr=" << qr << ")\n";

            // move LHS to boundary
            while(ql % bsz != 0 && ql <= qr) {
                out += arr[ql]; ql++;
                // cout << "\tincremented: ql[" << ql << "] out[" << out << "]\n";
            }

            // [ql, ql+bsz) < [ql, qr]
            // jump blocks.
            while(ql + bsz < qr) {
                out += block[ql/bsz];
                ql += bsz;
                // cout << "\tincremented: ql[" << ql << "] out[" << out << "]\n";
            }

            // recuperate end blocks.
            while(ql <= qr) {
                out += arr[ql];
                ql++;
                // cout << "\tincremented: ql[" << ql << "] out[" << out << "]\n";
            }
            
            cout << out << "\n";

        }
    }
    return 0;
}
