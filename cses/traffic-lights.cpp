#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
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

int main() {
    int x;
    cin >> x;
    int n;
    cin >> n;

    ordered_set<int> xs;
    xs.insert(0);
    xs.insert(x);

    std::map<int, int> start2dist;
    start2dist[0] = x + 1;  // full segment distance.

    // we fake a multiset by counting how many times a distance has occured
    // this is obviously fucked. 
    // - For whatever reason, std::multiset::erase(value)
    // removes *all* occurences of value
    //
    // - the "suggested" std::multiset::erase(std::multiset::find(value))
    // **HANGS** !
    std::map<int, int> dist2count;
    dist2count[x+1] = 1;

    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        auto it = xs.insert(v).first;
        auto it_prev = it;
        it_prev--;
        auto it_next = it;
        it_next++;

        auto prev_dist = start2dist.find(*it_prev);
        assert(prev_dist != start2dist.end());
        // erase the distance of the previous segment.
        auto it_dist2count = dist2count.find(prev_dist->second);
        it_dist2count->second--;
        if (it_dist2count->second == 0) {
            dist2count.erase(it_dist2count);
        }

        int distl = *it - *it_prev;
        int distr = *it_next - *it;

        if (distl > 0) { 
            start2dist[int(*it_prev)] = distl;
            dist2count[distl]++;
        }
        if (distr > 0) { 
            start2dist[int(*it)] = distr;
            dist2count[distr]++;
        }


        cout << dist2count.rbegin()->first << " ";
    }
    cout << "\n";
    return 0;
}
