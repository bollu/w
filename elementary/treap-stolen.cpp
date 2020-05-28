#include <map>
#include <iostream>
#include <algorithm>
#include <functional>
#include <assert.h>
using namespace std;

struct item {
    int key, priority, value;
    item * l, * r;
    item() { }
    item (int key, int value) : 
        key(key), value(value), priority(rand()), l(NULL), r(NULL) {}
    item (int key, int value, int priority) : 
        key(key), priority(priority), l(NULL), r(NULL) { }
};
typedef item * pitem;

item *lookup(pitem t, const int k) {
    if (t == nullptr) { return nullptr; }
    else if (k == t->key) { return t; }
    else if (k < t->key) { return lookup(t->l, k); }
    else { return lookup(t->r, k); };
}

// split the tree at t into l and r
void split (pitem t, int key, pitem & l, pitem & r) {
    if (!t) {
        l = r = NULL;
    } else if (key < t->key) {
        //          t
        //  (key,l)     r
        //  ======= 
        //  FINAL L |   FINAL R
        //          |     t -----
        //          |    /       \
        //split->l  | split->r   r
        //
        // ==========================================
        //                a  b       c
        split (t->l, key, l, t->l),  r = t;
    } else {

        //                    t
        //       l           |||   (key, r)
        //                   |||
        //     t---*         |||       FINAL R
        //    /    \         |||
        //   l    split->l   |||        split->r
        //
        // ==========================================
        //                b     a    c
        split (t->r, key, t->r, r),  l = t;
    }
}

void insert (pitem & t, pitem it) {
    if (!t) {
        t = it;
    } else if (it->priority > t->priority) {
        split (t, it->key, it->l, it->r),  t = it;
    } else {
        if (it->key == t->key) {
            t->value = it->value; // copy value, don't create new node?
        } else {
            insert (it->key < t->key ? t->l : t->r, it);
        }
    }
}

// Unused
// replace (t) with the merge of (p) and (q)
void merge (pitem & t, pitem p, pitem q) {
    if (!p || !q) {
        t = p ? p : q;
    } else if (p->priority > q->priority) {
        // p.priority     ||>||             q.priority
        // /        \     ||>||             /        \
        // l        r     ||>||            l         r
        //
        //
        // ==============================================
        //    p --
        //   /    \
        //  p.l   [p.r <- merge(p.r, q)]
        //
        merge (p->r, p->r, q); t = p;
    } else {
        // p.priority     ||<||             q.priority
        // /        \     ||<||             /        \
        //p.l       p.r   ||<||           q.l       q.r
        //
        //
        // ==============================================
        //    q ----------
        //   /             \
        // [q.l <- p + q.l]  q..r
        //
        merge (q->l, p, q->l); t = q;
    }
}

// merge used for erase.
// erase = find node, replace it with left and right.
void erase (pitem & t, int key) {
    if (t->key == key) { merge (t, t->l, t->r); }q
    else { erase (key < t->key ? t->l : t->r, key); }
}

// unite v/s merge?
pitem unite (pitem l, pitem r) {
    if (!l || !r)  return l ? l : r;
    if (l->priority < r->priority)  swap (l, r);
    pitem lt, rt;
    split (r, l->key, lt, rt);
    l->l = unite (l->l, lt);
    l->r = unite (l->r, rt);
    return l;
}

int main() { 
    pitem treap = NULL;
    srand(0);
    map<int, int> m;

    for(int i = 0; i < 100; ++i) {
        int k = rand() % 10;
        int v = rand() % 100;
        cout << "inserting: map[" << k << "] = " << v << "\n";
        m[k] = v;
        insert(treap, new item(k, v));
    }

    for(int i = 0; i < 100; ++i) {
        int v1 = m.count(i) == 0 ? 42 : m[i];
        item *it = lookup(treap, i);
        int v2 = it == nullptr ? 42 : it->value;
        assert(v1 == v2);
    }
    return 0;
}
