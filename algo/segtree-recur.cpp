// segtree: https://codeforces.com/problemset/problem/1234/D
#include<iostream>
#include<utility>
#include<tuple>
#include<algorithm>
#include<assert.h>
#include<stdlib.h>
#include<sstream>
using namespace std;

struct segtree {
    segtree(int n) {}
    virtual void set(int ix, int val) = 0;
    // [l, r)
    virtual int rangeq(int l, int r) = 0;
};

struct segtree_dumb : public segtree {
    vector<int> as;
    segtree_dumb(int n) : segtree(n), as(n+1) { for(int &a: as) a = 0; }
    void set(int ix, int val) { assert(ix < as.size()); assert(ix >= 0); as[ix] = val; }
    int rangeq(int lix, int rix) { int s=0; for(int i=lix;i<rix;++i) { s += as[i]; } return s; }
};

struct segtree_fancy : public segtree {
    vector<int> as; int n;
    segtree_fancy(int n) : segtree(n), as(4*n), n(n) {
        for(int i = 0; i < 4*n; ++i) { as[i] = 0; }
    }

    /*
    int set_(int qix, int qval, int node_left, int node_ix, int node_right) {
        cout << "as[" << qix << "]=" << qval << " | [" << node_left << "--" << node_ix << "--" 
            << node_right <<")\n";
        int len = node_right - node_left;
        assert(node_left <= node_right);
        assert(len >= 0);
        if (len == 0) { return 0; }

        // query out of range
        if (qix < node_left || qix >= node_right) { return as[node_ix]; } 
        // query in range, index in range
        if (len == 1 && qix == node_left) { return as[node_ix] = qval; }
        // cout << __FUNCTION__ << "[" <<node_left << "--" << len << "--" << node_right << "]\n";
        int node_mid = (node_left + node_right)/2;
        return as[node_ix] = set_(qix, qval, node_left, node_ix*2, node_mid) + 
                             set_(qix, qval, node_mid, node_ix*2+1, node_right);
    }
    */

    void set_(int qix, int qval, int node_left, int node_ix, int node_right) {
        cout << "as[" << qix << "]=" << qval << " | [" << node_left << "--" << node_ix << "--" << node_right <<")\n";
        cout.flush();
        int len = node_right - node_left;
        assert(node_left <= node_right);
        assert(len >= 0);
        // out of bounds.
        if (!(qix >= node_left && qix < node_right))  { return; }
        
        as[node_ix] += qval;
        if (len <= 1) return; 
        int node_mid = (node_left + node_right)/2;
        if (qix < node_mid) {
            set_(qix, qval, node_left, node_ix*2, node_mid);
        } else {
            set_(qix, qval, node_mid, node_ix*2+1, node_right); 
        }
    }

    int rangeq_(int ql, int qr, int node_left, int node_ix, int node_right) {
        stringstream ss;
        ss << "q[" << ql << "," << qr << ") | [" << node_left << "--" << node_ix << "--" << node_right <<")";
        int len = node_right - node_left;
        assert(ql <= qr);
        assert(node_left <= node_right);
        assert(len >= 0); if (len == 0) { ss << ":" << __LINE__ << "= 0\n"; cerr << ss.str();  return 0; }

        // [ql---q---qr) [node_left, node_right) [ql---q---qr)
        if (qr <= node_left || ql >= node_right) { 
            ss << ":" << __LINE__ << " = 0\n"; cerr << ss.str(); return 0;
        }
        //[ql--[node_left---node_right)--qr)
        if (ql <= node_left && node_right <= qr) { 
            ss << ":" << __LINE__ << " = " << as[node_ix] << "\n"; cerr << ss.str(); 
            return as[node_ix];
        }

        // cerr << __FUNCTION__ << "[" <<node_left << "--" << len << "--" << node_right << "]\n";
        int node_mid = (node_left + node_right)/2;
        int ans= rangeq_(ql, qr, node_left, node_ix*2, node_mid) +
            rangeq_(ql, qr, node_mid, node_ix*2+1, node_right);

        ss << ":" << __LINE__ << " = " << ans << "\n";
        cerr << ss.str();
        return ans;
    }

    void set(int ix, int val) { set_(ix, val, 1, /*root=*/1, n+1); };
    int rangeq(int lix, int rix) { return rangeq_(lix, rix, 1, /*root=*/1, n+1); }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    srand(0);
    const int N = 10;
    const int TESTS = 1000;
    segtree_dumb dumb(N);
    segtree_fancy fancy(N);

    for(int i = 0; i < TESTS; ++i) {
        if (i % 2) {
            int ix = 1 + rand() % N;
            int val = (1+ rand() % 3) * (rand() % 2 ? 1 : -1);
            cout <<"as[" << ix << "] = " << val <<"\n";
            dumb.set(ix, val); fancy.set(ix, val);
        } else {
            int l = rand() % N; int r = min(l + rand() % N, N);
            cout << "as[[" << l << ", " << r <<")]:\n";
            cout << "\tdumb.rangeq = " << dumb.rangeq(l, r) << " | fancy.rangeq = " << fancy.rangeq(l, r) << "\n";
            cout.flush();
            assert(dumb.rangeq(l, r) == fancy.rangeq(l, r));
        }
    }
}
























