/*
    Given an integer array height[] where height[i] represents the height of the i-th stair,
    a frog starts from the first stair and wants to reach the last stair. From any stair i,
    the frog has two options: it can either jump to the (i+1)th stair or the (i+2)th stair.
    
    The cost of a jump is the absolute difference in height between the two stairs.
    Determine the minimum total cost required for the frog to reach the last stair.

    Example:

    Input: heights[] = [20, 30, 40, 20]
    Output: 20
    Explanation:  Minimum cost is incurred when the frog jumps from stair 0 to 1 then 1 to 3:
    jump from stair 0 to 1: cost = |30 - 20| = 10
    jump from stair 1 to 3: cost = |20 - 30| = 10
    Total Cost = 10 + 10 = 20

    Input: heights[] = [30, 20, 50, 10, 40]
    Output: 30
    Explanation: Minimum cost will be incurred when frog jumps from stair 0 to 2 then 2 to 4:
    jump from stair 0 to 2: cost = |50 - 30| = 20
    jump from stair 2 to 4: cost = |40 - 50| = 10
    Total Cost = 20 + 10 = 30

    Constraints:
    1 ≤ height.size() ≤ 105
    0 ≤ height[i] ≤ 104
*/

#include <bits/stdc++.h>
using namespace std;

/*
    Frog Jump Problem
    -----------------
    Given an array `height` where height[i] represents the height of the i-th stair,
    a frog starts from the first stair (index 0) and wants to reach the last stair (index n-1).
    
    The frog can:
        - Jump to the next stair (i → i+1)
        - Jump over one stair (i → i+2)
    
    The cost of each jump is the absolute difference in heights.
    We must find the minimum total cost required to reach the last stair.
*/

class Solution {
  public:
    int minCost(vector<int>& height) {
        int n = height.size();

        // Base case: Only one stair — no cost to jump
        if (n == 1)
            return 0;

        // Base case: Cost to reach the 2nd stair (index 1)
        int prev2 = 0;                                   // dp[i-2]
        int prev1 = abs(height[1] - height[0]);          // dp[i-1]

        // Iterate through stairs from index 2 to n-1
        for (int i = 2; i < n; i++) {
            // Option 1: Jump from (i-1)
            int jumpOne = prev1 + abs(height[i] - height[i - 1]);

            // Option 2: Jump from (i-2)
            int jumpTwo = prev2 + abs(height[i] - height[i - 2]);

            // Choose the minimum cost to reach current stair
            int curr = min(jumpOne, jumpTwo);

            // Update dp variables for next iteration
            prev2 = prev1;
            prev1 = curr;
        }

        // `prev1` now holds the minimum cost to reach the last stair
        return prev1;
    }
};

// -----------------------------
// 🧪 Example Usage & Testing
// -----------------------------
int main() {
    Solution sol;

    vector<int> heights1 = {20, 30, 40, 20};
    cout << "Minimum Cost (Example 1): " << sol.minCost(heights1) << endl;
    // Expected Output: 20

    vector<int> heights2 = {30, 20, 50, 10, 40};
    cout << "Minimum Cost (Example 2): " << sol.minCost(heights2) << endl;
    // Expected Output: 30

    vector<int> heights3 = {10, 10};
    cout << "Minimum Cost (Example 3): " << sol.minCost(heights3) << endl;
    // Expected Output: 0

    return 0;
}
