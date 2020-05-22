#include <assert.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#define K 100001
using namespace std;
using I = long long int;
using P = pair<I, I>;
P a, b, p0, ps;
I t;
#define man(p, q) (llabs(p.first - q.first) + llabs(p.second - q.second))
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> p0.first >> p0.second;
    cin >> a.first >> a.second;
    cin >> b.first >> b.second;
    cin >> ps.first >> ps.second;
    cin >> t;

    vector<P> line;
    P p = p0;
    line.push_back(p);
    // 2^10 = 10^3
    // 10^16 < (10^3)^6 < (2^10)^6 < 2^60
    const I llmax = 1LL << 61;
    // while(a.first * p.first + b.dfirst < llmax && a.second * p.second +
    // b.second < llmax) {
    while (p.first < (llmax - b.first) / a.first &&
           p.second < (llmax - b.second) / a.second) {
        p.first = a.first * p.first + b.first;
        p.second = a.second * p.second + b.second;
        line.push_back(p);
    }

    // time needed to go from (beginPoint-> L -> R | beginpoint -> R -> L)
    // need to iterate w
    I score = 0;
    I n = line.size();
    for (int i = 0; i < n; ++i) {      // 1st point we readh
        for (int j = i; j < n; ++j) {  // final point in the interval
            // go to i, collect till j
            if (t - man(ps, line[i]) >= man(line[j], line[i])) {
                score = max<I>(score, j - i + 1);
            }

            // go to j, collect till i
            if (t - man(ps, line[j]) >= man(line[j], line[i])) {
                score = max<I>(score, j - i + 1);
            }
        }
    }
    cout << score << "\n";
}
