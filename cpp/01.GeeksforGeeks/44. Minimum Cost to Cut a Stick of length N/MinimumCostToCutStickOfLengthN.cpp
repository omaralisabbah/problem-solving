/*
    You are given a wooden stick of length n, labeled from 0 to n. You are also given an integer array cuts[], where each element cuts[i] represents a position along the stick at which you can make a cut.
Each cut costs an amount equal to the length of the stick being cut at that moment. After performing a cut, the stick is divided into two smaller sticks.
You can perform the cuts in any order. Your task is to determine the minimum total cost required to perform all the cuts.

Example:

Input: n = 10, cuts[] = [2, 4, 7]
Output: 20
Explanation: 
    
If we cut the stick in the order [4, 2, 7], the cost will be 10 + 4 + 6 = 20, which is the minimum total cost.

Input: n = 8, cuts[] = [1, 6, 3, 5]
Output: 19
Explanation: If we cut the stick in the order [3, 6, 1, 5], the cost will be 8 + 5 + 3 + 3 = 19, which is the minimum total cost.

Constraints:
2 ≤ n ≤ 106
1 ≤ cuts[i] ≤ n - 1
1 ≤ cuts.size() ≤ 100
*/

/*
    Problem:
    --------
    You are given a wooden stick of length n, labeled from 0 to n.
    You are also given an integer array cuts[], where each element cuts[i] 
    represents a position along the stick at which you can make a cut.

    Each cut costs an amount equal to the length of the stick being cut at that moment.
    After performing a cut, the stick is divided into two smaller sticks.
    You can perform the cuts in any order. Your task is to determine the minimum 
    total cost required to perform all the cuts.

    Example:
    --------
    Input: n = 10, cuts[] = [2, 4, 7]
    Output: 20
    Explanation: 
        If we cut the stick in the order [4, 2, 7], 
        the cost will be 10 + 4 + 6 = 20, which is the minimum total cost.

    Constraints:
    ------------
    2 ≤ n ≤ 10^6
    1 ≤ cuts[i] ≤ n - 1
    1 ≤ cuts.size() ≤ 100

    Approach:
    ---------
    - This is a classic Dynamic Programming on intervals problem.
    - Add boundaries (0 and n) to the cuts array and sort it.
    - Define dp[i][j] = minimum cost to cut the stick between cuts[i] and cuts[j].
    - Transition:
        dp[i][j] = min( dp[i][k] + dp[k][j] + (cuts[j] - cuts[i]) ) 
        for all k in (i, j).
    - Answer = dp[0][m-1], where m = cuts.size() after adding boundaries.
    - Time complexity: O(m^3), where m = cuts.size() + 2 (≤ 102).
      This is efficient enough.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCutCost(int n, vector<int>& cuts) {
        // Step 1: Add boundaries (0 and n)
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());

        int m = cuts.size();
        // dp[i][j] = minimum cost to cut stick between cuts[i] and cuts[j]
        vector<vector<int>> dp(m, vector<int>(m, 0));

        // Step 2: Fill DP table by increasing interval length
        for (int len = 2; len < m; ++len) { // interval length
            for (int i = 0; i + len < m; ++i) {
                int j = i + len;
                dp[i][j] = INT_MAX;
                // Try all possible cuts between i and j
                for (int k = i + 1; k < j; ++k) {
                    dp[i][j] = min(dp[i][j], 
                                   dp[i][k] + dp[k][j] + (cuts[j] - cuts[i]));
                }
            }
        }

        // Final answer: minimum cost to cut whole stick [0, n]
        return dp[0][m-1];
    }
};

// Driver code for testing
int main() {
    Solution sol;

    // Example 1
    int n1 = 10;
    vector<int> cuts1 = {2, 4, 7};
    cout << "Minimum cost for n=10, cuts=[2,4,7]: "
         << sol.minCutCost(n1, cuts1) << endl;

    // Example 2
    int n2 = 8;
    vector<int> cuts2 = {1, 6, 3, 5};
    cout << "Minimum cost for n=8, cuts=[1,6,3,5]: "
         << sol.minCutCost(n2, cuts2) << endl;

    return 0;
}
