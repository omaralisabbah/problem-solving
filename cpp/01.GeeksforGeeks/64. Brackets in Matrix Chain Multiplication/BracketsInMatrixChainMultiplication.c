/*

    Given an array arr[] of length n used to denote the dimensions of a series of matrices such that the dimension of i'th matrix is arr[i] * arr[i+1]. There are a total of n-1 matrices. Find the most efficient way to multiply these matrices together. 
Your task is to return the string which is formed of A - Z (only Uppercase) denoting matrices & Brackets( "(" ")" ) denoting multiplication symbols. For example, if n = 11, the matrixes can be denoted as A - K as n <= 26 & multiplication of A and B is denoted as (AB).

NOTE:

    Each multiplication is denoted by putting open & closed brackets to the matrices multiplied & also, please note that the order of matrix multiplication matters, as matrix multiplication is non-commutative A*B != B*A
    As there can be multiple possible answers, the console would print "true" for the correct string and "false" for the incorrect string. You need to only return a string that performs a minimum number of multiplications.

Examples:

Input: arr[] = [40, 20, 30, 10, 30]
Output: true
Explanation: Let's divide this into matrix(only 4 are possible) [ [40, 20] -> A, [20, 30] -> B, [30, 10] -> C, [10, 30] -> D ]
First we perform multiplication of B & C -> (BC), then we multiply A to (BC) -> (A(BC)), then we multiply D to (A(BC)) -> ((A(BC))D)
So the solution returned the string ((A(BC))D), which performs minimum multiplications. The total number of multiplications are 20*30*10 + 40*20*10 + 40*10*30 = 26,000.

Input: arr[] = [10, 20, 30]
Output: true
Explanation: There is only one way to multiply two matrices: (AB): The cost for the multiplication will be 6000

Input: arr = [10, 20, 30, 40]
Output: true
Explanation: There are two possible ways to multiply three matrices:
((AB)C): The cost for the multiplication will be 18,000
(A(BC)): The cost for the multiplication will be 32,000
So the solution returned the string ((AB)C), which performs minimum multiplications.

Constraints:
2 ≤ arr.size() ≤ 50
1 ≤ arr[i] ≤ 100 

Great problem! This is the Matrix Chain Multiplication problem, a classic in dynamic programming. The goal is not only to compute the minimum number of scalar multiplications but also to reconstruct the optimal parenthesization (the string with A-Z and brackets).

Here’s how we solve it:
🔑 Steps to Solve

    Define matrices: If arr has length n, then there are n-1 matrices:

        Matrix A has dimensions arr[0] × arr[1]

        Matrix B has dimensions arr[1] × arr[2]

        … and so on.

    DP table for costs:

        dp[i][j] = minimum cost to multiply matrices from i to j.

        split[i][j] = index k where the optimal split occurs.

    Recurrence relation: For i < j:

dp[i][j]=min⁡i≤k<j(dp[i][k]+dp[k+1][j]+arr[i]⋅arr[k+1]⋅arr[j+1])dp[i][j] = \min_{i \leq k < j} \big(dp[i][k] + dp[k+1][j] + arr[i] \cdot arr[k+1] \cdot arr[j+1]\big)

This formula accounts for splitting between k and k+1.

    Reconstruction: Use split[i][j] to recursively build the parenthesization string:

        If i == j, return the matrix letter (e.g., A + i).

        Otherwise, return "(" + build(i, split[i][j]) + build(split[i][j]+1, j) + ")".
*/

/*
    Matrix Chain Multiplication Problem
    -----------------------------------
    Given an array arr[] of length n used to denote the dimensions of a series of matrices
    such that the dimension of i'th matrix is arr[i] * arr[i+1]. There are a total of n-1 matrices.
    The task is to find the most efficient way to multiply these matrices together.

    We must return a string denoting the optimal parenthesization using:
      - Letters A, B, C, ... to represent matrices
      - Parentheses "(" and ")" to represent multiplication order

    Example:
        Input: arr = [40, 20, 30, 10, 30]
        Output: ((A(BC))D)

    Approach:
    ---------
    1. Dynamic Programming is used to compute the minimum number of multiplications.
    2. dp[i][j] stores the minimum cost to multiply matrices from i to j.
    3. split[i][j] stores the index k where the optimal split occurs.
    4. Recurrence relation:
         dp[i][j] = min( dp[i][k] + dp[k+1][j] + arr[i] * arr[k+1] * arr[j+1] )
    5. After computing dp, reconstruct the parenthesization string using recursion.

    Time Complexity: O(n^3)
    Space Complexity: O(n^2)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    string matrixChainOrder(vector<int> &arr) {
        int n = arr.size();
        int m = n - 1; // number of matrices

        // dp[i][j] = minimum cost to multiply matrices from i to j
        vector<vector<int>> dp(m, vector<int>(m, 0));
        // split[i][j] = index k where optimal split occurs
        vector<vector<int>> split(m, vector<int>(m, -1));

        // Fill DP table for chains of length >= 2
        for (int len = 2; len <= m; len++) {
            for (int i = 0; i + len - 1 < m; i++) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    int cost = dp[i][k] + dp[k+1][j] + arr[i] * arr[k+1] * arr[j+1];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        split[i][j] = k;
                    }
                }
            }
        }

        // Recursive function to build parenthesization string
        function<string(int,int)> build = [&](int i, int j) {
            if (i == j) {
                return string(1, 'A' + i); // Matrix names: A, B, C, ...
            }
            int k = split[i][j];
            return "(" + build(i, k) + build(k+1, j) + ")";
        };

        return build(0, m-1);
    }
};

// Driver code for testing
int main() {
    Solution sol;

    vector<int> arr1 = {40, 20, 30, 10, 30};
    cout << sol.matrixChainOrder(arr1) << endl; // Expected: ((A(BC))D)

    vector<int> arr2 = {10, 20, 30};
    cout << sol.matrixChainOrder(arr2) << endl; // Expected: (AB)

    vector<int> arr3 = {10, 20, 30, 40};
    cout << sol.matrixChainOrder(arr3) << endl; // Expected: ((AB)C)

    return 0;
}
