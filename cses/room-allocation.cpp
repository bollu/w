#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <stack>
#include <queue>
#include <assert.h>

// https://codeforces.com/blog/entry/11080
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>


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

template<typename T1, typename T2>
ostream &operator <<(ostream &o, const pair<T1, T2> &p) {
    return o << "(" << p.first << ", " << p.second << ")";
}


struct Event {
    int ix;
    int date;
    bool arrival;
    Event() : ix(-42), date(-42), arrival(false) {}
    Event(const Event &other) : ix(other.ix), date(other.date), arrival(other.arrival) { }
    bool operator < (const Event &other) const {
        // first proritize by date
        // if two different customers, then order departure before arrival
        // if same customer, then order arrival before departure.
        if (date != other.date) { return date < other.date; }
        int myarrive = arrival ? 0 : 1;
        int otherarrive = other.arrival ? 0 : 1;
        // put arrivals before departure
        if (myarrive != otherarrive) { return myarrive < otherarrive; }
        // put other customers before me
        if (ix != other.ix) { return ix > other.ix; }
        return false;
    }
};

int main() { 
    int n; cin >> n;
    vector<Event> es(2*n);

    for(int i = 0; i < n; ++i) {
        cin >> es[2*i].date;
        cin >> es[2*i+1].date;
        es[2*i].ix = es[2*i+1].ix = i;

        es[2*i].arrival = true;
        es[2*i+1].arrival = false;
    }

    int max_rooms = 0;
    map<int, int> ix2room;
    set<int> free_rooms;
    set<int> occupied_rooms;
    std::sort(es.begin(), es.end());
    for(int i = 0; i < es.size(); ++i) {
        // cout << "ix: " << es[i].ix << " | date: " << es[i].date << " | " 
        //     << (es[i].arrival ? "arrival" : " departure") << "\n";

        if (es[i].arrival) {
            if (!free_rooms.size()) {
                max_rooms++;
                occupied_rooms.insert(max_rooms);
                ix2room[es[i].ix] = max_rooms;
            } else {
                int roomix = *free_rooms.begin();
                free_rooms.erase(roomix);
                occupied_rooms.insert(roomix);
                ix2room[es[i].ix] = roomix;
            }
        } else {
            auto it = ix2room.find(es[i].ix);
            // assert(it != ix2room.end());
            // erase the room.
            int roomix = it->second;
            occupied_rooms.erase(roomix);
            free_rooms.insert(roomix);
        }
    }

    cout << max_rooms << "\n";
    for(int i = 0; i < n; ++i) {
        cout << ix2room[i] << "  ";
    }
    cout << "\n";

    return 0;
}
