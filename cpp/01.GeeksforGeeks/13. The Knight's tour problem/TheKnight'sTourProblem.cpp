/*
    You are given an integer n, there is a n × n chessboard with a Knight starting at the top-left corner (0, 0). Your task is to determine a valid Knight's Tour, where the Knight visits every square exactly once, following the standard movement rules of a chess Knight (two steps in one direction and one step perpendicular), for example if a Knight is placed at cell (2, 2), in one move it can move to any of the following cells: (4, 3), (4, 1), (0, 3), (0, 1), (3, 4), (3, 0), (1, 4) and (1, 0).

You have to return the order in which each cell is visited. If a solution exists, return the sequence of numbers (starting from 0) representing the order of visited squares. If no solution is possible, return an empty list.

Note: You can return any valid ordering, if it is correct the driver code will print true else it will print false.

Examples:

Input: n = 5
Output: true
Explanation: A possible Knight's Tour in a 5x5 chessboard is given below where Each number represents the step at which the Knight visits that cell, starting from (0, 0) as step 0.
[[0, 11, 2, 17, 20],
 [3, 16, 19, 12, 7],
 [10, 1, 6, 21, 18],
 [15, 4, 23, 8, 13], 
 [24, 9, 14, 5, 22]]

Input: n = 4
Output: true
Explanation: For n = 4, it is not possible for a valid Knight's Tour so you have to return [].

Constraints:
1 ≤ n ≤ 6

To solve the Knight's Tour problem on an n x n chessboard, we need to implement a backtracking solution where a knight starts at the top-left corner (0, 0) and tries to visit every square exactly once by following the knight's movement rules.

Knight’s Movement:

A knight moves in an "L" shape: it can move:

Two squares in one direction and one square perpendicular to it, or

One square in one direction and two squares perpendicular to it.

The possible moves from any position (x, y) are:

(x + 2, y + 1), (x + 2, y - 1), (x - 2, y + 1), (x - 2, y - 1)

(x + 1, y + 2), (x + 1, y - 2), (x - 1, y + 2), (x - 1, y - 2)

Problem Breakdown:

Backtracking: The idea is to start from (0, 0) and explore all possible moves in a depth-first manner. We mark the current position and attempt to move to the next available position.

Valid Moves: A move is valid if:

The new position is within the bounds of the board.

The new position hasn't been visited yet.

Stopping Condition: If we have visited all n * n cells, we've found a valid Knight's Tour.

Approach:

We'll maintain a matrix visited to track the visited positions.

We'll store the sequence of moves (i.e., the order in which the knight visits the cells).

The backtracking function will attempt to move to each of the 8 possible directions from the current cell.

If we can't complete the tour, we backtrack and try another path.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    // Possible moves a knight can make from any position
    vector<int> dx = {2, 2, -2, -2, 1, 1, -1, -1};
    vector<int> dy = {1, -1, 1, -1, 2, -2, 2, -2};
    
    // Function to check if a move is within bounds and the cell has not been visited
    bool isSafe(int x, int y, int n, vector<vector<int>>& board) {
        return (x >= 0 && y >= 0 && x < n && y < n && board[x][y] == -1);
    }

    // Backtracking function to solve the knight's tour problem
    bool solveKnightTour(int n, vector<vector<int>>& board, int x, int y, int moveCount) {
        // If all squares are visited, return true
        if (moveCount == n * n) {
            return true;
        }

        // Try all possible knight moves
        for (int i = 0; i < 8; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isSafe(newX, newY, n, board)) {
                // Mark the square as visited
                board[newX][newY] = moveCount;

                // Recur to place knight on the next square
                if (solveKnightTour(n, board, newX, newY, moveCount + 1)) {
                    return true;
                }

                // Backtrack: unmark the square if no solution is found
                board[newX][newY] = -1;
            }
        }

        // No valid move found, return false
        return false;
    }

    // Main function to return the Knight's Tour
    vector<vector<int>> knightTour(int n) {
        vector<vector<int>> board(n, vector<int>(n, -1)); // Initialize board with -1 (unvisited)
        board[0][0] = 0; // Start the tour from the top-left corner (0, 0)
        
        if (solveKnightTour(n, board, 0, 0, 1)) {
            return board;
        } else {
            return {}; // If no solution is found, return an empty list
        }
    }
};

// Function to print the board
void printBoard(const vector<vector<int>>& board) {
    if (board.empty()) {
        cout << "No solution exists!" << endl;
    } else {
        for (const auto& row : board) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << endl;
        }
    }
}

int main() {
    Solution sol;

    // Test case 1: n = 5
    int n1 = 5;
    vector<vector<int>> result1 = sol.knightTour(n1);
    cout << "Knight's Tour for n = " << n1 << ":\n";
    printBoard(result1);

    // Test case 2: n = 4
    int n2 = 4;
    vector<vector<int>> result2 = sol.knightTour(n2);
    cout << "\nKnight's Tour for n = " << n2 << ":\n";
    printBoard(result2);

    return 0;
}

