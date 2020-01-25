#include<iostream>
#include<fstream>
#include<assert.h>
#include<string>
#include<vector>
using namespace std;

template<typename V>
struct Plus {
  using T = V;
  static const V id = 0;
  // query is combine(a_i, a_2, ... a_j)
  static V combine(V v1, V v2) { return v1 + v2; }
};

// template specialization
template<>
struct Plus<string> {
  using T = string;
  static const string id;
  static string combine(string v1, string v2) { return v1 + v2; }
};

template <typename V>
struct Star {
  using T = V;
  static const V id = 1;
  static V combine(V v1, V v2) { return v1 * v2; }
};

template<typename Op> 
class Segtree {
private:
  vector<typename Op::T> vs;
  vector<typename Op::L> ls;
  int n;

  // [ql, qr] refer to 
  typename Op::T rangeQ_(int ql, int qr, int nl, int nix, int nr) {
    assert(ql >= n); assert(qr < 2*n-1);
    assert(nix >= 1); assert(nix <= 2*n-1);
    // if [ql, qr] is empty:
    if (ql <= nl && nr <= qr) { return vs[nl]; }
    if (nr < ql || qr < nl) { return Op::id;  }

    int mid = (nl + nr)/2;
    typename Op::T rangel = rangeQ_(ql, qr, nl, nix*2, mid);
    typename Op::T ranger = rangeQ_(ql, qr, mid+1, nix*2, nr);
    return Op::combine(rangel, ranger);
  }

public:
  template<typename T>
  friend ostream& operator<<(ostream&, const Segtree<T>&);


  Segtree(int n):n(n), vs(2*n), ls(n) {}
  // ix ∈ [n..2n).
  // DO NOT UPDATE AT THIS STAGE.
  // call build() after to init segtree to valid state.
  // Otherwise, UB.
  void set_(int ix, typename Op::T v) {
    assert(ix >= n); assert(ix < 2*n);
    vs[ix] = v;
  }

  // builds the segtree in O(n) time.
  void build() {
    for (int i = n-1; i >= 1; i--) {
      //vs[i] = vs[i<<1].combine(vs[i<<1|1]);
      const typename Op::T l = vs[i*2], r = vs[i*2+1];
      vs[i] = Op::combine(l, r);
    }
  }

  // update value at location ix as:
  //   a[ix] = combine(a[ix], v)
  void pointU(int ix, typename Op::T v) {
    assert(ix >= n); assert(ix < 2*n); 
    while (ix >= 1) { vs[ix] = Op::combine(vs[ix], v); ix /= 2; }
  }

  // return combine(a[ql,..., qr]) (CLOSED INTERVAL)
  typename Op::T rangeQ(int ql, int qr) { 
    return rangeQ_(ql, qr, n, 1, 2*n-1);
  }


};

template<typename T>
ostream& operator << (ostream &o, const Segtree<T> &st) {
  for(int i = 1; i < st.vs.size(); ++i) {
    o << st.vs[i] << " ";
  }
  return o;
}

int main() {
  static const int N = 8;
  Segtree<Plus<int> > s(N);
  cout << s << "\n";
  for (int i = 8; i < 2*8; ++i) {
    s.set_(i, i-N);
  }
  cout << s << "\n";
  s.build();
  cout << s << "\n";

  cout << "s[8:10] := " << s.rangeQ(8, 10) << "\n";
  return 0;
}
