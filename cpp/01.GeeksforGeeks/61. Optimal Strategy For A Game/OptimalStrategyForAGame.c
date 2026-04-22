/*
    You are given an integer array arr[] of size n(even). The array elements represent n coins of values v1, v2, ....vn.
You play against an opponent in an alternating way. In each turn, a player selects either the first or last coin from the row, removes it from the row permanently, and receives the coin's value.
You need to determine the maximum possible amount of money you can win if you go first.
Note: Both the players are playing optimally.

Examples:

Input: arr[] = [5, 3, 7, 10]
Output: 15
Explanation: The user collects the maximum value as 15(10 + 5). It is guaranteed that we cannot get more than 15 by any possible moves.

Input: arr[] = [8, 15, 3, 7]
Output: 22
Explanation: The user collects the maximum value as 22(7 + 15). It is guaranteed that we cannot get more than 22 by any possible moves.

Constraints:
2 <= n <= 103
1 <= arr[i] <= 106


Got it! This is the classic Optimal Strategy for a Game problem, often solved using Dynamic Programming. The key idea: since both players play optimally, you must anticipate the opponent’s moves and maximize your guaranteed winnings.
🔑 Approach

    Let dp[i][j] represent the maximum amount you can collect from subarray arr[i...j].

    Choices:

        Pick arr[i]: Then opponent chooses optimally between arr[i+1] and arr[j]. So you get:

arr[i]+min⁡(dp[i+2][j],dp[i+1][j−1])arr[i] + \min(dp[i+2][j], dp[i+1][j-1])

    Pick arr[j]: Then opponent chooses optimally between arr[i] and arr[j-1]. So you get:

arr[j]+min⁡(dp[i+1][j−1],dp[i][j−2])arr[j] + \min(dp[i+1][j-1], dp[i][j-2])

    Transition:

dp[i][j]=max⁡(choice1,choice2)dp[i][j] = \max(\text{choice1}, \text{choice2})

    Base cases:

        If only one coin: dp[i][i] = arr[i]

        If two coins: dp[i][i+1] = max(arr[i], arr[i+1])
*/

/*
    Problem:
    You are given an integer array arr[] of size n (even).
    The array elements represent n coins of values v1, v2, ....vn.
    You play against an opponent in an alternating way. In each turn,
    a player selects either the first or last coin from the row,
    removes it permanently, and receives the coin's value.
    Both players play optimally.

    Task:
    Determine the maximum possible amount of money you can win if you go first.

    Approach:
    - This is the "Optimal Strategy for a Game" problem.
    - Use Dynamic Programming to anticipate the opponent's moves.
    - Define dp[i][j] as the maximum amount you can collect from subarray arr[i...j].
    - Choices:
        1. Pick arr[i]:
           Opponent then chooses optimally between arr[i+1] and arr[j].
           You get: arr[i] + min(dp[i+2][j], dp[i+1][j-1])
        2. Pick arr[j]:
           Opponent then chooses optimally between arr[i] and arr[j-1].
           You get: arr[j] + min(dp[i+1][j-1], dp[i][j-2])
        dp[i][j] = max(choice1, choice2)
    - Base cases:
        * dp[i][i] = arr[i] (only one coin)
        * dp[i][i+1] = max(arr[i], arr[i+1]) (two coins)

    Complexity:
    - Time: O(n^2)
    - Space: O(n^2)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int maximumAmount(vector<int> &arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        
        // Base cases
        for (int i = 0; i < n; i++) {
            dp[i][i] = arr[i];
        }
        for (int i = 0; i < n-1; i++) {
            dp[i][i+1] = max(arr[i], arr[i+1]);
        }
        
        // Fill DP table for larger subarrays
        for (int len = 2; len < n; len++) {
            for (int i = 0; i + len < n; i++) {
                int j = i + len;
                
                int pickLeft = arr[i] + min(dp[i+2][j], dp[i+1][j-1]);
                int pickRight = arr[j] + min(dp[i+1][j-1], dp[i][j-2]);
                
                dp[i][j] = max(pickLeft, pickRight);
            }
        }
        
        return dp[0][n-1];
    }
};

// Driver code for testing
int main() {
    Solution sol;
    
    vector<int> arr1 = {5, 3, 7, 10};
    cout << "Maximum amount (arr1): " << sol.maximumAmount(arr1) << endl; // Expected 15
    
    vector<int> arr2 = {8, 15, 3, 7};
    cout << "Maximum amount (arr2): " << sol.maximumAmount(arr2) << endl; // Expected 22
    
    return 0;
}
