#include <iostream>

using namespace std;



// ncards: 8 njokers:3 nplayers:2

// ncards: 9 njokers:6 nplayers:3
// maxjokers_single_player: 3
// rest_jokers = 6
int main() {
    int t; cin >> t;
    while(t--) {
        int nplayers, njokers, ncards; 
        cin >> ncards >> njokers >> nplayers;

        int cards_per_player = ncards / nplayers;
        int maxjokers_single_player = min(njokers, cards_per_player); 

        int rest_jokers = njokers - maxjokers_single_player;

        int leftover = (rest_jokers + (nplayers - 1) - 1) / (nplayers - 1);
        cout << maxjokers_single_player - leftover  << "\n";
    }
}
