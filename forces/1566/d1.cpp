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

const int M = 300 + 10;
void solve() {
    int sight[M];
    int n; int m; cin >> n >> m;
    for(int i = 0; i < m; ++i) { cin >> sight[i]; }
    vector<int> rnk2people(m, 0);
    for(int  i = 0; i < m; ++i) { rnk2people[i] = i; }
    // ix2rnk[0] = index with 0th rank.
    sort(rnk2people.begin(), rnk2people.end(), [&](int i, int j) { 
            // want rightmost indexes to be ranked first.
            return (sight[i] < sight[j]) || (sight[i] == sight[j] && i > j); 
        });


    // cout << "\t-rnk2people: [";
    // for(int i = 0; i < m; ++i) {
    //     cout << rnk2people[i] << " ";
    // }
    // cout << "]\n";

    vector<int> people2rnk(m, 0);
    for(int i = 0; i < m; ++i) {
        people2rnk[rnk2people[i]] = i;
    }



    int out = 0;
    vector<bool> occupied(m, false);
    for(int i = 0; i < m; ++i) { 
        // cout << "\t-placing person (" << i << ") at (" << people2rnk[i] << ")\n";
        occupied[people2rnk[i]] = true;
        for(int j = 0; j < people2rnk[i]; ++j) { out += occupied[j]; }
    }
    cout << out << "\n";


}

int main() {
  ios::sync_with_stdio(false);
  int t;
  cin >> t;
  while(t--) { solve(); }

}
