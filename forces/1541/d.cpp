#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
using namespace std;

using ll = long long;

struct frac {
    ll n;
    ll d;
    frac(ll n, ll d) : n(n), d(d) {}
};

frac operator / (frac f, int i) {
    return frac(f.n, f.d * i);
}

void bfs(vector<bool> &seen, vector<vector<int>> &es, vector<int> &parents,
         vector<vector<int>> &bfses, vector<frac> &prob, int parent, int cur) {
    if (seen[cur]) return;
    seen[cur] = true;
    parents[cur] = parent;
    bfses[parent].push_back(cur);

    for (auto c : es[cur]) {
        bfs(seen, es, parents, bfses, prob, cur, c);
    }
}

void spreadprob(vector<vector<int>> &bfses, vector<frac> &prob, int r) {
    const int n = bfses[r].size();
    for(auto c : bfses[r]) {
        prob[c] = prob[r] / n;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> es(n);
    for (int i = 0; i < n - 1; ++i) {
        int p, c;
        cin >> p >> c;
        es[p].push_back(c);
        es[c].push_back(p);
    }
    // root
    for (int r = 0; r < n; ++r) {
        vector<int> parents(n);
        vector<vector<int>> bfses(n);
        vector<frac> prob(n);
        vector<bool> seen(n, false);

        bfs(seen, es, parents, bfses, prob, r, r);
        prob[r] = frac(1, 1);
        spreadprob(bfses, prob, r);
    }

    return 0;
}

