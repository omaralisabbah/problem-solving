/*
    Given an array of positive integers arr[], find the maximum sum of a subsequence such that the elements of the subsequence form a strictly increasing sequence.
In other words, among all strictly increasing subsequences of the array, return the one with the largest possible sum.

Examples:

Input: arr[] = [1, 101, 2, 3, 100]
Output: 106
Explanation: The maximum sum of an increasing sequence is obtained from [1, 2, 3, 100].

Input: arr[] = [4, 1, 2, 3]
Output: 6
Explanation: The maximum sum of an increasing sequence is obtained from [1, 2, 3].

Input: arr[] = [4, 1, 2, 4]
Output: 7
Explanation: The maximum sum of an increasing sequence is obtained from [1, 2, 4].

Constraints:
1 ≤ arr.size() ≤ 103
1 ≤ arr[i] ≤ 105

*/

/*
    Problem:
    Given an array of positive integers arr[], find the maximum sum of a subsequence
    such that the elements of the subsequence form a strictly increasing sequence.

    Approach:
    - This is a variation of the Longest Increasing Subsequence (LIS) problem.
    - Instead of maximizing the length, we maximize the sum of the subsequence.
    - Use Dynamic Programming (DP):
        * dp[i] = maximum sum of an increasing subsequence ending at index i.
        * Initialize dp[i] = arr[i] (minimum subsequence is the element itself).
        * For each i, check all j < i:
            - If arr[j] < arr[i], then arr[i] can extend the subsequence ending at j.
            - Update dp[i] = max(dp[i], dp[j] + arr[i]).
    - The answer is the maximum value in dp[].

    Complexity:
    - Time: O(n^2) due to nested loops.
    - Space: O(n) for the dp array.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maxSumIS(vector<int>& arr) {
        int n = arr.size();
        vector<int> dp(n);

        // Step 1: Initialize dp with arr[i]
        for (int i = 0; i < n; i++) {
            dp[i] = arr[i];
        }

        // Step 2: Build dp array
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // If arr[j] < arr[i], arr[i] can extend subsequence ending at j
                if (arr[j] < arr[i]) {
                    dp[i] = max(dp[i], dp[j] + arr[i]);
                }
            }
        }

        // Step 3: Find maximum sum among all dp[i]
        int maxSum = dp[0];
        for (int i = 1; i < n; i++) {
            maxSum = max(maxSum, dp[i]);
        }

        return maxSum;
    }
};

// Driver code for testing
int main() {
    Solution sol;

    vector<int> arr1 = {1, 101, 2, 3, 100};
    cout << "Output: " << sol.maxSumIS(arr1) << endl; // Expected: 106

    vector<int> arr2 = {4, 1, 2, 3};
    cout << "Output: " << sol.maxSumIS(arr2) << endl; // Expected: 6

    vector<int> arr3 = {4, 1, 2, 4};
    cout << "Output: " << sol.maxSumIS(arr3) << endl; // Expected: 7

    return 0;
}
