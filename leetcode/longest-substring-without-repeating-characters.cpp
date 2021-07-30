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

const ll INFTY = 100000000000000;
void solve() {}

// a a f b b c c d d d e e

class Solution {
public:
  int lengthOfLongestSubstring(string s) {
    // b a c a
    //     ^ ^
    //     l  r
    //
    // [l, r] interval;
    int l = 0, r = 0;
    set<char> seen;
    int best = 0;
    for (int r = 0; r < s.size(); ++r) {
        while (seen.count(s[r])) {
          seen.erase(s[l]);
          l++;
        }
        seen.insert(s[r]);
        best = max<int>(best, r - l + 1);
    }
    return best;
  }
};
