#include <optional>
#include <iostream>
using namespace std;

struct search {
    vector<int> as;
    search(vector<int> as)  : as(as) {}
    virtual optional<int> uniq_ix_query(int val) = 0;
    virtual optional<int> left_ix_query(int val) = 0;
    virtual optional<int> right_ix_query(int val) = 0;
};

struct dumb_search : search {
    dumb_search(vector<int> as) : search(as);
    optional<int> uniq_ix_query(int val) {
        for(int i = 0; i < as.size(); ++i) {
            if (as[i] == val) return i;
        }
        return optional::none;
    }
    virtual optional<int> left_ix_query(int val) {
        for(int i = 0; i < as.size(); ++i) {
            if (as[i] == val) return i;
        }
        return optional::none;
    }
    virtual optional<int> right_ix_query(int val) { 
        for(int i = as.size()-1; i >= 0; i--) {
            if (as[i] == val) return i;
        }
        return optional::none;
    }
};


int main() {
    // numbers 0 mod 10 are repeated, numbers nonzero mod 10 are not repeated.
    // This allows us to check for both left_ix_query, right_ix_query and uniq_ix_query
    vector<int> as = {10, 10, 10, 25, 30, 30, 45, 55, 65, 70, 70, 70, 70, 70, 85};
}
