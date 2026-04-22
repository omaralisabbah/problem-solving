/*
    Vadim has thought of a number x. To ensure that no one can guess it, he appended a positive number of zeros to the right of it, thus
    obtaining a new number y. However, as a precaution, Vadim decided to spread the number n=x+y. Find all suitable x that Vadim
    could have thought of for the given n.

    Input
    Each test consists of several test cases. The first line contains a single integer t(1≤t≤104)— the number of test cases.
    The following lines describe the test cases.

    In a single line of each test case, there is an integer n— the number spread by Vadim (11≤n≤1018).

    Output
    For each number n, output 0 if there are no suitable x. Otherwise, output the number of suitable x, followed by all suitable x in ascending order.

    Example
    Input

    5
    1111
    12
    55
    999999999999999999
    1000000000000000000

    Output

    2
    11 101
    0
    1
    5
    3
    999999999 999000999000999 90909090909090909
    0

    Note
    In the first sample, to 11 one can append two zeros to the right, then 11+1100=1111, and to 101 one can append one zero to the right,
    then 101+1010=1111.

    In the second sample, it is impossible to obtain 12 through the described actions.


*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int t;
    cin >> t;

    while (t--) {
        long long n;
        cin >> n;

        vector<long long> results;

        long long power10 = 10;
        for (int k = 1; k <= 18; ++k) {
            long long d = 1 + power10;
            if (n % d == 0) {
                long long x = n / d;
                results.push_back(x);
            }
            // Avoid overflow
            if (power10 > 1e18 / 10) break;
            power10 *= 10;
        }

        if (results.empty()) {
            cout << 0 << '\n';
        } else {
            sort(results.begin(), results.end());
            cout << results.size() << '\n';
            for (long long x : results) {
                cout << x << ' ';
            }
            cout << '\n';
        }
    }

    return 0;
}