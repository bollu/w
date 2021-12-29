#include <assert.h>
#include <algorithm>
#include <iomanip>
#include <ios>
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

void maxpot_floor(ll k, ll &nturns, ll &i) {
  i = 1;
  nturns = 1;
  while(i * 2 < k) { nturns++; i = i * 2; }
  assert(i <= k && i * 2 > k);
}


ll ceil_div(ll n, ll k) {
  return (n + (k - 1)) / k;
}

void solve() {
  ll n, k; cin >> n >> k;
  ll cur = 1;
  ll nspread = 1;
  ll nturns = 0;
  while(cur != n && nspread != k) {
    nturns++;
    cur += nspread;
    nspread = min(nspread * 2, k);
  }
  nturns += ceil_div(n - cur, nspread);
  cout << nturns << "\n";
}

int main() {
  int t; cin >> t;
  while(t--) { solve(); }
}

