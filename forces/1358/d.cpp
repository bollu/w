// https://codeforces.com/contest/1358/problem/D
#include <iostream>
#include <algorithm>
#include <vector>

#define int long long

using namespace std;

signed main() {
  int n, len;
  cin >> n >> len;
  vector<int> A(2 * n);
  for (int i = 0; i < n; i++) {
    cin >> A[i];
    A[n + i] = A[i];
  }
  n *= 2;
  
  // B: cumulative # of days
  // C: cumulative # of holidays
  vector<int> B = {0}, C = {0};
  for (int i = 0; i < n; i++) 
    B.push_back(B.back() + A[i]);
  for (int i = 0; i < n; i++) 
    C.push_back(C.back() + (A[i] * (A[i] + 1)) / 2);
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (B[i + 1] >= len) {
      // find the index which has value 
      // int z = upper_bound(B.begin(), B.end(), B[i + 1] - len) - B.begin();
      // find index `ix` which has value **strictly greater** than `B[i+1]-len`.
      int ix = upper_bound(B.begin(), B.end(), B[i + 1] - len) - B.begin();
      int cnt = C[i + 1] - C[ix];
      int days = B[i + 1] - B[ix];
      int too = len - days;
      cnt += ((A[ix - 1] * (A[ix - 1] + 1)) / 2);
      cnt -= (((A[ix - 1] - too) * (A[z - 1] - too + 1)) / 2);
      ans = max(ans, cnt);
    }
  }
  cout << ans;
}
