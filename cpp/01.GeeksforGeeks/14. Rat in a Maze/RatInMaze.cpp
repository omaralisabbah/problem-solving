/*
    Consider a rat placed at position (0, 0) in an n x n square matrix maze[][]. The rat's goal is to reach the destination at position (n-1, n-1). The rat can move in four possible directions: 'U'(up), 'D'(down), 'L' (left), 'R' (right).

The matrix contains only two possible values:

    0: A blocked cell through which the rat cannot travel.
    1: A free cell that the rat can pass through.

Your task is to find all possible paths the rat can take to reach the destination, starting from (0, 0) and ending at (n-1, n-1), under the condition that the rat cannot revisit any cell along the same path. Furthermore, the rat can only move to adjacent cells that are within the bounds of the matrix and not blocked.
If no path exists, return an empty list.

Note: Return the final result vector in lexicographically smallest order.

Examples:

Input: maze[][] = [[1, 0, 0, 0], [1, 1, 0, 1], [1, 1, 0, 0], [0, 1, 1, 1]]
Output: ["DDRDRR", "DRDDRR"]
Explanation: The rat can reach the destination at (3, 3) from (0, 0) by two paths - DRDDRR and DDRDRR, when printed in sorted order we get DDRDRR DRDDRR.

Input: maze[][] = [[1, 0], [1, 0]]
Output: []
Explanation: No path exists as the destination cell (1, 1) is blocked.

Input: maze[][] = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
Output: ["DDRR", "RRDD"]
Explanation: The rat has two possible paths to reach the destination: DDRR and RRDD.

Constraints:
2 ≤ n ≤ 5
0 ≤ maze[i][j] ≤ 1


To solve this problem, the goal is to find all possible paths the rat can take to reach from the top-left corner (0, 0) to the bottom-right corner (n-1, n-1) in a given maze, where the rat can move up ('U'), down ('D'), left ('L'), or right ('R'). The maze is represented as an n x n grid, where:

1 indicates a free cell (the rat can move through).

0 indicates a blocked cell (the rat cannot move through).

We need to ensure that:

The rat only moves within the maze bounds and through free cells.

The rat does not revisit any cell in the same path.

We find all paths, and return them in lexicographically sorted order.

Approach:

We'll use backtracking to explore all possible paths the rat can take, starting from (0, 0) and trying all four possible directions (up, down, left, and right).

The main steps involved are:

Recursive exploration: Starting from (0, 0), recursively move to adjacent cells if they are within bounds and not blocked.

Backtracking: When a valid move is made, mark the cell as visited and continue the exploration. Once we reach the destination (n-1, n-1), add the path to the result list.

Unmarking cells: After exploring a cell and backtracking, unmark it so that it can be used in other paths.

Sorting the paths: Since the problem specifies that the result should be in lexicographically smallest order, we'll sort the paths before returning them.

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> result;  // To store all the paths

    // Helper function to perform backtracking
    void solve(vector<vector<int>>& maze, int x, int y, string path, vector<vector<bool>>& visited) {
        int n = maze.size();
        
        // Base case: if we reach the destination
        if (x == n-1 && y == n-1) {
            result.push_back(path);
            return;
        }
        
        // Mark the current cell as visited
        visited[x][y] = true;
        
        // Directions in the order of lexicographical smallest path: D, L, R, U
        int dx[] = {1, 0, 0, -1};  // Down, Left, Right, Up
        int dy[] = {0, -1, 1, 0};
        char dir[] = {'D', 'L', 'R', 'U'};
        
        // Try all possible directions
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            // Check if the new position is within bounds, is a free cell, and not visited
            if (nx >= 0 && ny >= 0 && nx < n && ny < n && maze[nx][ny] == 1 && !visited[nx][ny]) {
                // Explore this direction by making a recursive call
                solve(maze, nx, ny, path + dir[i], visited);
            }
        }
        
        // Backtrack: unmark the current cell as visited
        visited[x][y] = false;
    }

    // Main function to find all the paths
    vector<string> ratInMaze(vector<vector<int>>& maze) {
        int n = maze.size();
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        // Start the backtracking process from (0, 0)
        if (maze[0][0] == 1) {
            solve(maze, 0, 0, "", visited);
        }
        
        // Sort the result lexicographically
        sort(result.begin(), result.end());
        
        return result;
    }
};

// Function to print the result
void printResult(const vector<string>& result) {
    if (result.empty()) {
        cout << "No path exists!" << endl;
    } else {
        for (const string& path : result) {
            cout << path << endl;
        }
    }
}

// Main function to run the program
int main() {
    Solution sol;

    // Test case 1
    vector<vector<int>> maze1 = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };
    vector<string> result1 = sol.ratInMaze(maze1);
    cout << "Paths for Test case 1: " << endl;
    printResult(result1);

    // Test case 2
    vector<vector<int>> maze2 = {
        {1, 0},
        {1, 0}
    };
    vector<string> result2 = sol.ratInMaze(maze2);
    cout << "\nPaths for Test case 2: " << endl;
    printResult(result2);

    // Test case 3
    vector<vector<int>> maze3 = {
        {1, 1, 1},
        {1, 0, 1},
        {1, 1, 1}
    };
    vector<string> result3 = sol.ratInMaze(maze3);
    cout << "\nPaths for Test case 3: " << endl;
    printResult(result3);

    return 0;
}