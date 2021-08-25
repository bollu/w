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

state f(ll l, ll r, int sign);
state f_(ll l, ll r, int sign) {
  if (l == r) {
    return state(l, r, sign*as[l]);
  } else {
    state sl = f(l+1, r, -sign);
    sl.delta += sign*as[l];
    state sr = f(l, r-1, -sign);
    sr.delta += sign*as[r];
    
    if (sl.delta * sign > sr.delta * sign) {
      return sl;
    } else {
      return sr;
    }
  }
}

map<tuple<int, int, int>, state> cache;
state f(ll l, ll r, int sign) {
  auto it = cache.find({l, r, sign});
  if (it != cache.end()) {
    return it->second;
  }
  state s = f_(l, r, sign);
  cache[{l, r, sign}] = s;
  return s;
}

int main() {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> as[i];
  }
  state out = f(0, n-1, 1);
  cout << (out.delta) << "\n";
  return 0;
}
