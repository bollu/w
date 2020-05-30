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
    if (t >= h){
        cout << 1 << endl;
        return;
    }
    if (t <= (h+c)/2){
        cout << 2 << endl;
        return;
    }
    ll low = 1;
    ll len  = 1ll<<38;
    ll steps;
    while(len >= 1) {
        ll mid = low + len/2;
        double cavg = f(mid); // current avg.
        if (cavg >= t){
            steps = mid;
            low = mid;
        }
        len /= 2;
    }
    ll ans = 2;
    double avg = (h+c)/2.0;
    // why don't we have to search _lower_?
    for(int i=0; i <= 100; ++i) {
        double cavg = f(steps+i);
        if (fabs(t-cavg) < fabs(t-avg)){
            ans = steps+i;
            avg = cavg;
        }
    }
    cout << ans << endl;
     
}

int main() { int t; cin >> t; while(t--) solve(); return 0; }
