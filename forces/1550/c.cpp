#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;


struct Vertex {
  ll sum = 0;
  Vertex *l = nullptr;
  Vertex *r = nullptr;
  // closed interval: [lix, rix]
  ll lix, rix;

  Vertex *clone(Vertex *newl, Vertex *newr, ll newsum) const {
    Vertex *v = new Vertex(lix, rix);
    v->sum = newsum;
    v->l = newl;
    v->r = newr;
    return v;
  }

  Vertex(ll lix, ll rix) : lix(lix), rix(rix) {
    // leaf.
    // for closed interval, r-l counts number of "stops"
    // between numbers.
    // [00] -> 0
    // [0.1] -> 1
    // [0.1.2] -> 2
    // etc.
    assert(lix <= rix);
    if (lix == rix) {
      return;
    }

    // lix < rix
    // l0 r1 -> [l0 m0] | [m1 mr]
    // l0 1 r2
    // mix will become smaller because floor, so
    // lix <= mix < rix
    //
    //   mix < rix => [lix=?mix < rix]
    //   lix <= mix => [lix < mix+1 =?rix]
    ll mix = (lix + rix) / 2;
    l = new Vertex(lix, mix);
    r = new Vertex(mix + 1, rix);
    // sum = l->sum + r->sum;
  }

  Vertex *upd(ll ix, ll val) const {
    // cerr << "upd " << ix << " " << val << " | " << lix << " " << rix << "\n";

    assert(lix <= rix);
    if (lix == rix) {
      assert(lix == ix);
      return this->clone(this->l, this->r, this->sum + val);
    }

    ll mix = (lix + rix) / 2;
    Vertex *newl = this->l;
    Vertex *newr = this->r;
    if (ix <= mix) {
      newl = this->l->upd(ix, val);
    } else {
      newr = this->r->upd(ix, val);
    }
    return this->clone(newl, newr, newl->sum + newr->sum);
  }

  // [ql..qr]
  ll rangeq(ll ql, ll qr) const {
    assert(ql <= qr);
    assert(lix <= rix);
    // cerr << "rangeq " << ql << " " << qr << " | " << lix << " " << rix <<
    // "\n"; [ql..qr][lix...rix] [lix...rix][ql..qr]
    if (qr < lix || rix < ql) {
      return 0;
    }

    // [ql..[lix..rix]..qr]
    if (ql <= lix && rix <= qr) {
      return sum;
    }
    return l->rangeq(ql, qr) + r->rangeq(ql, qr);
  }
};

// [l..r] is good => in the range [l+1..r-1] there is no occurence of a value k
// with value vl and vr.
ll good(vector<const Vertex *> &roots, map<int, int> &compress, vector<int> &as,
        ll l, ll r) {
  assert(l >= 0);
  assert(r >= 0);
  assert(l < as.size());
  assert(r < as.size());
  assert(r >= l);
  if (l == r) {
    return true;
  }
  assert(r > l); // => r >= 1

  const ll vl = min(compress[as[l]], compress[as[r]]);
  const ll vr = max(compress[as[l]], compress[as[r]]);

  const ll nl = roots[l]->rangeq(vl, vr);
  const ll nr = roots[r - 1]->rangeq(vl, vr);
  bool out = (nr - nl) == 0;
  assert(nr >= nl);
  return out;
}

int main() {
  ios::sync_with_stdio(false);
  // sum[n] = 1 + 2 + ... n
  // sum[0] = 0;
  // for (int i = 1; i < LEN; ++i) {
  //   sum[i] = i + sum[i - 1];
  // }
  int t;
  cin >> t;
  while (t--) {
    ll n;
    cin >> n;
    vector<int> as(n);
    set<int> asvals;
    for (int i = 0; i < n; ++i) {
      cin >> as[i];
      asvals.insert(as[i]);
    }

    map<int, int> compress;
    for (int a : asvals) {
      compress[a] = compress.size();
    }

    // cerr << "***as: ";

    // for (int i = 0; i < n; ++i) {
    //   cerr << "[" << i << "]" << as[i] << " ";
    // }
    // cerr << "***\n";

    // --
    vector<const Vertex *> roots(n);
    roots[0] = new Vertex(0, compress.size());
    roots[0] = roots[0]->upd(compress[as[0]], 1);
    for (int i = 1; i < n; ++i) {
      roots[i] = roots[i - 1]->upd(compress[as[i]], 1);
    }

    ll tot = 0;
    for (int l = 0; l < as.size(); ++l) {
      for (int r = l; r < as.size(); ++r) {
        if (good(roots, compress, as, l, r)) {
          tot++;
        } else {
          break;
        }
      }
    }
    cout << tot << "\n";
  }
}
