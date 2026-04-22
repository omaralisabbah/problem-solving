/*
    Given a matrix mat[][] of size n*n, where each row and column is sorted in non-decreasing order. Find the kth smallest element in the matrix.

Examples:
Input: mat[][] = [[16, 28, 60, 64], k = 3
                [22, 41, 63, 91],
                [27, 50, 87, 93],
                [36, 78, 87, 94]]
Output: 27
Explanation: 27 is the 3rd smallest element.
Input: mat[][] = [[10, 20, 30, 40], k = 7
                [15, 25, 35, 45],
                [24, 29, 37, 48],
                [32, 33, 39, 50]] 
Output: 30
Explanation: 30 is the 7th smallest element.
Constraints:
1 ≤ n ≤ 500
1 ≤ mat[i][j] ≤ 104
1 ≤ k ≤ n*n

*/
#include <bits/stdc++.h>
using namespace std;

/**
 * Problem:
 * Given a matrix of size n*n where each row and column is sorted in non-decreasing order,
 * find the kth smallest element in the matrix.
 *
 * Approach:
 * - Use a Min-Heap (priority_queue with greater comparator).
 * - Each row is sorted, so the smallest element of each row is at column 0.
 * - Push the first element of each row into the heap along with its row and column indices.
 * - Pop the smallest element from the heap k times.
 *   - Each time we pop, we push the next element in the same row (if it exists).
 * - The kth popped element is our answer.
 *
 * Complexity:
 * - Time: O(k * log n) because each push/pop operation costs log n and we do it k times.
 * - Space: O(n) for the heap (at most one element per row).
 */

class Solution {
public:
    int kthSmallest(vector<vector<int>> &mat, int k) {
        int n = mat.size();

        // Min-heap storing {value, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minHeap;

        // Step 1: Push the first element of each row into the heap
        for (int i = 0; i < n; i++) {
            minHeap.push({mat[i][0], i, 0});
        }

        int ans = -1;

        // Step 2: Extract min k times
        for (int count = 0; count < k; count++) {
            auto top = minHeap.top();
            minHeap.pop();

            ans = top[0]; // Current smallest element
            int r = top[1], c = top[2];

            // Step 3: Push the next element in the same row (if exists)
            if (c + 1 < n) {
                minHeap.push({mat[r][c + 1], r, c + 1});
            }
        }

        return ans; // kth smallest element
    }
};

// -------------------------
// Example Usage
// -------------------------
int main() {
    Solution sol;

    vector<vector<int>> mat1 = {
        {16, 28, 60, 64},
        {22, 41, 63, 91},
        {27, 50, 87, 93},
        {36, 78, 87, 94}
    };
    int k1 = 3;
    cout << "Example 1: " << sol.kthSmallest(mat1, k1) << endl; // Output: 27

    vector<vector<int>> mat2 = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {24, 29, 37, 48},
        {32, 33, 39, 50}
    };
    int k2 = 7;
    cout << "Example 2: " << sol.kthSmallest(mat2, k2) << endl; // Output: 30

    return 0;
}
