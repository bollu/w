#include <iostream>
#include <vector>
using namespace std;

// {1, 15, 25} and the sum 30
// G: [25] + 5x[1]
// O*: 2x[15]

// Let O* be optimal, G be greedy soln.
// O* will convert 5x[1] -> 1x[5]
// O* will convert 2x[5] -> 1x[10]
// O* will convert 2x[10] -> 1x[20]
// O* will convert 5x[20] -> 1x[100]
//
// O* can have at most: 4x[1], 1x[5], 1x[10], 4x[20]. If it has more, it is optimal to convert
// to larger coin.
//
// G: take as many 100, 10, 5, 1 as possible in succession.
// Suppose that O takes less 100s than G. Then O must use smaller coins. Using smaller coins, it can take at most
//   4x[20] + 1x[10] + 1x[5] + 4x[1]
// which has total value 99. But 99 < 100, so optimal solution literally can't represent 100, if it chooses to not
// use the 100 coin. Thus, it will be forced to take the 100 coin.
//
// So both G and O* use the same number of 100 coins.
//
int main() {
    int n; cin >> n;
    long n100 = n/100; n -= n100 * 100;
    long n20 = n/20; n -= n20 * 20;
    long n10 = n/10; n -= n10 * 10;
    long n5 = n/5; n -= n5 * 5;
    long n1 = n/1;
    cout << n100 + n20 + n10 + n5 + n1 << "\n";
}
