#include<iostream>
#include<fstream>
#include<assert.h>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

int pow2(int x) { return x == 0 ? 1 : 2 * pow2(x-1); }

template<typename V>
struct Plus {
  using T = V;
  using U = V;
  static const V id = 0;
  static const U uid = 0;

  // query is combine(a_i, a_2, ... a_j)
  static V combine(V v1, V v2) { return v1 + v2; }
  static U updcombine(U u1, U u2) { return u1 + u2; }
  static V updact(V u, V v, int h) { 
    return v + u*(pow2(h));
  }
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
  vector<typename Op::U> ls;
  int n;

  // [ql, qr] refer to 
  typename Op::T rangeQ_(int ql, int qr, int nl, int nix, int nr, int h) {
    assert(ql >= n); assert(qr <= 2*n-1);
    assert(nix >= 1); assert(nix <= 2*n-1);

    if (nr < ql || qr < nl) { return Op::id;  }

    // if [ql, qr] is empty:
    if (ql <= nl && nr <= qr) { return vs[nix]; }

    int mid = (nl + nr)/2;
    rangeU_(nl, nr, ls[nix], 
        nl, nix*2, mid, h-1);
    rangeU_(nl, nr, ls[nix], 
        mid+1, nix*2+1, nr, h-1);
    typename Op::T rangel = rangeQ_(ql, qr, nl, nix*2, mid, h-1);
    typename Op::T ranger = rangeQ_(ql, qr, mid+1, nix*2+1, nr, h-1);
    return Op::combine(rangel, ranger);
  }

  void rangeU_(int ql, int qr, typename Op::U upd, 
      int nl, int nix, int nr, int h) {
    assert(ql >= n); assert(qr <= 2*n-1);
    assert(nix >= 1); assert(nix <= 2*n-1);


    if (ql <= nl && nr <= qr) { 
      ls[nix] = Op::updcombine(ls[nix], upd);
      vs[nix] = Op::updact(upd, vs[nix], h);
      return;
    }

    if (nr < ql || qr < nl) { return; }

    if (nix*2 < vs.size())
    ls[nix*2] = Op::updcombine(ls[nix*2], ls[nix]);
    
    if (nix*2+1 < vs.size())
    ls[nix*2+1] = Op::updcombine(ls[nix*2+1], ls[nix]);

    ls[nix] = Op::uid;
    int mid = (nl + nr)/2;
    rangeU_(ql, qr, upd, nl, nix*2, mid,h-1);
    rangeU_(ql, qr, upd, mid+1, nix*2+1, nr,h-1);
  }

public:
  template<typename T>
  friend ostream& operator<<(ostream&, const Segtree<T>&);
  int H;

  Segtree(int n):n(n), vs(2*n), ls(2*n), H(ceil(log2(n))) {}
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
    for (int i = n-1; i >= 1; i--) { ls[i] = Op::uid; }
  }

  // update value at location ix as:
  //   a[ix] = combine(a[ix], v)

  // return combine(a[ql,..., qr]) (CLOSED INTERVAL)
  typename Op::T rangeQ(int ql, int qr) { 
    return rangeQ_(ql, qr, n, 1, 2*n-1, H);
  }

  void rangeU(int ql, int qr, typename Op::U upd) {
    rangeU_(ql, qr, upd, n, 1, 2*n-1, H);
  }

  void pointU(int ix, typename Op::U upd) {
    assert(ix >= n); assert(ix < 2*n);
    rangeU(ix, ix, upd);
  }


};

template<typename T>
ostream& operator << (ostream &o, const Segtree<T> &st) {
  o << "(H:" << st.H <<")";
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

  cout << "s[8:8] := " << s.rangeQ(8, 8) << "\n";
  cout << "s[9:9] := " << s.rangeQ(9, 9) << "\n";
  cout << "s[10:10] := " << s.rangeQ(10, 10) << "\n";
  cout << "s[11:11] := " << s.rangeQ(11, 11) << "\n";
  cout << "s[12:12] := " << s.rangeQ(12, 12) << "\n";
  cout << "s[9:9] := " << s.rangeQ(9, 9) << "\n";
  cout << "s[8:9] := " << s.rangeQ(8, 9) << "\n";
  cout << "s[8:10] := " << s.rangeQ(8, 10) << "\n";
  cout << "s[8:11] := " << s.rangeQ(8, 11) << "\n";


  cout << "=====\n";

  cout << "s[8:15] := " << s.rangeQ(8, 15) << "\n";
  cout << "s[8:11] := " << s.rangeQ(8, 11) << "\n";
  cout << s << "\n";
  cout << "s[8:15] :+= 1"; s.rangeU(8, 15, 1);
  cout << s << "\n";
  cout << "s[8:15] := " << s.rangeQ(8, 15) << "\n";
  cout << s << "\n";
  cout << "s[8:11] := " << s.rangeQ(8, 11) << "\n";
  cout << s << "\n";
  cout << "s[8:8] := " << s.rangeQ(8, 8) << "\n";
  cout << "s[9:9] := " << s.rangeQ(9, 9) << "\n";
  cout << "s[10:10] := " << s.rangeQ(10, 10) << "\n";
  cout << "s[11:11] := " << s.rangeQ(11, 11) << "\n";
  cout << "s[12:12] := " << s.rangeQ(12, 12) << "\n";
  cout << "s[13:13] := " << s.rangeQ(13, 13) << "\n";
  cout << "s[14:14] := " << s.rangeQ(14, 14) << "\n";
  cout << "s[15:15] := " << s.rangeQ(15, 15) << "\n";
  cout << s << "\n";
  return 0;
}
