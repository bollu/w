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
    virtual optional<int> leftmost_eq(int val) = 0;
    virtual optional<int> leftmost_geq(int val) = 0;
    virtual optional<int> leftmost_greater(int val) = 0;
};

// given that as is sorted.
struct dumb_search : search {
    dumb_search(vector<int> as) : search(as) { }

    virtual optional<int> leftmost_eq(int val) {
        for(int i = 0; i < as.size(); ++i) {
            if (as[i] == val) return i;
        }
        return {};
    }
    
    virtual optional<int> rightmost_eq(int val) {
        for(int i = as.size()-1; i >= 0; i--) {
            if (as[i] == val) return i;
        }
        return {};
    }

    // return leftmost ix such that value is _not less than_. That is,
    // value is _greater than or equal to_.
    virtual optional<int> leftmost_geq(int val) {
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

// Note that floor and ceiling division is vitally important! We will denote
// [...] to be the full array and {..} as the subsetion of the array we are
// focused on.
//
// Let us say we are looking for the **leftmost index**. So when we have
// a[mid] = val, move [right -> mid].
// In the final corner case:
//
// [.... {5   5} ....] 
//        n  (n+1)
//
// we want to move [right=n+1] towards [mid=n]. So we need to make sure
// our [mid=n]. That is we want:
//     n = mid = round((left+right)/2) = round((n + (n+1))/2)
//     round(n+1/2) = n
//     round = floor
//
//
// On the other hand,  when we are looking for the **rightmost index**,
// we move [left -> mid] when we have equal values. Now in the corner case:
//
// [.... {5   5} ....] 
//        n  (n+1)
//
// we want to move [left=n] towards [mid=n+1]. So we need to make sure our
// [mid=n+1]:
//     n+1 = mid = round((left+right)/2) = round((n + (n+1))/2)
//     round(n+1/2) = n+1
//     round = ceil
struct bin_search : search {
    bin_search(vector<int> as) : search(as) { }

    optional<int> leftmost_eq(int val) {
        int left = 0, right = as.size()-1;
        while(left != right) {
            int mid = (left + right)/2;

            // left----------mid-----right
            // as[left] <= as[mid] <= as[right]
            
            if (mid == right) break; // hack!
            if (as[mid] < val) { left = mid+1; }
            else if (as[mid] == val) { right = mid; } // want leftmost eq
            else { right = mid-1; }
        }
        if (as[left] == val) { return left; } else { return {}; }

    }

    optional<int> rightmost_eq(int val) {
        int left = 0, right = as.size()-1;
        while(left != right) {
            // need to take ceiling here. why?
            int mid = (left + right+1)/2;
            cout << "rightmost_eq(" << val << ")" 
                 << "[" << left << "," << mid << ") " 
                 << mid <<"=" << as[mid] 
                 << " (" << mid << "," << right << "]"
                 << "\n";
            // left----------mid-----right
            // as[left] <= as[mid] <= as[right]
            if (as[mid] < val) { left = mid+1; }
            else if (as[mid] == val) { left = mid; } // want rightmost eq
            else { right = mid-1; }
        }
        if (as[left] == val) { return left; } else { return {}; }

    }

    // return leftmost ix such that value is that is greater than or
    // equal to.
    // value is _greater than or equal to_.
    optional<int> leftmost_geq(int val) {
        int left = 0, right = as.size()-1;
        while (left != right) {
            int mid = (left + right)/2;
            if(as[mid] < val) { left = mid + 1; }
            else if (as[mid] > val) { right = mid; } // this is tricky.
            else if (as[mid] == val) { right = mid; }
        }
        if (as[left] >= val) { return left; } else { return {}; }
    }

    // return leftmost ix such that value is _greater than_ val.
    virtual optional<int> leftmost_greater(int val) { 
        int left = 0, right = as.size()-1;
        while(left != right) {
            int mid = (left + right)/2;
            if (as[mid] <= val) {  left = mid+1; }
            else { right = mid; } 
        }
        if (as[left] > val) { return left; } else { return {}; }
    }
};

// written using [left, len) notation.
struct bin_search2: public search {
    bin_search2(vector<int> as) : search(as) { }

    // find leftmost `ix` in `as` where `as[ix] = val`. Return `none`
    // if such an index does not exist.
    optional<int> leftmost_eq(int val) { 
        int left = 0; 
        int len = as.size(); 
        while(len > 0) {
            // TODO: meditate on why this is correct.
            const int mid = left + len/2;
            // the +1 is very important, otherwise the technique gives
            // wrong answers, not just infinite loops!
            if (as[mid] < val) { left = mid+1; }
            len /= 2;
        }
        if (as[left] == val) { return left; } else { return {}; };
    }
    optional<int> rightmost_eq(int val) { 
        int right = as.size()-1; 
        int len = as.size(); 
        while(len > 0) {
            // TODO: meditate on why this is correct.
            const int mid = right - len/2;
            // the -1 is very important, otherwise the technique gives
            // wrong answers, not just infinite loops!
            if (as[mid] > val) { right = mid-1; }
            len /= 2;
        }
        if (right < 0) { return {}; }
        if (as[right] == val) { return right; } else { return {}; };
    }

    optional<int> leftmost_geq(int val) { 
        int left = 0; 
        int len = as.size(); 
        while(len > 0) {
            // TODO: meditate on why this is correct.
            const int mid = left + len/2;
            // the +1 is very important, otherwise the technique gives
            // wrong answers, not just infinite loops!
            if (as[mid] < val) { left = mid+1; }
            len /= 2;
        }
        if (as[left] >= val) { return left; } else { return {}; };
    }
    optional<int> leftmost_greater(int val) { return {}; }
};

template<typename T>
ostream &operator <<(ostream &os, optional<T> opt) {
    if (opt) { return os << *opt; } else { return os << "none"; }
}

void test(vector<int> as) {
    dumb_search dumb(as);
    bin_search bin(as);

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.leftmost_eq(i);
        optional<int> ix = bin.leftmost_eq(i);
        cout << "leftmost_eq(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    cout << "LEFTMOST EQ 1 SUCCEEDED\n";


    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.rightmost_eq(i);
        optional<int> ix = bin.rightmost_eq(i);
        cout << "rightmost_eq(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    cout << "RIGHTMOST EQ 1 SUCCEEDED\n";

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.leftmost_geq(i);
        optional<int> ix = bin.leftmost_geq(i);
        cout << "leftmost_geq(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    cout << "LEFTMOST GEQ1 SUCCEEDED\n";

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.leftmost_greater(i);
        optional<int> ix = bin.leftmost_greater(i);
        cout << "leftmost_greater(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    cout << "LEFTMOST GREATER1 SUCCEEDED\n";


    /*
    bin_search2 bin2(as);

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.leftmost_eq(i);
        optional<int> ix = bin2.leftmost_eq(i);
        cout << "leftmost_eq(" << i << "): dumb=" << dumbix << " | bin2=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    cout << "LEFTMOST EQ 2 SUCCEEDED\n";

     for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.rightmost_eq(i);
        optional<int> ix = bin2.rightmost_eq(i);
        cout << "rightmost_eq(" << i << "): dumb=" << dumbix << " | bin2=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    cout << "RIGHTMOST EQ 2 SUCCEEDED\n";

    for(int i = 0; i < 100; ++i) {
        optional<int> dumbix = dumb.leftmost_geq(i);
        optional<int> ix = bin2.leftmost_geq(i);
        cout << "leftmost_geq(" << i << "): dumb=" << dumbix << " | bin=" << ix << "\n";
        cout.flush();
        assert(dumbix == ix);
    }

    cout << "LEFTMOST GEQ2 SUCCEEDED\n";
    */
}


int main() {
    // numbers 0 mod 10 are repeated, numbers nonzero mod 10 are not repeated.
    // This allows us to check for both leftmost_geq, leftmost_greater and ix
    //                0    1   2   3   4   5   6   7
    vector<int> as = {10, 10, 10, 25, 30, 30, 45, 55, 65, 70, 70, 70, 70, 70, 85};
    test(as);
    // test both lengths, odd and even.
    as.push_back(90);
    test(as);
    return 0;
}
