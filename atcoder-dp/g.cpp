#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;
using ll = long long;

const int MAX = 1e5;

set<int> parents[MAX];
set<int> children[MAX];
bool visited[MAX];
int dp[MAX];
int longest;

int main() {
  int n, m; cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int s, t; cin >> s >> t;
    s--; t--;
    parents[t].insert(s);
    children[s].insert(t);
  }

  queue<int> q;

  // multi source BFS from root nodes. (nodes with no parent).
  // roots of the DAG.
  for(int i = 0; i < n; ++i) {
    if (parents[i].size() == 0) {
      q.push(i);
    }
  }

  while(!q.empty()) {
    int cur = q.front();
    q.pop();

    if (visited[cur]) { continue; }
    visited[cur] = true;
    for (int next : children[cur]) {
      parents[next].erase(cur);

      // toposort, so only explore once all parents have been explored.
      if (parents[next].size() == 0) {
	q.push(next);
      }

      dp[next] = max<int>(dp[next], dp[cur]+1);
      longest = max<int>(longest, dp[next]);
    }
  }
  
  cout << longest << "\n";
  return 0;
}
