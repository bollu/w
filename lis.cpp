#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 9;

template<typename T>
ostream &operator << (ostream &os, const vector<T> &xs) {      
    os << "[";
    for(int i = 0; i < xs.size(); ++i) {
        os << xs[i];
        if (i < (int)xs.size() - 1) os << ", ";
    }
    return os << "]";
}

template<typename T>
void subseqs_(const int i, const vector<T> &xs, vector<vector<T>> &xss) {
    if (i == xs.size()) { return; }
    const int nxss = xss.size();
    for(int j = 0; j < nxss; ++j) {
        vector<T> cur = xss[j]; cur.push_back(xs[i]);
        xss.push_back(cur);
    }
    subseqs_(i+1, xs, xss);
}

template<typename T>
vector<vector<T>> subseqs(const vector<T> &xs) {
    vector<vector<T>> xss;
    xss.push_back({});
    subseqs_(0, xs, xss); return xss;
}

template<typename T>
bool nondecreasing(const vector<T> &v) {
    for(int i = 0; i < (int) v.size()-1; ++i) { 
        if (v[i+1] < v[i]) { 
            return false;
        }
    }
    return true;
}

vector<int> lis_spec(const vector<int> &xs) {
    vector<vector<int>> xss = subseqs(xs);
    int maxlen = -1, maxix = -1;
    for(int i = 0; i < xss.size(); ++i) {
        if (nondecreasing(xss[i]) && 
            (int)xss[i].size() > maxlen) { 
            maxlen = xss[i].size(); maxix = i;
        }
    }
    assert(maxlen != -1);
    assert(maxix != -1);
    return xss[maxix];
}

int lis_len_spec(const vector<int> &xs) {
    return lis_spec(xs).size();
}

int s[2*N];
void segtree_init() {
    for(int i = 0; i < 2*N; ++i) s[i] = 0;
    // for(int i = N-1; i >= 1; --i) { s[i] = xs[2*i] + xs[2*i+1]; }
}

int segtree_maxrange_inclusive(int l, int r) {
    int res = 0;
    for(int i = l; i <= r; ++i) { res = max(res, s[i]); }
    return res;
}

void segtree_set(int ix, int val) {
    s[ix] = val;
}

int lislen(const vector<int> xs) {
    assert(xs.size() == N);
    segtree_init();
    // everything is 0-initialized.

    int maxlen = 0;
    for(int i = 0; i < N; ++i) {
        // set s[xs[i]]: find max in [0..i] and then update xs[i]
        // use fenwick tree?
        int curlen = segtree_maxrange_inclusive(0, xs[i]) + 1; 
        cout << "\n* xs[" << i << "] = " << xs[i] << " | curlen: " << curlen;
        segtree_set(xs[i], curlen);
        if (curlen > maxlen) maxlen = curlen;
    }
    return maxlen;

}

int main(int argc, const char **argv) {
    vector<int> xs;
    for(int i = 0; i < N; ++i) { xs.push_back((i/2)); }

    do {
        cout << "\nconsidering: " << xs << "...";
        const vector<int> lisref = lis_spec(xs);
        const int l = lislen(xs);
        if (l != lisref.size()) {
            cout << "\n\tLIS failed out: |" << xs;
            cout << "\n\treference lis: " << lisref;
            cout << "\n\treference lis length: " << lisref.size();
            cout << "\n\treported lis length (WRONG): " << l;
            exit(1);
        } else { cout << "\nsuccess"; }
    } while(std::next_permutation(xs.begin(), xs.end()));
}
