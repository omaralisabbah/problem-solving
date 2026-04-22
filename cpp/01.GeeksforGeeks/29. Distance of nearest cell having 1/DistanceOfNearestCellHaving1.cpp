/*
    Given a binary grid[][], where each cell contains either 0 or 1, find the distance of the nearest 1 for every cell in the grid.
The distance between two cells (i1, j1)  and (i2, j2) is calculated as |i1 - i2| + |j1 - j2|. 
You need to return a matrix of the same size, where each cell (i, j) contains the minimum distance from grid[i][j] to the nearest cell having value 1.

Note: It is guaranteed that there is at least one cell with value 1 in the grid.

Examples

Input: grid[][] = [[0, 1, 1, 0], 
                [1, 1, 0, 0], 
                [0, 0, 1, 1]]
Output: [[1, 0, 0, 1], 
        [0, 0, 1, 1], 
        [1, 1, 0, 0]]
Explanation: The grid is -

- 0's at (0,0), (0,3), (1,2), (1,3), (2,0) and (2,1) are at a distance of 1 from 1's at (0,1), (0,2), (0,2), (2,3), (1,0) and (1,1) respectively.

Input: grid[][] = [[1, 0, 1], 
                [1, 1, 0], 
                [1, 0, 0]]
Output: [[0, 1, 0], 
        [0, 0, 1], 
        [0, 1, 2]]
Explanation: The grid is -

- 0's at (0,1), (1,2), (2,1) and (2,2) are at a  distance of 1, 1, 1 and 2 from 1's at (0,0), (0,2), (2,0) and (1,1) respectively.

Constraints:
1 ≤ grid.size() ≤ 200
1 ≤ grid[0].size() ≤ 200


To solve this problem efficiently, we can use Breadth-First Search (BFS) starting from all cells that contain 1. Here's the idea:

    Initialize a queue and push all cells with value 1 into it.

    Create a result matrix initialized with -1 or INT_MAX.

    Perform BFS from all 1s simultaneously, updating the distance for each 0 cell as we visit it.

This ensures that each cell gets the shortest distance to the nearest 1.


Why this works:

    BFS ensures that we explore all neighboring cells level by level.

    Starting from all 1s guarantees that each 0 gets the shortest path to any 1.



    Key Concepts Used

    Breadth-First Search (BFS): Efficient for finding shortest paths in unweighted grids.

    Manhattan Distance: Used to measure distance between grid cells.

    Multi-source BFS: Starts from all 1s simultaneously to ensure minimal distance propagation.
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/*
    Problem:
    Given a binary grid where each cell contains either 0 or 1, compute a matrix of the same size
    where each cell contains the distance to the nearest cell with value 1.

    Distance is calculated using Manhattan distance: |i1 - i2| + |j1 - j2|
*/

class Solution {
public:
    /*
        Function: nearest
        ------------------
        Computes the minimum distance from each cell to the nearest cell containing 1.

        Parameters:
            grid - a 2D vector of integers (0s and 1s)

        Returns:
            A 2D vector of integers representing the minimum distances
    */
    vector<vector<int>> nearest(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        // Initialize the result matrix with -1 (unvisited)
        vector<vector<int>> dist(rows, vector<int>(cols, -1));

        // Queue for BFS traversal
        queue<pair<int, int>> q;

        // Step 1: Enqueue all cells with value 1 and set their distance to 0
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // Step 2: Define directions for moving up, down, left, right
        vector<int> dx = {-1, 1, 0, 0};
        vector<int> dy = {0, 0, -1, 1};

        // Step 3: Perform BFS to update distances
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (int d = 0; d < 4; ++d) {
                int nx = x + dx[d];
                int ny = y + dy[d];

                // Check bounds and if the cell is unvisited
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols && dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }

        return dist;
    }
};

/*
    Function: printMatrix
    ---------------------
    Utility function to print a 2D matrix.

    Parameters:
        matrix - a 2D vector of integers
*/
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

/*
    Main function to demonstrate the solution
*/
int main() {
    Solution sol;

    // Example 1
    vector<vector<int>> grid1 = {
        {0, 1, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1}
    };

    cout << "Input Grid 1:\n";
    printMatrix(grid1);

    vector<vector<int>> result1 = sol.nearest(grid1);
    cout << "\nOutput Grid 1 (Distances):\n";
    printMatrix(result1);

    // Example 2
    vector<vector<int>> grid2 = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 0, 0}
    };

    cout << "\nInput Grid 2:\n";
    printMatrix(grid2);

    vector<vector<int>> result2 = sol.nearest(grid2);
    cout << "\nOutput Grid 2 (Distances):\n";
    printMatrix(result2);

    return 0;
}
