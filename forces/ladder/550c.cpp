#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<utility>
#include<algorithm>
using namespace std;
using ll = long long;

// You are given a non-negative integer n, its decimal representation consists of at most 100 digits and doesn't contain leading zeroes.
// Your task is to determine if it is possible in this case to remove some of
// the digits (possibly not remove any digit at all) so that the result
// contains at least one digit, forms a non-negative integer, doesn't have
// leading zeroes and is divisible by 8. After the removing, it is forbidden to
// rearrange the digits.
// Consider mod 8. Anything mod 1000 and above will disappear, because 1000 % 8 = 0, while 100 % 8 = 4.
// So we only need to keep 3 digits. DP.

int main() {
    ios::sync_with_stdio(false);
    std::string s; cin >> s;
    vector<int> ds(s.size());
    for(int i = 0; i < s.size(); ++i) { ds[i] = s[i] - '0'; }

    for(int i = 0; i < ds.size(); ++i) {
        if (ds[i] % 8 == 0) {
            cout << "YES\n" << ds[i]; return 0;
        }
    }

    for(int i = 0; i < ds.size(); ++i) {
        for(int j = i+1; j < ds.size(); ++j) {
            int n = ds[i]*10+ds[j];
            if (n % 8 == 0) {
                cout << "YES\n" << n; return 0;
            }
        }
    }

    for(int i = 0; i < ds.size(); ++i) {
        for(int j = i+1; j < ds.size(); ++j) {
            for(int k = j+1; k < ds.size(); ++k) {
                int n = 100*ds[i] + 10*ds[j] + ds[k];
                if (n % 8 == 0) { 
                    cout << "YES\n";
                    cout << n;
                    return 0;
                }
            }
        }
    }

    cout << "NO\n";
    return 0;
}



