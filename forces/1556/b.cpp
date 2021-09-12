#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <new>
#include <ostream>
#include <queue>
#include <set>
#include <stack>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;


ll cabs(ll v) {
  return v >= 0 ? v : -v;
}

template<typename T>
void printarray(vector<T> &xs) {
  cout << "[";
  for(int i = 0; i < xs.size(); ++i) {
    cout << xs[i] << " ";
  }
  cout << "]"; return;
}

int solvecase(int pmore, vector<int> as) {
  int tot = 0;
  int n = as.size();
    for(int i = 0; i < n; i += 1) {
     int pcur = i % 2 == 0 ? pmore : 1 - pmore;

     int j = i + 1;
     if (as[i] == pcur) { continue; }
      while(j < n) {
          if (as[j] == pcur) { break; }
          else { j++; }
      }
      if (j >= n) { return -1; }
      assert(j < n);
      assert(as[j] == pcur);
      tot += cabs(j-i);
      // cout << "swapping " << i << " " << j << "\n";
      // cout << "\tarray: "; printarray(as); cout << "\n";
      swap(as[i], as[j]);
      // cout << "\t(after): "; printarray(as); cout << "\n";

      // j++;
  }
  return tot;

}

void solve() {
  int n; cin >> n;
  vector<int> as(n);
  int nodd = 0, neven = 0;
  for(int i = 0; i < n; ++i) {
    cin >> as[i];
    as[i] %= 2;
    if (as[i] == 0) {
      neven++;
    } else {
      nodd++;
    }
  }
  // cout << "neven: " << neven << " | nodd: " << nodd << " cabs: " << cabs(neven - nodd) << "\n";
  // if (cabs(neven - nodd) > 1) { cout << "-1\n"; return; }

  int pmore;
  if (neven > nodd) {
    pmore = 0;
    cout << solvecase(pmore, as) << "\n";
    return;
  } else if (neven < nodd) {
    pmore = 1;
    cout << solvecase(pmore, as) << "\n";
    return;
  }   else {
    assert(neven == nodd);
    int tot = solvecase(pmore, as);
    tot = min<int>(tot, solvecase(1 - pmore,as));
    cout << tot << "\n";
    return;
  }
  // cout << "pmore: " << pmore << "\n" << std::endl;
  int tot = 0;
  // int j = 1;
  for(int i = 0; i < n; i += 1) {
     int pcur = i % 2 == 0 ? pmore : 1 - pmore;

     int j = i + 1;
     if (as[i] == pcur) { continue; }
      while(j < n) {
          if (as[j] == pcur) { break; }
          else { j++; }
      }
      assert(j < n);
      assert(as[j] == pcur);
      tot += cabs(j-i);
      // cout << "swapping " << i << " " << j << "\n";
      // cout << "\tarray: "; printarray(as); cout << "\n";
      swap(as[i], as[j]);
      // cout << "\t(after): "; printarray(as); cout << "\n";

      // j++;
  }

  // j = 2;
  // for(int i = 1; i < n; i += 2) {
  //     if (as[i] != pmore) { continue; }
  //     while(j < n) {
  //       if (as[j] != pmore) { break; }
  //       else { j++; }
  //     }
  //     assert(j < n);
  //     assert(as[j] != pmore);
  //     tot += cabs(j-i);
      
  //     cout << "swapping " << i << " " << j << "\n";
  //     cout << "\tarray: "; printarray(as); cout << "\n";

  //     swap(as[i], as[j]);
  //     cout << "\t(after): "; printarray(as); cout << "\n";

  //     j++;

  // }
  // cout << "tot:" << tot << "\n";
  cout << tot << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--) {
      solve();
    }

}

