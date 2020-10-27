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


// This only works if we can pick the same book multiple times!
// we want zero or one!
// Best solution for problem:
// 4 10
// 4 8 5 3
// 5 12 8 1
//  Unrestriced: 
//    pick book with price=5, #pages=8 _twice_, giving us 16 pages.
//
//
// 0/1:
//   pick book with price=5, price=4 to give 8 + 5 = 13 pages.
namespace f0 {
static const int INFTY = 1e9 + 42;
static const int MAXPRICE = 1e5 + 5;
int dp[MAXPRICE];

struct Book {
    int pages;
    int price;
    bool operator<(const Book &o) { return price < o.price; };
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, maxprice;
    cin >> n >> maxprice;

    vector<Book> books(n);
    for (int i = 0; i < n; ++i) {
        cin >> books[i].price;
    }
    for (int i = 0; i < n; ++i) {
        cin >> books[i].pages;
    }


    sort(books.begin(), books.end());

    for(int p = 1; p <= maxprice; ++p) {
        cerr << "  p:"  <<p << "\n";
        for(int i = 0; i < n; ++i) {
            const Book b = books[i];
            if (b.price > p) { continue; }
            int cur = b.pages + dp[p - b.price];
            if (cur > dp[p]) {
                cerr << "    best=" << cur << " i="  << i << 
                    " pages=" << b.pages << " price=" << b.price <<" rest=dp[" << p - b.price << "]=" << 
                    dp[p-b.price] << "\n";
                dp[p] = cur;
            }
            // dp[p] = max<int>(dp[p], b.pages + dp[p - b.price]);
        }
    }


    cout << dp[maxprice] << "\n";

    return 0;
}
}

//Correctly perform 0/1 dp, but this TLEs.
namespace f1 {
static const int INFTY = 1e9 + 42;
static const int MAXPRICE = 1e5 + 5;
static const int MAXBOOKS = 1e3 + 5;
int dp[MAXPRICE][MAXBOOKS];

struct Book {
    int pages;
    int price;
    bool operator<(const Book &o) { return price < o.price; };
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, maxprice;
    cin >> n >> maxprice;

    vector<Book> books(n);
    for (int i = 0; i < n; ++i) {
        cin >> books[i].price;
    }
    for (int i = 0; i < n; ++i) {
        cin >> books[i].pages;
    }


    sort(books.begin(), books.end());


    for(int i = 0; i < books.size(); ++i) {
        const Book b = books[i];
        for(int p = b.price; p <= maxprice; ++p) {
            dp[p][i+1] = max<int>(dp[p][i], b.pages + dp[p - b.price][i]);
        }
    }
    cout << dp[maxprice][books.size()] << "\n";

    return 0;
}
}

// Use same trick as coins. Switch order of processing. Process books, not
// prices. Use double buffering instead of N buffers.
namespace f2 {
static const int INFTY = 1e9 + 42;
static const int MAXPRICE = 1e5 + 5;
static const int MAXBOOKS = 1e3 + 5;
ll dp[MAXPRICE][2];

struct Book {
    ll pages;
    ll price;
    bool operator<(const Book &o) { return price < o.price; };
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, maxprice;
    cin >> n >> maxprice;

    vector<Book> books(n);
    for (int i = 0; i < n; ++i) {
        cin >> books[i].price;
    }
    for (int i = 0; i < n; ++i) {
        cin >> books[i].pages;
    }


    sort(books.begin(), books.end());

    bool ixcur = 1;
    for(int i = 0; i < n; ++i) {
        bool ixnext = ixcur^1;
        const Book b = books[i];
        for(int p = b.price; p <= maxprice; ++p) {
            dp[p][ixnext] = max<ll>(dp[p][ixcur], b.pages + dp[p - b.price][ixcur]);
        }
        ixcur = ixnext;
    }
    cout << dp[maxprice][ixcur] << "\n";

    return 0;
}
}

int main() {
    f2::main();
}
