#include <assert.h>
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
#include <queue>
#include <stack>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        vector<int> as(n+1);
        vector<int> bs(n+1);
        int asum = 0;
        for(int i = 1; i <= n; ++i) { cin >> as[i]; asum += as[i]; }
        int bsum = 0;
        for(int i = 1; i <= n; ++i) { cin >> bs[i]; bsum += bs[i];}

        if (asum != bsum) { cout << -1 << "\n"; continue; }

        vector<pair<int, int>> commands;

        for(int i = 1; i != n; ++i) {
            if (as[i] == bs[i]) {
                continue; 
            } else if (as[i] > bs[i]) {
                while(as[i] != bs[i]) {
                    for(int j = i+1; j <= n; ++j) {
                        if (as[j] < bs[j]) {
                            as[i]--;
                            as[j]++;
                            commands.push_back({i, j});
                            break;
                        }
                    }
                }
                assert(as[i] == bs[i]);
            } else {
                // as[i] < bs[i]
                while(as[i] != bs[i]) {
                    for(int j = i+1; j <= n; ++j) {
                        if (as[j] > bs[j]) {
                            as[i]++;
                            as[j]--;
                            commands.push_back({j, i});
                            break;
                        }
                    }
                }
                assert(as[i] == bs[i]);
            }
        }
        // for(int i = 1; i != n; ++i) {
        //     while(as[i] > 0) {
        //         commands.push_back({i, n});
        //         as[i]--;
        //     }
        // }

        // for(int i = 1; i != n; ++i) {
        //     while(as[i] != bs[i]) {
        //         commands.push_back({n, i});
        //         as[i]++;
        //     }
        // }

        cout << commands.size() << "\n";
        for(auto c : commands) {
            cout << c.first << " " << c.second << "\n";
        }
    }
}



