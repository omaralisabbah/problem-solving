/*
    You are given n walls arranged in a row, and each wall must be painted using one of the k available colors. The cost of painting ith wall with jth color is given by costs[i][j]. Your task is to determine the minimum total cost required to paint all the walls in such a way that no two adjacent walls share the same color. If it is impossible to paint the walls under this condition, you must return -1.

Examples:

Input: n = 4, k = 3,
costs[][] = [[1, 5, 7],
           [5, 8, 4],
           [3, 2, 9],
           [1, 2, 4]]

Output: 8
Explanation:
Paint wall 0 with color 0. Cost = 1
Paint wall 1 with color 2. Cost = 4
Paint wall 2 with color 1. Cost = 2
Paint wall 3 with color 0. Cost = 1
Total Cost = 1 + 4 + 2 + 1 = 8

Input: n = 5, k = 1,
costs[][] = [[5],
           [4],
           [9],
           [2],
           [1]]
Output: -1
Explanation: It is not possible to color all the walls under the given conditions.

Constraints:
0 ≤ n  ≤ 103
0 ≤ k  ≤ 103
1 ≤ costs[i][j]  ≤ 105

Got it 👍 — this is a dynamic programming problem where we need to minimize the painting cost while ensuring no two adjacent walls have the same color. Let’s break it down and then I’ll give you the C++ implementation.
🔑 Key Observations

    If k=1k = 1 and n>1n > 1, it’s impossible to paint adjacent walls differently → return -1.

    We need to track the minimum cost up to each wall for each color.

    For each wall ii, the cost of painting it with color jj depends on:

dp[i][j]=costs[i][j]+min⁡c≠j(dp[i−1][c])dp[i][j] = costs[i][j] + \min_{c \neq j}(dp[i-1][c])

    To optimize, instead of scanning all colors for each wall, we can keep track of:

        The minimum cost and its color from the previous wall.

        The second minimum cost (in case the current color matches the min color).

This reduces complexity from O(n⋅k2)O(n \cdot k^2) to O(n⋅k)O(n \cdot k).

*/

/*
    Problem:
    You are given n walls arranged in a row, and each wall must be painted using one of the k available colors.
    The cost of painting ith wall with jth color is given by costs[i][j].
    Your task is to determine the minimum total cost required to paint all the walls in such a way that
    no two adjacent walls share the same color. If it is impossible to paint the walls under this condition,
    you must return -1.

    Approach:
    - If k == 1 and n > 1, it's impossible to paint adjacent walls differently → return -1.
    - Use Dynamic Programming (DP):
        dp[i][j] = minimum cost to paint up to wall i with color j.
        Transition:
            dp[i][j] = costs[i][j] + min(dp[i-1][c]) for all c != j
    - To optimize, instead of scanning all colors for each wall, track:
        * min1 = smallest cost from previous wall
        * min2 = second smallest cost from previous wall
        * idx1 = color index of min1
      Then:
        If current color == idx1 → use min2
        Else → use min1
    - This reduces complexity from O(n * k^2) to O(n * k).

    Time Complexity: O(n * k)
    Space Complexity: O(k)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>> &costs) {
        int n = costs.size();
        if (n == 0) return 0;
        int k = costs[0].size();

        // If only one color and more than one wall, impossible
        if (k == 1) {
            return (n == 1) ? costs[0][0] : -1;
        }

        // dp arrays: prev = previous wall costs, curr = current wall costs
        vector<int> prev(k, 0), curr(k, 0);

        // Initialize with first wall costs
        for (int j = 0; j < k; j++) {
            prev[j] = costs[0][j];
        }

        // Process each wall
        for (int i = 1; i < n; i++) {
            // Find min1 and min2 in prev row
            int min1 = INT_MAX, min2 = INT_MAX, idx1 = -1;
            for (int j = 0; j < k; j++) {
                if (prev[j] < min1) {
                    min2 = min1;
                    min1 = prev[j];
                    idx1 = j;
                } else if (prev[j] < min2) {
                    min2 = prev[j];
                }
            }

            // Update current row
            for (int j = 0; j < k; j++) {
                if (j == idx1) {
                    curr[j] = costs[i][j] + min2;
                } else {
                    curr[j] = costs[i][j] + min1;
                }
            }

            prev = curr; // Move to next wall
        }

        // Answer is min of last row
        return *min_element(prev.begin(), prev.end());
    }
};

// Driver code for testing
int main() {
    Solution sol;

    // Example 1
    vector<vector<int>> costs1 = {
        {1, 5, 7},
        {5, 8, 4},
        {3, 2, 9},
        {1, 2, 4}
    };
    cout << "Minimum cost (Example 1): " << sol.minCost(costs1) << endl; // Expected: 8

    // Example 2
    vector<vector<int>> costs2 = {
        {5},
        {4},
        {9},
        {2},
        {1}
    };
    cout << "Minimum cost (Example 2): " << sol.minCost(costs2) << endl; // Expected: -1

    return 0;
}
