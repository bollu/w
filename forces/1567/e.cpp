#include <algorithm>
#include <assert.h>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

const int N = 1e9 + 10;
int *base;

struct Node {
    ll basel, baser; // indexes of original array controlled by node
    ll p; // lenth on longest non-decreasing prefix
    ll s; // length of longest non-decreasing suffix
    ll count; // number of subsegments internal (not in prefix & suffix)
    bool full; // if the entire array is <. Can be check by p == baser - basel + 1.
};

ostream & operator <<(ostream &o, const Node &n) {
    return o << "[l:" << n.basel << " r:" << n.baser << 
        " p:" << n.p << " s:" << n.s << " count:" << n.count << " full:" << (n.full ? "t" : "f") << "]";
}

ll f(ll n) {
    return (1LL*n*1LL*(n+1))/2;
}


// NON-decreasing: 1 1 1 2 3 4 a[i] <= a[i+1]
void merge(Node *l, Node *r, Node *out) {
    assert(l->baser + 1 == r->basel);
    out->basel = l->basel;
    out->baser = r->baser;
    out->count = 0;
    out->p = out->s = 0;
    out->full = false;

    if (l->full && r-> full) {
        if (base[l->baser] <= base[r->basel]) {
            // L<<<<<<<<<<<<<<<<<L<R<<<<<<<<<<<<<<<<<R
            out->count = 0;
            out->p = l->p + r->p;
            out->s = r->s + l->s;
            out->full = true;
        } else {
            // L<<<<<<<<<<<<<<<<<L>R<<<<<<<<<<<<<<<<<R
            out->count = 0;
            out->p = l->p;
            out->s =  r->s;
            out->full = false;
        }
    }
    else if (r->full) {
        assert(!l->full);
        if (base[l->baser] <= base[r->basel]) {
            // L<<<<--<<<--<<<L<R<<<<<<<<<<<<<<<<R
            out->count = l->count;
            out->p = l->p;
            out->s = l->s + r->s;
            out->full = false;
        } else {
            // L<<<<---<<<---<<<L>R<<<<<<<<<<<<<<<<R
            out->count = l->count + f(l->s);
            out->p = l->p;
            out->s = r->s;
            out->full = false;
        }
    }
    else if (l->full) {
        assert(!r->full);
        if (base[l->baser] <= base[r->basel]) {
            // L<<<<<<<<L<R<<<---<<<<--<<<<<<<<<R
            out->count = r->count;
            out->p = l->p + r->p;
            out->s = r->s;
            out->full = false;
        } else{
            // L<<<<<<<<L>R<<<---<<<<--<<<<<<<<<R
            out->count = f(r->p) + r->count;
            out->p = l->p;
            out->s = r->s;
            out->full = false;
        }
    } else { 
        assert(!l->full);
        assert(!r->full);
        if (base[l->baser] <= base[r->basel]) {
            // L<<<----<<<----<<<L<R<<<---<<<<--<<<<<<<<<R
            out->count = l->count + r->count + f(l->s + r->p);
            out->p = l->p;
            out->s = r->s;
            out->full = false;
        } else {
            // L<<<----<<<----<<<L>R<<<---<<<<--<<<<<<<<<R
            out->count = l->count + r->count + f(l->s) + f(r->p);
            out->p = l->p;
            out->s = r->s;
            out->full = false;
        }
    }
}

Node *tree;

// [basel, baser]: range of indexes of array controlled by node.
void build(int nodeix, int basel, int baser) {
    Node *cur = tree + nodeix;
    // cerr << "[" << basel << " " << baser << "]" << endl;
    assert(basel <= baser);
    if (basel == baser) {
        tree[nodeix].p = 1;
        tree[nodeix].s = 1;
        tree[nodeix].full = true;
        tree[nodeix].count = 0;
        tree[nodeix].basel = basel;
        tree[nodeix].baser = basel;
        return;
    } else {
        int basem = (basel + baser)/2;
        build(nodeix*2, basel, basem);
        build(nodeix*2+1, basem+1, baser);
        Node *cl = tree + nodeix*2;
        Node *cr = tree + nodeix*2+1;
        merge(cl, cr, cur);
    }
}

void upd(int qix, int qval, int nodeix, int basel, int baser) {
    Node *cur = tree + nodeix;
    if (basel == baser) {
        assert(basel == qix);
        base[qix] = qval;
    } else {
        int basem = (basel + baser)/2;
        if (qix <= basem) {
            upd(qix, qval, nodeix*2, basel, basem);
        } else {
            upd(qix, qval, nodeix*2+1, basem+1, baser);
        }
        merge(tree + nodeix*2, tree + nodeix*2+1, cur);
    }
}

void query(int ql, int qr, int nodeix, int basel, int baser, ll &out, ll &sufflen) {
    // [basel---baser] [ql---qr] [basel---baser]
    if (baser < ql || qr < basel) { 
        // out += f(sufflen); sufflen = 0;
        return;
    } 
    // [ql---[basel---baser]--qr] 
    else if (ql <= basel && baser <= qr) {
        // cerr << "\t\t" << tree[nodeix] << " | out:" << out << " sufflen: " << sufflen << "\n";
        if (tree[nodeix].full) {
            // extends suffix.
            if (basel == 0 || (basel > 0 && base[basel-1] <= base[basel])) {
                //<<<<<;<;[basel<<<<<<<<]
                sufflen += tree[nodeix].s;
            } else {
                //<<<<<;>;[basel<<<<<<<<]
                // close previous suffix, open new suffix.
                out += f(sufflen);
                sufflen = tree[nodeix].s;
            }
        } else {
            // node is not entirely of the form [<<<<<<<<<<<<<]
            // <<<<<<;?;<<<<---<<<<---<<<<<
            if (basel == 0 || (basel > 0 && base[basel-1] <= base[basel])) {
                // <<<<<<;<;<<<<---<<<<---<<<<<
                out += f(sufflen + tree[nodeix].p) + tree[nodeix].count;
                sufflen = tree[nodeix].s;
            } else {
                // <<<<<<;>;<<<<---<<<<---<<<<<
                out += f(sufflen) + f(tree[nodeix].p) + tree[nodeix].count;
                sufflen = tree[nodeix].s;
            }
        }
    } else {
        int basem = (basel + baser)/2;
        query(ql, qr, nodeix*2, basel, basem, out, sufflen);
        query(ql, qr, nodeix*2+1, basem+1, baser, out, sufflen);
    }
}

void queryfold(int ql, int qr, int nodeix, int basel, int baser, Node &nl) {
    // [basel---baser] [ql---qr] [basel---baser]
    if (baser < ql || qr < basel) { 
        // out += f(sufflen); sufflen = 0;
        return;
    }

    // [ql---[basel---baser]--qr] 
    else if (ql <= basel && baser <= qr) {
        Node nr = tree[nodeix];
        if (nl.basel == 0) { nl = nr; }
        else {
            Node merged;
            merge(&nl, &nr, &merged);
            nl = merged;
        }

    } else {
        int basem = (basel + baser)/2;
        queryfold(ql, qr, nodeix*2, basel, basem, nl);
        queryfold(ql, qr, nodeix*2+1, basem+1, baser, nl);
    }
}

int main() {
  ios::sync_with_stdio(false);
  int n, q; 
  cin >> n >> q;
  base = (int *)calloc(n+1, sizeof(int));
  for(int i = 1; i <= n; ++i) { cin >> base[i]; }
  tree = (Node*)calloc(n*4, sizeof(Node));
  build(1, 1, n);
  for(int i = 0; i < q; ++i) {
      int type; cin >> type;
      if (type == 1) {
          int ix, val; cin >> ix >> val;
          upd(ix, val, 1, 1, n);
      } else {
          int l, r; cin >> l >> r;
          // cerr << "\t-before q(" << l << ", " << r << "): "; for(int i = l; i <= r; ++i) { cerr << base[i] << " "; } cerr << "\n";
          Node left {  .basel = 0, .baser = 0, .p = 0, .s = 0 , .count = 0, .full = true }; 
          queryfold(l, r, 1, 1, n, left);
          // cerr << "\t\tout: " << out << " |sufflen: " << sufflen << "\n";
          ll out = 0; 
          if (left.full) {
              out = f(left.p);
          } else {
              out = left.count + f(left.p) + f(left.s);
          }

          cout << out << "\n";
      }
  }
}
