#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;
using ll = long long;
using rr = double;

const int N = 3000 + 3;
ll n;
ll as[N];

struct state {
  ll l;
  ll r;
  ll delta;
  state() {}
  state(ll l, ll r, ll delta)
    : l(l), r(r), delta(delta) {}
};

state t(ll l, ll r);
state j(ll l, ll r);

// maximiser plays first.
state j_(ll l, ll r) {
  if (l == r) {
    return state(l, r, -as[l]);
  } else {
    state takel = t(l + 1, r);
    takel.delta -= as[l];
    state taker = t(l, r - 1);
    taker.delta -= as[r];
    if (takel.delta < taker.delta) {
      return takel;
    } else {
      return taker;
    }
  }
}

map<pair<int, int>, state> jcache;
state j(ll l, ll r) {
  auto it = jcache.find({l, r});
  if (it == jcache.end()) {
    state s = j_(l, r);
    jcache[{l, r}] = s;
    return s;
  } else {
    return it->second;
  }
}

state t_(ll l, ll r) {
  if (l == r) {
    return state(l, r, as[l]);
  } else {
    state takel = j(l + 1, r);
    takel.delta += as[l];
    state taker = j(l, r - 1);
    taker.delta += as[r];
    if (takel.delta > taker.delta) {
      return takel;
    } else {
      return taker;
    }
  }
}
map<pair<int, int>, state> tcache;
state t(ll l, ll r) {
  auto it = tcache.find({l, r});
  if (it == tcache.end()) {
    state s = t_(l, r);
    tcache[{l, r}] = s;
    return s;
  } else {
    return it->second;
  }
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> as[i];
  }
  state out = t(0, n-1);
  cout << (out.delta) << "\n";
  return 0;
}
