#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
using namespace std;
using ll = long long;

int n, m, d; 
static const int INF = 1e9;

int cost(std::vector<int> &as, int mid) {
    int c = 0;
    for(int i = 0; i < (int)as.size(); ++i) {
        c += abs(as[i] - as[mid]);
    }
    return c;
}

int main() {
    cin >> n >> m >> d;
    vector<int> nums(n*m);

    for(int i = 0; i < n*m; ++i) { 
        cin >> nums[i];
    }
    for(int i = 0; i < n*m; ++i) {
        if (nums[0] % d == nums[i] % d) continue;;
        cout << "-1";
        return 0;
    }

    vector<int> steps(n*m);
    for(int i = 0; i < n*m; ++i) {
        int residue = nums[i] % d;
        steps[i] = (nums[i] - residue)/d;
        assert(steps[i] * d + residue == nums[i]);
    }
    std::sort(steps.begin(), steps.end());
    int mid = (n*m)/2;
    int c = INF;
    // TODO: think about what the exact range should be for median.
    for(int i = mid -2; i <= mid+3; ++i) {
        if (i  < 0) continue;
        if (i >= n*m) continue;
        c = min(c, cost(steps, mid));
    }
    std::cout << c << "\n";

    return 0;
}

