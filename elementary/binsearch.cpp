#include<functional>
#include <optional>
#include <iostream>
#include <assert.h>
using namespace std;

struct search {
    vector<int> as;
    search(vector<int> as)  : as(as) {
        for(int i = 0; i < as.size() - 1; ++i) { assert(as[i] <= as[i+1]); }
    }
    virtual optional<int> ix(int val) = 0;
    virtual optional<int> leftmost_not_less_than(int val) = 0;
    virtual optional<int> leftmost_greater(int val) = 0;
};

// given that as is sorted.
struct dumb_search : search {
    dumb_search(vector<int> as) : search(as) { }

    optional<int> ix(int val) {
        for(int i = 0; i < as.size(); ++i) {
            if (as[i] == val) return i;
        }
        return {};
    }
    // return leftmost ix such that value is _not less than_. That is,
    // value is _greater than or equal to_.
    virtual optional<int> leftmost_not_less_than(int val) {
        for(int i = 0; i < as.size(); ++i) {
            if (as[i] >= val) return i;
        }
        return {};
    }

    // return leftmost ix such that value is _greater than_.
    virtual optional<int> leftmost_greater(int val) { 
        for(int i = 0; i < as.size(); ++i) {
            if (as[i] > val) return i;
        }
        return {};
    }
};

template<typename T>
ostream &operator <<(ostream &os, optional<T> opt) {
    if (opt) { return os << *opt; } else { return os << "none"; }
}


int main() {
    // numbers 0 mod 10 are repeated, numbers nonzero mod 10 are not repeated.
    // This allows us to check for both leftmost_not_less_than, leftmost_greater and ix
    vector<int> as = {10, 10, 10, 25, 30, 30, 45, 55, 65, 70, 70, 70, 70, 70, 85};
    dumb_search dumb(as);
    dumb_search bin(as);

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.ix(i);
        optional<int> ix = bin.ix(i);
        cout << "uniq_ix(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.leftmost_not_less_than(i);
        optional<int> ix = bin.leftmost_not_less_than(i);
        cout << "uniq_ix(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.leftmost_greater(i);
        optional<int> ix = bin.leftmost_greater(i);
        cout << "uniq_ix(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }
}
