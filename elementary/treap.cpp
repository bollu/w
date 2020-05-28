#include <map>
#include <iostream>
#include <algorithm>
#include <functional>
#include <assert.h>
using namespace std;

template<typename K, typename V, int INFTY=100000000> struct treap {
    // pr = priority
    struct node {
        K k; V v; int pr; node *l= nullptr, *r=nullptr; 
        node(K k, V v, int pr): k(k), v(v), pr(pr) {};
    };
    node *root = nullptr;

    int count() const;
    node *lookup(const K k) const { return lookup(k, root); } 
    node *lookup(const K k, node *root) const {
        if (!root) { return nullptr; }
        else if (root->k == k) { return root; }
        else { return lookup(k, k < root->k ? root->l : root->r); }
    }

    // *destructively* merge nodes p and q
    node *merge(node *&p, node *&q) {
        if (!p || !q) { return p ? p : q; }
        // p is always parent (closer to root on min-heap)
        if (p->pr > q->pr) { swap(p, q); }

        if (q->k < p->k) { p->l = merge(p->l, q); }
        else { p->r = merge(p->r, q); }

        return p;
    }

    void erase(K k) { erase(k, root); }
    void erase(K k, node *&root) {
        if (!root) { return; }
        if (root->k == k) { root = merge(root->l, root->r); }
        else { erase(k, k < root->k  ? root->l : root->r); }
    }

    void insert(K k, V v) { 
        insert(new node(k, v, rand() % 10), root);
    }

    void insert(node *n, node *&root) {
        if (!root) { root = n; return; }
        if (root->k == n->k) { root->v = n->v; return;  }

        if (n->pr < root->pr) {
            //   INCORRECT:
            //   n    
            //   k:8 ----\
            //        root
            //      /--k:10--\
            //     k:4      k:16
            //       \
            //       k:9
            // ================
            //   CORRECT:
            //      n    
            //  /---8---------\
            // k:4           root
            //          /----10----\
            //         k:9         k:16

        }
        else { insert(n, n->k < root->k ? root->l : root->r); }
    }

    void check(node *n) {
        if (n == nullptr) return;
        if (n->l) { assert(n->pr <= n->l->pr); assert(n->l->k < n->k); check(n->l); } 
        if (n->r) { assert(n->pr <= n->r->pr); assert(n->r->k >= n->k); check(n->r); } 
    }

    void print() { print(root, 0); }
    void print(node *n, int depth) {
        if (!n) return;
        // for(int i = 0; i < depth; ++i) cout << ' ';
        cout << "[pr(" << n->pr << ") k(" << n->k << ") v(" << n->v <<")]\n";
        if(n->l) {
            for(int i = 0; i < depth+4; ++i) cout << ' '; cout << "l:";
            print(n->l, depth+4);
        }
        if(n->r) {
            for(int i = 0; i < depth+4; ++i) cout << ' '; cout << "r:";
            print(n->r, depth+4);
        }
    }
};

int main() { 
    treap<int, int> tr;
    tr.check(tr.root);
    srand(0);
    map<int, int> m;
    const int KEYSPACE = 10;

    for(int i = 0; i < 10; ++i) {
        int k = rand() % KEYSPACE;
        int v = rand() % 100;
        cout << "inserting map[" << k << "] = " << v << "\n";
        m[k] = v;
        tr.insert(k, v);
        tr.check(tr.root);
    }
    tr.print();

    for(int i = 0; i < 10000; ++i) {
        int v1 = m.count(i) == 0 ? -42 : m[i];
        auto it = tr.lookup(i);
        tr.check(tr.root);
        int v2 = it == nullptr ? -42 : it->v;
        cout << "lookup up (" << i << "): map[i] = " << v1
             << " | tr[i] = " << v2 << "\n";
        assert(v1 == v2);
    }


    for(int i = 0; i < 100; ++i) {
        int k = rand() % KEYSPACE;
        auto map_it = m.find(k);
        auto tr_it = tr.lookup(i);

        assert((map_it == m.end()) == (tr_it == nullptr));
        m.erase(map_it);
        tr.erase(k);
    }
    return 0;
}
