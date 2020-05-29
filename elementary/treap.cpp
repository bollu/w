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

    node *lookup(const K k) const { return lookup(k, root); } 
    node *lookup(const K k, node *root) const {
        if (!root) { return nullptr; }
        else if (root->k == k) { return root; }
        else { return lookup(k, k < root->k ? root->l : root->r); }
    }

    // *destructively* merge nodes p and q
    node *merge(node *&p, node *&q) const {
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



    // how does this work?
    pair<node *, node*> split(K k, node *cur) const {
        if (!cur) { return {nullptr, nullptr}; }
        else if (k < cur->k) {
            // cur->l   k   cur      cur->r
            //
            //
            // (lsplit.first k lsplit.second) cur  cur->r
            auto lsplit = split(k, cur->l);
            cur->l = lsplit.second;
            return {lsplit.first, cur};
        } else {
            auto rsplit = split(k, cur->r);
            cur->r = rsplit.first;
            return {cur, rsplit.second}; 
        }
    }

    void insert(K k, V v) { 
        if (node *n = lookup(k)) { n->v = v; return; }
        insert(new node(k, v, rand() % 1000), root);
    }

    void insert(node *n, node *&cur) const {
        if (!cur) { cur = n; return; }
        else if (cur->pr < n->pr) { insert(n, n->k < cur->k ? cur->l : cur->r); }
        else { tie(n->l, n->r) = split(n->k, cur); cur = n; }
    }

    void check(node *n) const {
        if (n == nullptr) return;
        else if (n->l) { assert(n->pr <= n->l->pr); assert(n->l->k < n->k); check(n->l); } 
        if (n->r) { assert(n->pr <= n->r->pr); assert(n->r->k >= n->k); check(n->r); } 
    }

    void print() const { print(root, 0); }
    void print(node *n, int depth) const {
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

    int size() const { return size(root); }
    int size(node *n) const { if (!n) return 0; return 1 + size(n->l) + size(n->r); }
};

int main() { 
    treap<int, int> tr;
    tr.check(tr.root);
    srand(0);
    map<int, int> m;
    const int KEYSPACE = 100;

    for(int i = 0; i < 10000; ++i) {
        int k = rand() % KEYSPACE;
        int v = rand() % 100;
        cout << "inserting map[" << k << "] = " << v << "\n";
        m[k] = v;
        tr.insert(k, v);
        tr.print();
        tr.check(tr.root);
        assert(m.size() == tr.size());
    }
    tr.print();

    for(auto it : m) {
        cout << "looking up: " << it.first << ": " << it.second << "\n";
        auto trit = tr.lookup(it.first);
        assert(trit != nullptr);
        assert(it.second == trit->v); 
    }

    for(int i = 0; i < 10000; ++i) {
        const int k = rand() % KEYSPACE;
        const int v1 = m.count(k) == 0 ? -42 : m[k];

        const auto it = tr.lookup(k);
        tr.check(tr.root);
        int v2 = it == nullptr ? -42 : it->v;
        cout << "lookup up (" << k << "): map[i] = " << v1
             << " | tr[i] = " << v2 << "\n";
        tr.print();
        assert(v1 == v2);
    }


    for(int i = 0; i < 10000; ++i) {
        int k = rand() % KEYSPACE;
        auto map_it = m.find(k);
        auto tr_it = tr.lookup(k);

        assert((map_it == m.end()) == (tr_it == nullptr));
        if (map_it == m.end()) { continue; }
        m.erase(map_it);
        tr.erase(k);
    }
    return 0;
}
