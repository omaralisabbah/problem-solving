/*
    You are given two integers l and r. Find the result after applying the series of Bitwise AND ( & ) operation on every natural number between the range l to r (including both).

Examples:

Input: l = 8, r = 13
Output: 8
Explanation: 
8 AND 9 AND 10 AND 11 AND 12 AND 13 = 8.

Input: l = 2, r = 3
Output: 2
Explanation: 2 AND 3 = 2.

Constraints:
1 ≤ l ≤ r ≤ 109


🔎 Key Insight

    The bitwise AND of all numbers in a range [l, r] essentially keeps only the common prefix bits of l and r.

    As soon as a bit position differs between l and r, all lower bits (to the right) will eventually be zeroed out because the range covers numbers with both 0 and 1 in those positions.

⚡ Efficient Approach

Instead of iterating through all numbers (which is impossible for large ranges), we:

    Compare l and r bit by bit.

    Shift both numbers right until they become equal.

    Count how many shifts we did.

    Shift the result back left to restore the common prefix.

This works because the AND result is exactly the common prefix of l and r in binary, padded with zeros.


*/


/*
    Problem:
    --------
    You are given two integers l and r. Find the result after applying the series
    of Bitwise AND (&) operation on every natural number between the range l to r
    (including both).

    Examples:
    ---------
    Input: l = 8, r = 13
    Output: 8
    Explanation: 8 & 9 & 10 & 11 & 12 & 13 = 8

    Input: l = 2, r = 3
    Output: 2
    Explanation: 2 & 3 = 2

    Constraints:
    ------------
    1 ≤ l ≤ r ≤ 1e9

    Approach:
    ---------
    - The AND of all numbers in [l, r] keeps only the common prefix bits of l and r.
    - As soon as a bit differs between l and r, all lower bits will eventually be zeroed.
    - Efficient method:
        1. Shift l and r right until they become equal.
        2. Count how many shifts were done.
        3. Shift the result back left to restore the common prefix.
    - Time complexity: O(log(max(l, r))) which is very efficient.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int andInRange(int l, int r) {
        int shift = 0;
        // Keep shifting until l == r
        while (l < r) {
            l >>= 1;
            r >>= 1;
            shift++;
        }
        // Restore the common prefix
        return l << shift;
    }
};

int main() {
    Solution sol;

    // Example 1
    int l1 = 8, r1 = 13;
    cout << "AND in range [" << l1 << ", " << r1 << "] = "
         << sol.andInRange(l1, r1) << endl;

    // Example 2
    int l2 = 2, r2 = 3;
    cout << "AND in range [" << l2 << ", " << r2 << "] = "
         << sol.andInRange(l2, r2) << endl;

    // You can test with custom inputs:
    int l, r;
    cout << "Enter l and r: ";
    cin >> l >> r;
    cout << "AND in range [" << l << ", " << r << "] = "
         << sol.andInRange(l, r) << endl;

    return 0;
}
