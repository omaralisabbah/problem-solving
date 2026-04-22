/*
    Given an array stones[], where the ith element represents the number of stones in the ith pile.
In one move, you can merge exactly k consecutive piles into a single pile, and the cost of this move is equal to the total number of stones in these k piles.
Determine the minimum total cost required to merge all the piles into one single pile. If it is not possible to merge all piles into one according to the given rules, return -1.

Examples:

Input: stones[] = [1, 2, 3], k = 2
Output: 9
Explanation: Initially the array looks like [1, 2, 3].
First, we merge first 2 stones, i.e., 1 and 2, array becomes [3, 3] and cost is 1 + 2 = 3.
Then, we merge remaining stones, i.e., 3 and 3, array becomes [6] and the cost = 3 + 3 = 6.
Total cost = 3 + 6 = 9.

Input: stones[] = [1, 5, 3, 2, 4], k = 2
Output: 35
Explanation: Initially the array looks like [1, 5, 3, 2, 4].
First, we merge 1 and 5, array becomes [6, 3, 2, 4] and cost is 1 + 5 = 6.
Then, we merge 3 and 2, array becomes [6, 5, 4] and the cost = 3 + 2 = 5.
Then, we merge 5 and 4, array becomes [6, 9] and the cost = 5 + 4 = 9.
Finally, we merge 6 and 9, array becomes [15] and the cost = 6 + 9 = 15.
Total cost = 6 + 5 + 9 + 15 = 35.

Input: stones[] = [1, 5, 3, 2, 4], k = 4
Output: -1
Explanation: There is no possible way to combine the stones in piles of 4 to get 1 stone in the end.

Constraints:
1 ≤ stones.size() ≤ 30
2 ≤ k ≤ 30
1 ≤ stones[i] ≤ 100



Great problem — this is a classic dynamic programming (DP) challenge often called Minimum Cost to Merge Stones. Let’s carefully break it down and then provide the C++ solution.
🔑 Key Observations

    Feasibility Check To merge piles into one, the number of piles must reduce by exactly k−1k-1 each time.

        Starting with nn piles, ending with 1 pile requires: (n−1)%(k−1)==0(n-1) \% (k-1) == 0.

        If not, return -1.

    Prefix Sum for Fast Range Sum Since merging cost = sum of stones in the merged segment, we precompute prefix sums.

    DP State Definition Let:

        dp[i][j] = minimum cost to merge piles from index i to j into one pile.

        To compute this, we may need intermediate states where the segment is merged into multiple piles first.

common trick:

    dp[i][j] = minimum cost to merge piles from i to j into any number of piles, not necessarily one.

    Then, when the number of piles in [i..j] can be reduced to 1, we add the sum of stones.

Transition

    Split [i..j] into [i..m] and [m+1..j] with step (k-1) to ensure valid merges.

    Recurrence:
    dp[i][j] = min(dp[i][m] + dp[m+1][j])   for all valid m

If (j-i) % (k-1) == 0, then we can merge into 1 pile, so:
dp[i][j] += sum(i..j)

*/

/**
 * Problem: Minimum Cost to Merge Stones
 * -------------------------------------
 * You are given an array stones[], where the ith element represents the number of stones in the ith pile.
 * In one move, you can merge exactly k consecutive piles into a single pile, and the cost of this move
 * is equal to the total number of stones in these k piles.
 *
 * Goal: Determine the minimum total cost required to merge all the piles into one single pile.
 * If it is not possible to merge all piles into one according to the given rules, return -1.
 *
 * Constraints:
 *  - 1 ≤ stones.size() ≤ 30
 *  - 2 ≤ k ≤ 30
 *  - 1 ≤ stones[i] ≤ 100
 *
 * Approach:
 * ---------
 * 1. **Feasibility Check**:
 *    - To merge piles into one, the number of piles must reduce by exactly (k-1) each time.
 *    - Starting with n piles, ending with 1 pile requires: (n-1) % (k-1) == 0.
 *    - If not satisfied, return -1 immediately.
 *
 * 2. **Prefix Sum**:
 *    - Precompute prefix sums to quickly calculate the sum of stones in any subarray [i..j].
 *
 * 3. **Dynamic Programming (DP)**:
 *    - Define dp[i][j] = minimum cost to merge stones[i..j] into one pile.
 *    - Transition:
 *        dp[i][j] = min(dp[i][m] + dp[m+1][j]) for all valid splits m.
 *    - If (length-1) % (k-1) == 0, then we can merge into one pile, so:
 *        dp[i][j] += sum(i..j).
 *
 * 4. **Complexity**:
 *    - Time: O(n^3 / (k-1)), feasible for n ≤ 30.
 *    - Space: O(n^2).
 *
 * Example:
 * --------
 * Input: stones = [1,2,3], k = 2
 * Output: 9
 *
 * Explanation:
 *   Merge [1,2] → cost = 3, array becomes [3,3].
 *   Merge [3,3] → cost = 6, array becomes [6].
 *   Total cost = 3 + 6 = 9.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mergeStones(vector<int>& stones, int k) {
        int n = stones.size();

        // Step 1: Feasibility check
        if ((n - 1) % (k - 1) != 0) return -1;

        // Step 2: Prefix sums for fast range sum queries
        vector<int> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + stones[i];
        }

        // Step 3: DP table initialization
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // Step 4: Fill DP table for increasing interval lengths
        for (int len = k; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;

                // Try splitting into two parts with step (k-1)
                for (int m = i; m < j; m += (k - 1)) {
                    dp[i][j] = min(dp[i][j], dp[i][m] + dp[m + 1][j]);
                }

                // If we can merge into one pile, add the sum of stones
                if ((len - 1) % (k - 1) == 0) {
                    dp[i][j] += prefix[j + 1] - prefix[i];
                }
            }
        }

        // Step 5: Answer is dp[0][n-1]
        return dp[0][n - 1];
    }
};

// ---------------------------
// Driver code for testing
// ---------------------------
int main() {
    Solution sol;

    vector<int> stones1 = {1, 2, 3};
    int k1 = 2;
    cout << "Input: [1,2,3], k=2 -> Output: " << sol.mergeStones(stones1, k1) << endl;

    vector<int> stones2 = {1, 5, 3, 2, 4};
    int k2 = 2;
    cout << "Input: [1,5,3,2,4], k=2 -> Output: " << sol.mergeStones(stones2, k2) << endl;

    vector<int> stones3 = {1, 5, 3, 2, 4};
    int k3 = 4;
    cout << "Input: [1,5,3,2,4], k=4 -> Output: " << sol.mergeStones(stones3, k3) << endl;

    return 0;
}
