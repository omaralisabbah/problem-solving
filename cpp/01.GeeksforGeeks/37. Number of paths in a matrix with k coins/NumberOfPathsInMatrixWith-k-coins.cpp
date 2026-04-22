/*
    You are given a matrix mat[][] of size n x m, where each of its cells contains some coins. Count the number of ways to collect exactly k coins while moving from the top left cell of the matrix to the bottom right cell.
From a cell (i, j), you can only move to cell (i+1, j) or (i, j+1).

Note: It is guaranteed that the answer will not exceed 32-bit integer limits.

Examples:

Input: k = 12, mat[] = [[1, 2, 3],
                      [4, 6, 5],
                      [3, 2, 1]]
Output: 2
Explanation: There are 2 possible paths with exactly 12 coins, (1 + 2 + 6 + 2 + 1) and (1 + 2 + 3 + 5 + 1).

Input: k = 16, mat[] = [[1, 2, 3], 
                      [4, 6, 5], 
                      [9, 8, 7]]
Output: 0 
Explanation: There are no possible paths that lead to sum = 16.

Constraints:
1 ≤ k ≤ 100
1 ≤ n, m ≤ 100
0 ≤ mat[i][j] ≤ 200

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Function to count the number of ways to collect exactly k coins
    int numberOfPath(vector<vector<int>>& mat, int k) {
        int n = mat.size(), m = mat[0].size();
        
        // Create a 3D DP table initialized to 0
        // dp[i][j][c] represents the number of ways to reach cell (i, j) with exactly c coins
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k + 1, 0)));
        
        // Base case: Start from (0, 0) with the number of coins mat[0][0]
        if (mat[0][0] <= k) {
            dp[0][0][mat[0][0]] = 1;
        }
        
        // Fill the DP table
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int coins = 0; coins <= k; ++coins) {
                    // If there are ways to reach (i, j) with 'coins' number of coins
                    if (dp[i][j][coins] > 0) {
                        // Move down to (i + 1, j) if within bounds
                        if (i + 1 < n && coins + mat[i + 1][j] <= k) {
                            dp[i + 1][j][coins + mat[i + 1][j]] += dp[i][j][coins];
                        }
                        // Move right to (i, j + 1) if within bounds
                        if (j + 1 < m && coins + mat[i][j + 1] <= k) {
                            dp[i][j + 1][coins + mat[i][j + 1]] += dp[i][j][coins];
                        }
                    }
                }
            }
        }
        
        // The result is the number of ways to reach the bottom-right corner with exactly k coins
        return dp[n - 1][m - 1][k];
    }
};

// Main function to test the solution
int main() {
    Solution solution;
    
    // Test case 1
    int k1 = 12;
    vector<vector<int>> mat1 = {{1, 2, 3}, 
                                 {4, 6, 5}, 
                                 {3, 2, 1}};
    cout << "Number of ways to collect " << k1 << " coins: " << solution.numberOfPath(mat1, k1) << endl;

    // Test case 2
    int k2 = 16;
    vector<vector<int>> mat2 = {{1, 2, 3}, 
                                 {4, 6, 5}, 
                                 {9, 8, 7}};
    cout << "Number of ways to collect " << k2 << " coins: " << solution.numberOfPath(mat2, k2) << endl;

    return 0;
}
