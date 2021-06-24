#include <iostream>
using namespace std;
// let f(n) be min. number of moves to reduce n to 0 as per beaver algo.
// Let D(n) be the set of digits of n
// f(n) := 1 + min[d in D(n)] f(n-d): 
//
// Claim. if f(n) is monotone (f(n) >= f(n-1)), then subtracting more is better!
// intuition: if f(n) is monotone (n > m => f(n) > f(m)), then the faster we can
//   make n smaller, the less steps we need: n1' < n2' => f(n1') < f(n2').
//   So us making the number smaller is advantageous.
// claim. f(n) is monotone
// proof by induction: 
//   - base case: f(1) = 1 > f(0) = 0.
//   - inductive case: let k := max(D(n)) (k is largest digit of n) . let l := max(D(n-1)) [largest digit of (n-1)].
//      Claim: l >= k-1. (eg. 69[max=9] → 68[max=8]. 8 >= 9-1. 
//                             64[max=6] → 63[max=6]. 6 >= 6-1. 
//                             60[max=6] → 59[max=9]. 9 >= 6-1.
//      f(n-1) = 1 + min[d in D(n-1)]f((n-1)-d)
//             <= 1 + f((n-1)-l)   [d is the value that minimizes f((n-1)-d). Any other choice will be larger]
//             <= 1 + f((n-1)-(k-1)) [l >= k-1 implies n-1-l <= n-1-(k-1), which implies f(n-1-l) <= f((n-1)-(k-1)) by monotonicity]
//             <= 1 + f(n-k)
//      So f(n-1) <= 1 + f(n-k)
//     
//     In addition, since f(n) = min[d in D(n)]f(n-d).
//     since k=max D(n) and f is monotone on [1..n-1], f(n-k) is smallest amongst all choice.
//     so f(n) = 1 + f(n-k). 
//     Proof looks dubious at best.
//
//
//  claim: f(n) >= f(n-1).
//  base case: f(1) >= f(0). done.
//  inductive: assume f(n) >= f(n-1) for all n. Now we need to show f(n+1) >= f(n).
//  Recall that f(n+1) = 1 + min[d in D(n+1)] f((n+1)-d)
//  We will have some non-zero digit in D(n+1). So (n+1)-d <= n. So we are considering inputs of the form `min[d in D(n+1)] f(x)` where `x <= n`.
//  f is monotonic for `x <= n`. Which means choosing the largest digit gives the best results? So, we need to show that `n` has larger digit than `n+1`.
//  That's not strictly true. what is true is that `1 + max D(n) >= max(D(n+1))`. 

int maxdigit(int n) {
	int mx=0;
	while(n != 0) {
        mx = max(mx, n%10);
		n /= 10;
	}
	return mx;
}
 


int main() {
    int n; cin >> n;
    int count = 0;
    while(n > 0) {
        count++; n -= maxdigit(n);
    }
    cout << count << "\n";

}
