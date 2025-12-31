#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    /**
     * Finds the last day it is possible to cross from top to bottom.
     * Time Complexity: O(R * C * log(R * C))
     * Space Complexity: O(R * C)
     */
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int left = 1, right = cells.size();
        int lastPossibleDay = 0;

        // Binary Search for the maximum day
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (canWalk(row, col, cells, mid)) {
                lastPossibleDay = mid; // Crossing is possible, try a later day
                left = mid + 1;
            } else {
                right = mid - 1; // Crossing is blocked, try an earlier day
            }
        }
        return lastPossibleDay;
    }

private:
    /**
     * Helper to verify if a path exists from top to bottom on a given day.
     */
    bool canWalk(int row, int col, const vector<vector<int>>& cells, int day) {
        // grid[r][c] = 1 represents water, 0 represents land
        vector<vector<int>> grid(row, vector<int>(col, 0));
        
        // Flood the grid up to the specified day (using 0-based indexing)
        for (int i = 0; i < day; ++i) {
            grid[cells[i][0] - 1][cells[i][1] - 1] = 1;
        }

        queue<pair<int, int>> q;
        // Start BFS from all available land cells in the top row
        for (int c = 0; c < col; ++c) {
            if (grid[0][c] == 0) {
                q.push({0, c});
                grid[0][c] = 1; // Mark as visited to save space
            }
        }

        // Direction vectors for cardinal movement (Up, Down, Left, Right)
        int dr[] = {0, 0, 1, -1};
        int dc[] = {1, -1, 0, 0};

        while (!q.empty()) {
            pair<int, int> curr = q.front();
            q.pop();
            int r = curr.first;
            int c = curr.second;

            // If we reached any cell in the bottom row, path found
            if (r == row - 1) return true;

            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];

                // Check boundaries and if the next cell is land
                if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 0) {
                    grid[nr][nc] = 1; // Mark visited
                    q.push({nr, nc});
                }
            }
        }
        return false;
    }
};
