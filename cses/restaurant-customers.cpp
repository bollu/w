#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

static const int TMAX = 1000000007;

struct event { 
    int t = -1; int act = 0;
    // all times unique.
    bool operator < (const event &other) { return this->t < other.t; }
};

using namespace std;
int main1() { 
    int n; cin >> n;
    vector<event> ts(2*n);
    for(int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        ts[i*2].t = a; ts[i*2].act = +1; 
        ts[i*2+1].t = b; ts[i*2+1].act = -1;
    }

    std::sort(ts.begin(), ts.end());

    int cnt = 0, maxcnt = 0;
    for(int i = 0; i < 2*n; ++i) {
        cnt += ts[i].act;
        maxcnt = max<int>(cnt, maxcnt);
    }
    cout << maxcnt << "\n";
    return 0;
}

int main0() { 
    int n; cin >> n;
    vector<int> as(n), bs(n);
    for(int i = 0; i < n; ++i) {
        cin >> as[i] >> bs[i];
    }

    std::sort(as.begin(), as.end());
    std::sort(bs.begin(), bs.end());

    int ai = 0, bi = 0;
    int cnt = 0, maxcnt = 0;
    while(ai < n || bi < n) {
        int Tnext = TMAX;
        if (ai < n) { Tnext = min<int>(Tnext, as[ai]); }
        if (bi < n) { Tnext = min<int>(Tnext, bs[bi]); }
        // arrival
        if (ai < n && Tnext == as[ai]) { ai++; cnt++; maxcnt = max<int>(cnt, maxcnt); }
        // departure
        if (bi < n && Tnext == bs[bi]) { bi++; cnt--; maxcnt = max<int>(cnt, maxcnt); }
    }
    cout << maxcnt << "\n";
    return 0;
}
int main() { return main1(); }
