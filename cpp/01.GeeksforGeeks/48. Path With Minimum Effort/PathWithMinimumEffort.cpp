/*
    You are given a 2D array mat[][], of size n*m. Your task is to find the minimum possible path cost from the top-left cell (0, 0) to the bottom-right cell (n-1, m-1) by moving up, down, left, or right between adjacent cells.

Note: The cost of a path is defined as the maximum absolute difference between the values of any two consecutive cells along that path.

Examples:

Input: mat[][] = [[7, 2, 6, 5],
               [3, 1, 10, 8]]
Output: 4
Explanation: The route of [7, 3, 1, 2, 6, 5, 8] has a minimum value of maximum absolute difference between any two consecutive cells in the route, i.e., 4.
   

Input: mat[][] = [[2, 2, 2, 1],
               [8, 1, 2, 7],
               [2, 2, 2, 8],
               [2, 1, 4, 7],
               [2, 2, 2, 2]]
Output: 0
Explanation: The route of [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2] has a minimum value of maximum absolute difference between any two consecutive cells in the route, i.e., 0.
    

Constraints:
1 ≤ n, m ≤ 100
0 ≤ mat[i][j] ≤ 106



Got it — this is a graph shortest path problem but with a twist: instead of summing weights, the path cost is defined as the maximum absolute difference between consecutive cells. We want to minimize that maximum difference.

This is essentially a minimax path problem. The standard approach is to use Dijkstra’s algorithm (or BFS with binary search) where the "distance" to a cell is the minimum possible maximum difference encountered so far.
🔑 Key Idea

    Each cell (i, j) is a node.

    The edge weight between (i, j) and (x, y) is abs(mat[i][j] - mat[x][y]).

    Path cost = maximum edge weight along the path.

    We want the path with the minimum possible maximum edge weight.

This can be solved using:

    Modified Dijkstra’s Algorithm:

        Instead of summing weights, we propagate the maximum edge weight seen so far.

        Use a priority queue to always expand the path with the smallest current maximum difference.

    Binary Search + BFS/DFS:

        Guess a maximum allowed difference mid.

        Check if there exists a path from (0,0) to (n-1,m-1) using only edges ≤ mid.

        Binary search over possible values.

Both work, but Dijkstra-style is cleaner.
*/

/*
    Problem:
    --------
    You are given a 2D array mat[][] of size n*m. 
    Your task is to find the minimum possible path cost from the top-left cell (0, 0) 
    to the bottom-right cell (n-1, m-1) by moving up, down, left, or right between adjacent cells.

    Path cost definition:
    ---------------------
    The cost of a path is defined as the maximum absolute difference between the values 
    of any two consecutive cells along that path.

    Approach:
    ---------
    - Treat the matrix as a graph where each cell is a node.
    - The edge weight between two adjacent cells is the absolute difference of their values.
    - We want the path that minimizes the maximum edge weight encountered.
    - This is a "minimax path" problem, solved using a modified Dijkstra’s algorithm:
        * Instead of summing weights, we propagate the maximum edge weight seen so far.
        * Use a priority queue to always expand the path with the smallest current maximum difference.
    - Time complexity: O(n * m * log(n * m))
    - Space complexity: O(n * m)

    Example:
    --------
    Input: [[7, 2, 6, 5],
            [3, 1, 10, 8]]
    Output: 4
    Explanation: Path [7, 3, 1, 2, 6, 5, 8] has differences [4,2,1,4,1,3], max = 4.

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minCostPath(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();

        // Min-heap storing {current path cost, x, y}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
        pq.push({0, 0, 0});

        // Distance matrix: minimum possible max-diff to reach (i,j)
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;

        // Directions: up, down, left, right
        int dirs[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

        while (!pq.empty()) {
            auto cur = pq.top(); pq.pop();
            int cost = cur[0], x = cur[1], y = cur[2];

            // If we reached the target, return the cost
            if (x == n-1 && y == m-1) return cost;

            // Skip outdated entries
            if (cost > dist[x][y]) continue;

            // Explore neighbors
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

                int edge = abs(mat[x][y] - mat[nx][ny]);
                int newCost = max(cost, edge);

                if (newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    pq.push({newCost, nx, ny});
                }
            }
        }

        return dist[n-1][m-1];
    }
};

// Driver code for testing
int main() {
    Solution sol;

    vector<vector<int>> mat1 = {{7, 2, 6, 5},
                                {3, 1, 10, 8}};
    cout << "Output: " << sol.minCostPath(mat1) << endl; // Expected: 4

    vector<vector<int>> mat2 = {{2, 2, 2, 1},
                                {8, 1, 2, 7},
                                {2, 2, 2, 8},
                                {2, 1, 4, 7},
                                {2, 2, 2, 2}};
    cout << "Output: " << sol.minCostPath(mat2) << endl; // Expected: 0

    return 0;
}
