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


struct sorter {
    pair<int, int> rank;
    int ix;

    bool operator <(const sorter &other) {
        return rank < other.rank;
    }
};


// returns suffix array.
// can I increment by *2+1?
vector<int> rankedSuffixes(string s) {
    const int n = s.size();
    assert(s[n-1] == '$');

    // index of string suffix space -> rank.
    vector<int> str2rank(n);
    // rank space -> index of string suffix.
    bool cur = 0;
    int len = 1;
    
    vector<sorter> rank2str[2];
    rank2str[0].resize(n); rank2str[1].resize(n);
    for(int i = 0; i < n; ++i) {
        rank2str[cur][i].rank.first = rank2str[cur][i].rank.second = s[i] - 'a';
        rank2str[cur][i].ix = i;
    }
    
    sort(rank2str[cur].begin(), rank2str[cur].end());
    for(int i = 0; i < n; ++i) {
        str2rank[rank2str[cur][i].ix] = i;
    }

    while(len <= n) {
        const bool next = cur ^ 1;
        for(int i = 0; i < n; ++i) {
            rank2str[next][i].ix = i;
            rank2str[next][i].rank.first = str2rank[i];
            rank2str[next][i].rank.second = i + len >= n ? str2rank[i] : str2rank[i + len];
        }
        cur = next;
        len *= 2;
        sort(rank2str[cur].begin(), rank2str[cur].end());
    
        for(int i = 0; i < n; ++i) {
            str2rank[rank2str[cur][i].ix] = i;
        }
    }
    vector<int> out(n);
    for(int i = 0; i < n; ++i) { out[i] = rank2str[cur][i].ix; }
    return out;
}

int main() {
    string s; cin >> s;
    s += '$';

    const int n = s.size();
    vector<int> rank2str = rankedSuffixes(s);

    cout << "sorted suffixes:\n";
    for(int i = 0; i < n; ++i) {
        cout << s.substr(rank2str[i]) << "\n";
    }

    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    return 0;
}