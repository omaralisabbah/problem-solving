/*
    Given two arrays, a[] and b[], find the length of the longest common increasing subsequence(LCIS).

Note:  LCIS refers to a subsequence that is present in both arrays and strictly increases.

Examples:

Input: a[] = [3, 4, 9, 1], b[] = [5, 3, 8, 9, 10, 2, 1]
Output: 2
Explanation: The longest increasing subsequence that is common is [3, 9] and its length is 2.

Input: a[] = [1, 1, 4, 3], b[] = [1, 1, 3, 4]
Output: 2
Explanation: There are two common subsequences [1, 4] and [1, 3] both of length 2.

Constraints:
1 ≤ a.size(), b.size() ≤ 103
1 ≤ a[i], b[i] ≤ 104
*/

/*
    Problem: Longest Common Increasing Subsequence (LCIS)

    Given two arrays a[] and b[], find the length of the longest common increasing subsequence (LCIS).
    LCIS refers to a subsequence that is present in both arrays and strictly increases.

    Approach:
    ----------
    - We use Dynamic Programming with O(n * m) time complexity.
    - Maintain a dp[] array of size m, where dp[j] represents the length of LCIS ending with b[j].
    - For each element a[i]:
        * Track current_max = maximum LCIS length for elements smaller than a[i].
        * If a[i] == b[j], update dp[j] = max(dp[j], current_max + 1).
        * If a[i] > b[j], update current_max = max(current_max, dp[j]).
    - The result is the maximum value in dp[].

    Complexity:
    -----------
    - Time: O(n * m), where n = size of a[], m = size of b[]
    - Space: O(m)

    Example:
    --------
    Input: a = [3, 4, 9, 1], b = [5, 3, 8, 9, 10, 2, 1]
    Output: 2
    Explanation: LCIS is [3, 9]

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int LCIS(vector<int> &a, vector<int> &b) {
        int n = a.size(), m = b.size();
        vector<int> dp(m, 0);  // dp[j] = LCIS ending at b[j]

        for (int i = 0; i < n; i++) {
            int current_max = 0;
            for (int j = 0; j < m; j++) {
                if (a[i] == b[j]) {
                    dp[j] = max(dp[j], current_max + 1);
                }
                if (a[i] > b[j]) {
                    current_max = max(current_max, dp[j]);
                }
            }
        }

        return *max_element(dp.begin(), dp.end());
    }
};

// Driver code for testing
int main() {
    Solution sol;

    vector<int> a1 = {3, 4, 9, 1};
    vector<int> b1 = {5, 3, 8, 9, 10, 2, 1};
    cout << "LCIS length (Example 1): " << sol.LCIS(a1, b1) << endl; // Expected: 2

    vector<int> a2 = {1, 1, 4, 3};
    vector<int> b2 = {1, 1, 3, 4};
    cout << "LCIS length (Example 2): " << sol.LCIS(a2, b2) << endl; // Expected: 2

    return 0;
}
