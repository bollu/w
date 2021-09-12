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

struct state {
  ll nl = 0;
  ll nr = 0;
};
const ll N = 1000 + 1;

state dp[N][N]; // dp[len][ix]

pair<state, ll> merge(state l, state r) {
  ll ncancel = min<int>(l.nr, r.nl);
  state out;
  out.nl = l.nl + r.nl - ncancel;
  out.nr = l.nr + r.nr - ncancel;
  return {out, ncancel};
}

void print_state(state &s) {
  cout << s.nl << ")"
       << "(" << s.nr;
}

void solve() {
  ll tot = 0;
  int n;
  cin >> n;
  stack<state> ss;
  for (int i = 0; i < n; ++i) {
    state cur;
    if (i % 2 == 0) {
      cin >> cur.nr;
    } else {
      cin >> cur.nl;
    }
    while (ss.size()) {
      state top = ss.top();
      state smerge;
      ll nmerge;
      tie(smerge, nmerge) = merge(top, cur);
      if (nmerge == 0) {
        break;
      } else {
        ss.pop();
        cur = smerge;
        tot += nmerge;
      }
    }
    ss.push(cur);
  }

  cout << tot << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  solve();
}
