#include <iostream>
#include <assert.h>
#include <map>
#include <vector>
using namespace std;

long long as[1000000];
long long bs[1000000];
long long ms[1000000]; // m = matching


int main() {
    long long an, bn; cin >> an >> bn;
    long long fc, fr, bc; cin >> fc >> fr >> bc;
    as[0] = bs[0] = 0;
    for(int i = 1; i <= an; ++i) cin >> as[i];
    for(int i = 1; i <= bn; ++i) cin >> bs[i];
    as[an+1] = bs[bn+1] = 0;
    an += 2, bn += 2;

    long long out = 0;

    // find pairs, which are guaranteed to exist.
    long long al = 0, bix = 0;
    while(bix < bn-1) {
        assert(as[al] == bs[bix]);
        // [al, ar] matched (inclusive). So al, ar need to be kept, everything inside
        // needs to be removed.
        long long ar = al+1;
        while(as[ar] != bs[bix+1] && ar < an) { ar++; }
	if (ar == an) { cout << "-1"; return false; }
	// printf("[%d, %d...]|an=%d\n", al, ar, an);


        long long maxstr = 0;
        for(long long i = al+1; i <= ar-1; ++i) { maxstr = std::max<long long>(as[i], maxstr); }

        long long len = (ar - 1) - (al + 1) + 1;
        bool bordermax = false;
        if (as[al] > maxstr || as[ar] > maxstr) bordermax = true;

        if (len == 0) { bix++; al = ar; continue; }

        // cannot kill with fireball nor with berserk
        if (len < fr && !bordermax) { cout << "-1\n"; return false; }

        long long need = len % fr; out += need * bc; len -= need;

        // fireball is cost effective
        if (bc * fr >= fc) {
            out += (len / fr) * fc;
        } else {
	  // fireball is not cost effective, and we can kill everyone
	  // using berserk. kill the full thing using berserk.
	  if(bordermax) { 
	    out += len * bc;
	  } else { 
	    // we cannot kill the full thing using berserk, because the strongest monster is not on the border.
	    // So we take down as many monsters as possible and kill the last one with a fireball.
	    out += (len - fr) * bc + fc;
	  }
	}

	al = ar; bix++;
    }

    cout << out << "\n";

    return 0;
}
