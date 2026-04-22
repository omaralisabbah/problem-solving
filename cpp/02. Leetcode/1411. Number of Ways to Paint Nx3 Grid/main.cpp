#include <bits/stdc++.h>
using namespace std;

/**
 * Problem:
 * Paint an n x 3 grid with 3 colors (Red, Yellow, Green) such that
 * no two adjacent cells (sharing a side) have the same color.
 *
 * Approach:
 * - Each row of 3 cells can be classified into two types:
 *   Type A: Uses exactly 2 colors (like R Y R). Count = 6.
 *   Type B: Uses all 3 colors (like R Y G). Count = 6.
 *
 * - Define DP states:
 *   a_k = number of ways up to row k with row k being Type A.
 *   b_k = number of ways up to row k with row k being Type B.
 *
 * - Recurrence:
 *   a_{k+1} = 3 * a_k + 2 * b_k
 *   b_{k+1} = 2 * a_k + 2 * b_k
 *
 * - Base case:
 *   a_1 = 6, b_1 = 6
 *
 * - Answer:
 *   total = (a_n + b_n) % MOD
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(1)
 */

class Solution {
public:
    int numOfWays(int n) {
        const int MOD = 1e9 + 7;
        
        long long a = 6; // Type A rows at row 1
        long long b = 6; // Type B rows at row 1
        
        for (int i = 2; i <= n; i++) {
            long long newA = (3 * a + 2 * b) % MOD;
            long long newB = (2 * a + 2 * b) % MOD;
            a = newA;
            b = newB;
        }
        
        return (a + b) % MOD;
    }
};

int main() {
    Solution sol;
    
    // Example 1
    int n1 = 1;
    cout << "Input: n = " << n1 << endl;
    cout << "Output: " << sol.numOfWays(n1) << endl;
    // Expected: 12
    
    cout << "----------------------" << endl;
    
    // Example 2
    int n2 = 5000;
    cout << "Input: n = " << n2 << endl;
    cout << "Output: " << sol.numOfWays(n2) << endl;
    // Expected: 30228214
    
    return 0;
}