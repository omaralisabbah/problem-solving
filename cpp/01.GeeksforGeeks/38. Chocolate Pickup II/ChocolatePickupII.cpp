/*
    You are given a square matrix mat[][] of size n × n, where each cell represents either a blocked cell or a cell containing some chocolates. If mat[i][j] equals -1, then the cell is blocked and cannot be visited. Otherwise, mat[i][j] represents the number of chocolates present in that cell.
The task is to determine the maximum number of chocolates a robot can collected by starting from the top-left cell (0, 0), moving to the bottom-right cell (n-1, n-1), and then returning back to (0, 0).
While moving from (0, 0) to (n-1, n-1), the robot can move only in the right (i, j+1) or downward (i+1, j) directions. On the return journey from (n-1, n-1) to (0, 0), it can move only in the left (i, j-1) or upward (i-1, j) directions.

Note: After collecting chocolates from a cell (i, j), that cell becomes empty, meaning mat[i][j] becomes 0 for next visit. If there is no valid path from (0, 0) to (n-1, n-1) or for the return trip, the result should be 0.

Example:

Input: mat[][] = [[0, 1, -1], 
                [1, 1, -1], 
                [1, 1, 2]]
Output: 7
Explanation:
  
One of the optimal paths is to move from (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2) while going forward, and then from (2,2) -> (2,1) -> (1,1) -> (0,1) -> (0,0) while coming back. The total number of chocolates collected is 7.

Input: mat[][] = [[1, 1, 0], 
               [1, 1, 1], 
               [0, 1, 1]]
Output: 7
Explanation:
  
One of the optimal paths is to move from (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2) while going forward, and then from (2,2) -> (1,2) -> (1,1) -> (0,1) -> (0,0) while coming back. The total number of chocolates collected is 7.

Input: mat[][] = [[1, 0, -1],
                [2, -1, -1],
                [1, -1, 3]]
Output: 0
Explanation:
  
It is impossible to reach the bottom-right cell (2,2) from (0,0) because every route is blocked. Since the destination cannot be reached, the total chocolates collected is 0.

Constraint:
1 ≤ n ≤ 50
-1 ≤ mat[i][j] ≤ 100



To solve this problem, we can model it as a two-person pathfinding problem using dynamic programming.
The idea is to simulate two robots starting from (0,0) and reaching (n-1,n-1) simultaneously,
collecting chocolates along the way. This approach cleverly handles both the forward and return trips in one pass.




To solve this problem, we need to compute the maximum number of chocolates that a robot can collect while traveling from the top-left cell (0, 0) to the bottom-right cell (n-1, n-1) and then back from (n-1, n-1) to (0, 0). The key points are:

Forward Journey: From (0, 0) to (n-1, n-1), the robot can only move right (i, j+1) or down (i+1, j).

Return Journey: From (n-1, n-1) to (0, 0), the robot can only move left (i, j-1) or up (i-1, j).

Chocolates Collected: While traversing through any cell, the robot collects chocolates (the value in that cell), and the cell becomes empty (set to 0 after the visit).

Blocked Cells: A cell with a value of -1 is blocked and cannot be visited.

Approach:

Dynamic Programming (DP):

We'll use a dynamic programming approach where we keep track of the maximum chocolates that can be collected at each step both during the forward journey and the return journey.

Forward DP:

We'll define a DP table dp1[i][j] where each cell holds the maximum chocolates collected up to the point (i, j) on the forward journey.

Return DP:

Similarly, we'll define another DP table dp2[i][j] for the return journey where each cell holds the maximum chocolates collected from (i, j) to (0, 0).

Final Calculation:

The final solution will be obtained by combining both the forward and return journeys. We need to consider all possible points where the robot can change its direction from forward to backward, and calculate the total chocolates collected.

Steps:

Forward DP Initialization:

dp1[0][0] = mat[0][0] (starting point).

For each subsequent cell, check if the cell is valid (not blocked) and update the value based on the previous reachable cells.

Return DP Initialization:

Start from the bottom-right corner (n-1, n-1) and fill in the DP table in reverse order.

Combining Results:

After filling both DP tables, we compute the maximum chocolates collected by considering all possible ways to reach a cell (i, j) and return back to (i, j).
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int n;
    vector<vector<vector<int>>> dp;

    int helper(vector<vector<int>> &mat, int r1, int c1, int r2) {
        int c2 = r1 + c1 - r2;
        if (r1 >= n || c1 >= n || r2 >= n || c2 >= n ||
            mat[r1][c1] == -1 || mat[r2][c2] == -1)
            return INT_MIN;

        if (r1 == n - 1 && c1 == n - 1)
            return mat[r1][c1];

        if (dp[r1][c1][r2] != -1)
            return dp[r1][c1][r2];

        int chocolates = mat[r1][c1];
        if (r1 != r2 || c1 != c2)
            chocolates += mat[r2][c2];

        int temp = max({
            helper(mat, r1 + 1, c1, r2 + 1),
            helper(mat, r1, c1 + 1, r2),
            helper(mat, r1 + 1, c1, r2),
            helper(mat, r1, c1 + 1, r2 + 1)
        });

        return dp[r1][c1][r2] = chocolates + temp;
    }

    int chocolatePickup(vector<vector<int>> &mat) {
        n = mat.size();
        dp = vector<vector<vector<int>>>(n, vector<vector<int>>(n, vector<int>(n, -1)));
        int result = helper(mat, 0, 0, 0);
        return max(0, result);
    }
};

int main() {
    Solution sol;

    vector<vector<int>> mat1 = {
        {0, 1, -1},
        {1, 1, -1},
        {1, 1, 2}
    };

    vector<vector<int>> mat2 = {
        {1, 1, 0},
        {1, 1, 1},
        {0, 1, 1}
    };

    vector<vector<int>> mat3 = {
        {1, 0, -1},
        {2, -1, -1},
        {1, -1, 3}
    };

    cout << "Output 1: " << sol.chocolatePickup(mat1) << endl; // Expected: 7
    cout << "Output 2: " << sol.chocolatePickup(mat2) << endl; // Expected: 7
    cout << "Output 3: " << sol.chocolatePickup(mat3) << endl; // Expected: 0

    return 0;
}
