#include <assert.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>  // for gcd
#include <queue>
#include <set>
#include <stack>
#include <vector>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp>  // Common file
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/tree_policy.hpp>  // Including tree_order_statistics_node_update



using ll = long long;
using namespace std;

template <typename T>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, less<T>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename K, typename V>
using ordered_map =
    __gnu_pbds::tree<K, V, less<K>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;

template <typename T1, typename T2>
ostream &operator<<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}

// naive, build queue
namespace f0 {

struct Event {
    ll evtime, period, uuid;
    Event(ll evtime, ll period, ll uuid)
        : evtime(evtime), period(period), uuid(uuid){};
    bool operator<(const Event &other) const {
        return make_tuple(evtime, period, uuid) <
               make_tuple(other.evtime, other.period, other.uuid);
    }
};

int main() {
    ll n, N;
    cin >> n >> N;
    vector<int> times(n);
    ll Tlcm = 1;

    for (int i = 0; i < n; ++i) {
        cin >> times[i];
        Tlcm = lcm(Tlcm, times[i]);
    }

    ll n_in_Tlcm = 0;
    for (int i = 0; i < n; ++i) {
        n_in_Tlcm += Tlcm / times[i];
    }

    ll leftover = N % n_in_Tlcm;
    // cout << "leftover: " << N << " % " << n_in_Tlcm << " (" << N % n_in_Tlcm << ")\n";

    ll last_time = 0;
    set<Event> events;
    for (int i = 0; i < n; ++i) {
        events.insert(Event(times[i], times[i], i));
    }
    while (leftover != 0) {
        auto it = events.begin();
        assert(it != events.end());
        leftover--;
        // cout << "(time=" << it->evtime << ", period=" << it->period << ") ";
        events.insert(Event(it->evtime + it->period, it->period, it->uuid));
        last_time = max(last_time, it->evtime);
        events.erase(it);
    }

    cout << (N / n_in_Tlcm) * Tlcm  + last_time << "\n";
}

}

// https://usaco.guide/solutions/cses-1620
// Explpoit monotonicity
namespace f1 {
    ll nproduced(vector<ll> &times, ll totaltime) {
        ll n = 0; for(ll t : times) { n += totaltime / t; } return n;
    }

    int main() {
        ll nmachines, Nwidgets;
        cin >> nmachines >> Nwidgets;
        vector<ll> times(nmachines);
        for(int i = 0; i < nmachines; ++i) { cin >> times[i]; }

        ll ltime = 0;
        ll rtime = *std::min_element(times.begin(), times.end()) * Nwidgets+1;

        // interval is [l, r)
        while (ltime < rtime) {
            ll midtime = (ltime + rtime)/2;

            const bool success = nproduced(times, midtime) >= Nwidgets;
            // cout << "[" << ltime << ":" << midtime << ":" << rtime << "]" << success << "\n";
            if (success) { rtime = midtime; }
            else { ltime = midtime+1; }
        }
        cout << ltime << "\n";
        return 0;
    };
}

int main() {
    f1::main();
}
