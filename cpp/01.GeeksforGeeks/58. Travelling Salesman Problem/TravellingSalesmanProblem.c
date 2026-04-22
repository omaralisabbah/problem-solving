/*

    Given a 2d matrix cost[][] of size n where cost[i][j] denotes the cost of moving from city i to city j. Your task is to complete a tour from city 0 (0-based index) to all other cities such that you visit each city exactly once and then at the end come back to city 0 at minimum cost.

Examples:

Input: cost[][] = [[0, 111], 
                [112, 0]]
Output: 223
Explanation: We can visit 0->1->0 and cost = 111 + 112.

Input: cost[][] = [[0, 1000, 5000],
                [5000, 0, 1000],
                [1000, 5000, 0]]
Output: 3000
Explanation: We can visit 0->1->2->0 and cost = 1000 + 1000 + 1000 = 3000

Constraints:
1 ≤ cost.size() ≤ 15
0 ≤ cost[i][j] ≤ 104


Great problem — this is the Traveling Salesman Problem (TSP) in disguise. We need to find the minimum cost Hamiltonian cycle starting from city 0. Since n ≤ 15, we can solve it using Dynamic Programming with Bitmasking.
🔑 Approach

    Use DP + Bitmask:

        dp[mask][i] = minimum cost to reach city i having visited all cities in mask.

        mask is a bitmask representing visited cities.

    Transition:

        From dp[mask][i], try to go to a new city j not in mask.

        Update:

dp[mask∣(1<<j)][j]=min⁡(dp[mask∣(1<<j)][j],dp[mask][i]+cost[i][j])dp[mask | (1 << j)][j] = \min(dp[mask | (1 << j)][j], dp[mask][i] + cost[i][j])

    Base case:

        Start at city 0: dp[1][0] = 0 (only city 0 visited).

    Answer:

        After visiting all cities (mask = (1<<n)-1), return:

min⁡i(dp[(1<<n)−1][i]+cost[i][0])\min_{i} \big(dp[(1<<n)-1][i] + cost[i][0]\big)

    This ensures we return to city 0.


*/

#include <bits/stdc++.h>
using namespace std;

/*
 * Traveling Salesman Problem (TSP) using Dynamic Programming + Bitmasking
 *
 * Problem:
 * - We are given a cost matrix cost[][] where cost[i][j] is the cost of traveling
 *   from city i to city j.
 * - We must start at city 0, visit every city exactly once, and return to city 0
 *   with minimum total cost.
 *
 * Approach:
 * - Use DP with bitmasking:
 *   dp[mask][i] = minimum cost to reach city i having visited all cities in 'mask'.
 *   - mask is a bitmask representing visited cities (1 = visited).
 *   - Transition: try moving from city i to city j if j is not visited.
 *   - Base case: dp[1][0] = 0 (only city 0 visited).
 * - Final answer: min(dp[(1<<n)-1][i] + cost[i][0]) for all i != 0.
 *
 * Complexity:
 * - Time: O(n^2 * 2^n)
 * - Space: O(n * 2^n)
 * - Works for n ≤ 15 (as per constraints).
 */

class Solution {
public:
    int tsp(vector<vector<int>>& cost) {
        int n = cost.size();
        
        // Edge case: only one city
        if (n == 1) return 0;
        
        int N = 1 << n;  // total subsets of cities
        const int INF = 1e9;
        
        // dp[mask][i] = minimum cost to reach city i with visited set 'mask'
        vector<vector<int>> dp(N, vector<int>(n, INF));
        
        // Base case: starting at city 0 with only city 0 visited
        dp[1][0] = 0;
        
        // Iterate over all subsets of cities
        for (int mask = 1; mask < N; mask++) {
            for (int i = 0; i < n; i++) {
                if (!(mask & (1 << i))) continue; // city i not visited in this mask
                
                // Try moving to a new city j
                for (int j = 0; j < n; j++) {
                    if (mask & (1 << j)) continue; // city j already visited
                    int nextMask = mask | (1 << j);
                    dp[nextMask][j] = min(dp[nextMask][j], dp[mask][i] + cost[i][j]);
                }
            }
        }
        
        // Final step: return to city 0
        int ans = INF;
        for (int i = 1; i < n; i++) {
            ans = min(ans, dp[N-1][i] + cost[i][0]);
        }
        
        return ans;
    }
};

// Example usage
int main() {
    Solution sol;
    
    vector<vector<int>> cost1 = {{0, 111}, {112, 0}};
    cout << "Minimum tour cost (Example 1): " << sol.tsp(cost1) << endl; // Expected: 223
    
    vector<vector<int>> cost2 = {{0, 1000, 5000},
                                 {5000, 0, 1000},
                                 {1000, 5000, 0}};
    cout << "Minimum tour cost (Example 2): " << sol.tsp(cost2) << endl; // Expected: 3000
    
    vector<vector<int>> cost3 = {{0}};
    cout << "Minimum tour cost (Single city): " << sol.tsp(cost3) << endl; // Expected: 0
    
    return 0;
}
