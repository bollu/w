#include <assert.h>

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
// #include <pstl/execution_defs.h>
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

// len: length of equiv class representative (longest string)
struct Node {
    int len;
    Node *suflink;
    Node *next[26];
    Node() {
        suflink = nullptr;
        len = 0;
        for(int i = 0; i < 26; ++i) next[i] = nullptr;
    }

    Node(const Node &other) {
        this->len = other.len;
        this->suflink = other.suflink;
        for(int i = 0; i < 26; ++i) next[i] = other.next[i];

    }
};

Node *first;
Node *last;

void init() {
    first = last = new Node();
    first->suflink = nullptr;
    first->len = 0;
}

void extend(const char c) {
    Node *const newlast = new Node();
    newlast->len = last->len + 1;

    const int ci = c -'a';
    Node *suf = last;
    last = newlast;

    while(suf->next[ci] == nullptr) {
        suf->next[ci] = last;
        if (suf == first) { 
            last->suflink = first;
            return;
        }
        suf = suf->suflink;
    }

    assert(suf->next[ci]);
    Node *p = suf;
    Node *q = suf->next[ci];
    if (p->len + 1 == q->len) {
        last->suflink = q;
        return;
    }

    assert(q->len > 1 + p->len);

    // split the equiv. class of q at p:c
    Node *splitq = new Node(*q);
    splitq->len = p->len + 1;
    last->suflink = q->suflink = splitq;

    // p's and p's suffixes  transitions to q to splitq.
    while(p->next[ci] == q) {
        p->next[ci] = splitq;
        if (p == first) { return; }
        p = p->suflink;
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string s; cin >> s;
    init();
    for(char c : s) { extend(c);}

    int k; cin >> k;
    while(k--) {
        string t; cin >> t;
        Node *cur = first;
        for (char c : t)  {
            const int ci = c - 'a';
            cur = cur->next[ci];
            if (!cur) { break; }
        }
        if (cur) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }


    }
    return 0;
}
