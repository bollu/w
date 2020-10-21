#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
// https://en.wikipedia.org/wiki/Activity_selection_problem
// https://www.youtube.com/watch?v=pN7RzOWIOn4
// 1. Why does this work?
// 2. What solutions *don't* work?

using namespace std;
// dp
namespace f1 {
int main() {
    map<int, set<pair<int, int>>> events;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        pair<int, int> job;
        cin >> job.first >> job.second;
        events[job.first].insert(job);
        events[job.second].insert(job);
    }

    // map of evt to all possible 
    // [end time, number of jobs], removing "obviously better" candidates.
    map<int, set<pair<int, int>>> best;

    // iterate in descending order of finish time.
    for(auto evt = events.rend(); evt != events.rbegin(); ++evt) {
        // for every job at this event..
        // for(pair<int, int> interval : evt->second) {
        // }

    }

    return 0;
}
}  // namespace f1

// greedy
namespace f0 {
int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> ms(n);
    for (int i = 0; i < n; ++i) {
        cin >> ms[i].first >> ms[i].second;
    }

    std::sort(ms.begin(), ms.end(), [](pair<int, int> p1, pair<int, int> p2) {
        return (p1.second < p2.second) ||
               (p1.second == p2.second && p1.first < p2.first);
    });

    int njobs = 0;
    int cur_end = -1;
    for (int i = 0; i < n; ++i) {
        if (cur_end <= ms[i].first) {
            cur_end = ms[i].second;
            njobs++;
        }
    }
    // 0 1 2 3 4 5 6 7 8 9
    //       [---]
    //           [-----]
    //         [---------]
    cout << njobs << "\n";
    return 0;
}
}  // namespace f0

int main() { 
    // return f0::main();
    return f1::main();
}
