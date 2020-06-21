#include <iostream>
#include <math.h>
using namespace std;
using ll = long long;
double h,c,t;
// 1 -> h + c
// 2 -> (h + c)/2
// 3 -> (2h + c)/3
// 4 -> (2h + 2c)/4 = (h + c)/2
// 5 -> (3h + 2c)/5
// double f(double i){ return (c*(i-1) + h*(i))/(2*i-1); }
double f(ll i){ return (ll((i+1)/2)*h + ll(i/2)*c)/(double)i; }
 
void solve()
{
    cin >> h >> c >> t;
    if (t >= h){ cout << 1 << endl; return; }
    if (t <= (h+c)/2){ cout << 2 << endl; return; }

    ll low = 1;
    ll len = 1ll<<38;
    ll gtix;
    while(len >= 1) {
        ll mid = low + len/2;
        if (f(mid) >= t) { gtix = mid; low = mid; }
        len /= 2;
    }
    ll besti = 2;
    double besty = fabs(t - (h+c)/2.0);
    // why don't we have to search _lower_?
    for(ll i=max<ll>(1, gtix-100); i <= gtix+100; ++i) {
        double cy = fabs(t-f(i));
        if (cy < besty) { besti = i; besty = cy; }
    }
    cout << besti << endl;
     
}

int main() { int t; cin >> t; while(t--) solve(); return 0; }
