// https://cp-algorithms.com/data_structures/deleting_in_log_n.html
#include <assert.h>
#include <iostream>
#include <fstream>
#include<vector>
#include<stack>
#include<unordered_map>
#include<functional>
#include<utility>
#include<tuple>
#include<map>
using namespace std;

struct dsu_save {
    int v, rnkv, u, rnku;
    dsu_save() {}
    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

static const size_t N = (300005 / 2);
int p[N], rnk[N];

dsu_save op[N]; int opsp;

struct dsu_with_rollbacks {
    int comps;

    void init(int n)  {
        this->comps = n;
        for (int i = 0; i < n; i++) { p[i] = i; rnk[i] = 0; }
    }

    int find_set(int v) {
        return (v == p[v]) ? v : find_set(p[v]);
    }

    bool unite(int v, int u) {
        v = find_set(v);
        u = find_set(u);
        if (v == u) { return false; }
        comps--;
        if (rnk[v] > rnk[u]) { swap(v, u); }
        op[opsp++] = dsu_save(v, rnk[v], u, rnk[u]);
        p[v] = u;
        if (rnk[u] == rnk[v]) { rnk[u]++; }
        return true;
    }

    void rollback() {
        if (opsp == 0) { return; }
        dsu_save x = op[--opsp];
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
    }
};

struct query {
    int v, u;
    bool united;
    query(int _v, int _u) : v(_v), u(_u) {}
};

vector<query> t[N];
dsu_with_rollbacks dsu;

int ans[N];

struct QueryTree {
    int T;
    
    void init(int T, int n) { this->T = T; dsu.init(n); }

    void __add_to_tree(int v, int l, int r, int ul, int ur, query q) {
        if (ul > ur) { return; }
        if (l == ul && r == ur) {
            t[v].push_back(q);
            return;
        }
        int mid = (l + r) / 2;
        __add_to_tree(2 * v, l, mid, ul, min(ur, mid), q);
        __add_to_tree(2 * v + 1, mid + 1, r, max(ul, mid + 1), ur, q);
    }

    // [l, r] inclusive. in query, nodes are 0-indexed.
    void add_query(query q, int l, int r) {
        __add_to_tree(1, 0, T - 1, l, r, q);
    }

    void __dfs(int v, int l, int r) {
        for (query& q : t[v]) {
            q.united = dsu.unite(q.v, q.u);
        }

        if (l == r)
            ans[l] = dsu.comps;
        else {
            int mid = (l + r) / 2;
            __dfs(2 * v, l, mid);
            __dfs(2 * v + 1, mid + 1, r);
        }
        for (query q : t[v]) {
            if (q.united) { dsu.rollback(); }
        }
    }

    void solve() {
        __dfs(1, 0, T - 1);
    }
};


QueryTree qt;


map<pair<int, int>, int> started;
int questions[N]; int nquestions;
int n, k;

int main() {
    FILE *input = fopen("connect.in", "r");
    fscanf(input, "%d %d", &n, &k);
    qt.init(k+2, n);


    int timepoint = 1;
    for(int i = 0; i < k; ++i) {
        char c; fscanf(input, " %c", &c);
        if (c == '?') {
            timepoint++;
            questions[nquestions++] = timepoint;
            timepoint++;

        } else if (c == '+' || c == '-') {
            int u, v; fscanf(input, "%d %d", &u, &v); u -= 1; v -= 1;

            // printf("t: %d | %c %d %d\n", i, c, u, v);
            if (c == '+') { 
                started[make_pair(u, v)] = timepoint;
            }
            if (c == '-') { 
                auto it = started.find(make_pair(u, v));
                qt.add_query(query(u, v), it->second, timepoint);
                started.erase(it);
            }
        }
    }
    fclose(input);

    timepoint++;
    for(auto it : started) {
        qt.add_query(query(it.first.first, it.first.second), it.second, timepoint);
    }

    qt.solve();

    FILE *output = fopen("connect.out", "w");
    for(int i = 0; i < nquestions; ++i) {
         fprintf(output, "%d\n", ans[questions[i]]);
    }
    fclose(output);
    return 0;
}
