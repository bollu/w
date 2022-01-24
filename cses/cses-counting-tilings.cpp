#include <iostream>
#include "assert.h"

using namespace std;

namespace straight_profile {
	const int NMAX = 10;
	const int MMAX = 1000;

	// dp[m][profile] = number of states where [0..m] is filled up, with profile <profile>
	// (ie, board[m][n] is filled iff profile[n] is true)
	int dp[MMAX][1<<NMAX];
	int N, M;
	const int MOD = 1e9 + 7;
	bool compatible(int p, int q) {
		for(int i = 0; i < N;) {
			const bool pi = p & (1 << i);
			const bool qi = q & (1 << i);
			const bool pii = p & (1 << (i + 1));
			const bool qii = q & (1 << (i + 1));

			//   | m| m+1 |m+2
			//   +--|-----|
			//p  p  |     |
			//   |  |     |
			//q  |  q     |
			if (pi == 0 && qi == 0) {
				// need vertical bar
				if (i + 1 < N && pii == 0 && qii == 0) {
					i += 2; continue;
				} else {
					return false; 
				}
			}
			else if (pi == 0 && qi == 1) {
				//   | m| m+1 |m+2
				//   +--|-----|
				//p  p  |     |
				//   |  |     |
				//q  |  |     q
				// need horizontal bar
				i += 1; continue;

			}
			else if (pi == 1 && qi == 0) {
				//   | m| m+1 |m+2
				//   +--|-----|
				//p  |  p     |
				//   |  |     |
				//q  |  q     |
				// nothing to fill. continue
				i += 1; continue;
			} else if (pi == 1 && qi == 1) {
				//   | m| m+1 |m+2
				//   +--|-----|
				//p  |  p     |
				//   |  |     |
				//q  |  |     q
				// need vertical bar in column (m+1)
				// but remember that we are only filling column m!
				// thus this stae is invalid!
				return false;
			} else {
				assert(false && "unreachable");
			}
		}
		return true;
	}

	void plus_equals_mod(int &result, int val) {
		result = (result + val) % MOD;
	}

	int main() {
		cin >> N >> M;
		dp[0][0] = 1;
		for(int m = 0; m < M; ++m) {
			for(int p = 0; p < 1<<N; ++p) {
				for(int q = 0; q < 1<<N; ++q) {
					if(compatible(p, q)) {
						plus_equals_mod(dp[m+1][q], dp[m][p]);
					}
				}
			}
		}
		cout << dp[M][0] << "\n";
		return 0;
	}
}

namespace straight_profile_transition_cache {
	const int NMAX = 10;
	const int MMAX = 1000;

	// dp[m][profile] = number of states where [0..m] is filled up, with profile <profile>
	// (ie, board[m][n] is filled iff profile[n] is true)
	int dp[MMAX][1<<NMAX];
	int N, M;
	const int MOD = 1e9 + 7;
	bool compatible(int p, int q) {
		for(int i = 0; i < N;) {
			const bool pi = p & (1 << i);
			const bool qi = q & (1 << i);
			const bool pii = p & (1 << (i + 1));
			const bool qii = q & (1 << (i + 1));

			//   | m| m+1 |m+2
			//   +--|-----|
			//p  p  |     |
			//   |  |     |
			//q  |  q     |
			if (pi == 0 && qi == 0) {
				// need vertical bar
				if (i + 1 < N && pii == 0 && qii == 0) {
					i += 2; continue;
				} else {
					return false; 
				}
			}
			else if (pi == 0 && qi == 1) {
				//   | m| m+1 |m+2
				//   +--|-----|
				//p  p  |     |
				//   |  |     |
				//q  |  |     q
				// need horizontal bar
				i += 1; continue;

			}
			else if (pi == 1 && qi == 0) {
				//   | m| m+1 |m+2
				//   +--|-----|
				//p  |  p     |
				//   |  |     |
				//q  |  q     |
				// nothing to fill. continue
				i += 1; continue;
			} else if (pi == 1 && qi == 1) {
				//   | m| m+1 |m+2
				//   +--|-----|
				//p  |  p     |
				//   |  |     |
				//q  |  |     q
				// need vertical bar in column (m+1)
				// but remember that we are only filling column m!
				// thus this stae is invalid!
				return false;
			} else {
				assert(false && "unreachable");
			}
		}
		return true;
	}

	void plus_equals_mod(int &result, int val) {
		result = (result + val) % MOD;
	}

	int main() {
		cin >> N >> M;
		dp[0][0] = 1;

		bool T[1<<N][1<<N];
		for(int p = 0; p < 1<<N; ++p) {
			for(int q = 0; q < 1<<N; ++q) {
				T[p][q] = compatible(p, q);
			}
		}


		for(int m = 0; m < M; ++m) {
			for(int p = 0; p < 1<<N; ++p) {
				for(int q = 0; q < 1<<N; ++q) {
					if(T[p][q]) {
						plus_equals_mod(dp[m+1][q], dp[m][p]);
					}
				}
			}
		}
		cout << dp[M][0] << "\n";
		return 0;
	}
}


namespace broken_profile {
}
int main() {
	return straight_profile_transition_cache::main();
}
