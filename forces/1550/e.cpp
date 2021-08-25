#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <bitset>
#include <utility>
#include <vector>
using namespace std;
using ll = long long;

int n, k;
string s;

static const int N = 2e5 + 1;
static const int K = 17 + 1;
// prefixSum[K][N]:  # of occurrences of char 'k' in [0, 'n'). 
int prefixSum[K][N+1];


// recall: `len` is global, being searched upon.
// nextPlace[K][N]: next location (`nextPlace[K][N] > N`)
//    where we can place `len` occurrences of character `k`.
int nextPlace[K][N+1];

// shortest length of prefix of string we can use to cover that mask of letters.
int earliestReachable [1<<K];

// lemma: always optimal to place in blocks.
// lemma: question is monotone.


// lemma: Put each block after the previous one 
//    but as far to the left as possible
//    (the correctness can be proven by showing
//    that picking not the furthest to the left position can't be more optimal). 
// create k blocks of length x in the string.
bool solve(int len) {
	for(int c = 0; c < k; ++c) {
		prefixSum[c][0] = 0; 
		for(int i = 1; i <= n; ++i) {
			char sc = s[i-1];
			prefixSum[c][i] = prefixSum[c][i-1] + (sc - 'a' == c || sc == '?');
		}
	}


	// initially: can only go 'outside string'.
	for(int c = 0; c < k; ++c) {
		nextPlace[c][n] = n+1;
		for(int i = n-1; i >= 0; i--) {
			nextPlace[c][i] = nextPlace[c][i+1];
			// if there's space to place `d` characters of this type, then
			// this is the leftmost location we can place these `d` characters
			// using the suffix range [i: ...)
			if (i + len <= n && 
				prefixSum[c][i+len] - prefixSum[c][i] >= len) {
				nextPlace[c][i] = i;
			}
		}
	}

	// for(int c = 0; c < k; ++c) {
	// 	cout << "len{" << len << "} nextPlace{" << char('a' + c) << "}:\n\t";
	// 	for(int i = 0; i <= n; ++i) {
	// 		cout << i << "{" << nextPlace[c][i] << "} ";
	// 	}
	// 	cout << "\n";
	// }

	// for a string of length 0, can reach in length 0.
	earliestReachable[0] = 0;
	for(int mask = 1; mask <= 1<<k; ++mask) {
			earliestReachable[mask] = n+1;
		std::string maskstr = std::bitset<16>(mask).to_string();
		// the final character we end up placing.
		// we know what the mask was without this final character.
		for(int finalc = 0; finalc < k; ++finalc) {
			// this mask does not place this character.
			if ((mask & (1 << finalc)) == 0)  { continue; }
			// mask we are coming from.
			int prev = mask ^ (1 << finalc);
			// find length of prefix from earlier mask.
			int prevEnd = earliestReachable[prev];
			// length from earlier mask is unuistable. skip.
			if (prevEnd >= n) { continue; }
			int start = nextPlace[finalc][prevEnd];
			// earliest reachable length will be previous length plus our length.
			// why do we need min, why can't we simply override?
			// oh okay, because we are brute forcing over finalc, got it.
			earliestReachable[mask] = min<int>(earliestReachable[mask], start+len);
			// cout << "\tearliestReachable{" << maskstr << "} finalc{" << finalc << "} {" << earliestReachable[mask] << "}\n";
		}
	}

	// check if the final mask fits in the string.
	return earliestReachable[(1<<k)-1] <= n;
}

int main() {
    ios::sync_with_stdio(false);
 	cin >> n >> k;
 	cin >> s;
 	int best = 0;
 	int l = 0; int r = n;
 	while(l <= r) {
 		int mid = (l + r)/2;
 		if (solve(mid)) {
 			best = max<int>(mid, best);
 			l = mid+1;
 		} else {
 			r = mid-1;
 		}
 	}
 	cout << best << "\n";
}

