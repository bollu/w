#include <iostream>
#include <unordered_map>
#include <assert.h>

using namespace std;

// Solution from CP algorithms
namespace two_state {

	// sort people from lower to higher weight
	// dp[wt, ix] := max # of people that can be shoved into elevator
	//               with total wt <= wt, people drawn from [1..ix]
	// minimize number of partitions such that each part is <= w.
	static const int N = 20;

	// dp[subset].first := min # of rounds needed to shove into subset elevator
	// dp[subset].second := weight of # of people in last round of moving subset.
	pair<int, int> dp[1<<20];
	int weights[N];
	int main() {
		int n; cin >> n;
		int W; cin >> W;
		for(int i = 0; i < n; ++i) {
			cin >> weights[i];
		}

		dp[0].first = 1; dp[0].second = 0;
		for(int s = 1; s < 1<<n; ++s) {
			dp[s] = {n + 1, 0};
			for(int p = 0; p < n; ++p)  {
				// subset has person `p`.
				if (s & (1 << p)) {
					const auto prev = dp[s ^ (1 << p)];
					auto cur = prev;
					if (prev.second + weights[p] <= W) {
						cur.second += weights[p]; // can find person into last round.
					} else {
						cur.first++; // need one more round.
						cur.second = weights[p]; // round only has this person
					}
					if (cur.first < dp[s].first || 
							(cur.first == dp[s].first && cur.second < dp[s].second)) {
						dp[s] = cur;
					}
				} 
			}
		}
		cout << dp[(1<<n) - 1].first << "\n";
		return 0;
	}

}

// Solution from ITMO course: 
// https://www.youtube.com/watch?v=5C7JT8cVHDU&list=PLrS21S1jm43igE57Ye_edwds_iL7ZOAG4&index=12
namespace last_knapsack {
	// dp[x] = min. no. of knapsacks needed to transport subset x.
	static const int N = 20;
	int dp[1<<N];
	int weights[N];
	int main() {
		int n; cin >> n;
		int W; cin >> W;
		for(int i = 0; i < n; ++i) {
			cin >> weights[i];
		}
		dp[0] = 0;

		for(int s = 1; s < (1<<n); ++s) {
			dp[s] = 1024;
			// min_{ss subset s, wt(ss) <= W} 1 + dp[ss]
			// iterate on all subsets of `s`
			for(int ss = 1; ss <= s; ++ss) {
				// weight of subset.
				// this is a valid subset
				int wt = 0;
				bool is_subset = true;
				for(int b = 0; b < n; ++b) {
					if ((ss & (1 << b)) && !(s & (1 << b))) { is_subset = false; break; } 
					if (ss & (1 << b)) { wt += weights[b]; }
				}
				if (!is_subset) { continue; }
				if (wt <= W) {
					// cout << s << " -> " << ss << " " << (s ^ ss) << "\n";
					dp[s] = min(dp[s], 1 + dp[s ^ ss]);
				}
			}
			// cout << "dp[" << s << "] = " << dp[s] << "\n";
		}
		cout << dp[(1<<n)-1];
		return 0;
	}
}

namespace last_knapsack_fast {
	// dp[x] = min. no. of knapsacks needed to transport subset x.
	static const int N = 20;
	int dp[1<<N];
	int weights[N];
	int main() {
		int n; cin >> n;
		int W; cin >> W;
		for(int i = 0; i < n; ++i) {
			cin >> weights[i];
		}
		dp[0] = 0;

		for(int s = 1; s < (1<<n); ++s) {
			dp[s] = 1024;
			// min_{ss subset s, wt(ss) <= W} 1 + dp[ss]
			// iterate on all subsets of `s`
			for(int ss = s; ss != 0; ss = (ss - 1) & s) {
				// weight of subset.
				// this is a valid subset
				int wt = 0;
				for(int b = 0; b < n; ++b) {
					if (ss & (1 << b)) { wt += weights[b]; }
				}
				if (wt <= W) {
					// cout << s << " -> " << ss << " " << (s ^ ss) << "\n";
					dp[s] = min(dp[s], 1 + dp[s ^ ss]);
				}
			}
			// cout << "dp[" << s << "] = " << dp[s] << "\n";
		}
		cout << dp[(1<<n)-1];
		return 0;
	}
}



int main() {
	return last_knapsack_fast::main();
}
