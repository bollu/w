#include <iostream>
using namespace std;


static const int N = 2 * 1e5 + 10;
vector<int> es[N];
vector<int> parents[N];
vector<int> depths[N];
void dfs(int v, int parent, int depth) {

}

int main() {
    int n, m; cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a>> b;
        es[a].push_back(b);
        es[b].push_back(a);
    }
}
