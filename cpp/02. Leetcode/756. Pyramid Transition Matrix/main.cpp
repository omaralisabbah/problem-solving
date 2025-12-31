#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>

using namespace std;

/**
 * Solution for the Pyramid Transition Matrix problem.
 * 
 * Approach:
 * 1. Pre-process 'allowed' strings into a 2D adjacency matrix for O(1) lookup.
 * 2. Use DFS/Backtracking to build the next row level-by-level.
 * 3. Use memoization (unordered_map) to store results of previously seen rows 
 *    to avoid redundant recursive paths.
 */
class Solution {
    // adj[i][j] stores a bitmask of characters that can sit on top of 
    // characters i and j. Bit k is set if character (k + 'A') is allowed.
    int adj[7][7]; 
    
    // Memoization table: maps a row string to whether it can reach the top.
    unordered_map<string, bool> memo;

public:
    bool pyramidTransition(string bottom, vector<string>& allowed) {
        // Reset state for each test case
        memset(adj, 0, sizeof(adj));
        memo.clear();

        // Populate the lookup table
        for (const string& s : allowed) {
            int u = s[0] - 'A';
            int v = s[1] - 'A';
            int top = s[2] - 'A';
            adj[u][v] |= (1 << top);
        }

        return canReachTop(bottom);
    }

private:
    /**
     * Recursive function to determine if a given row can build a full pyramid.
     */
    bool canReachTop(string row) {
        // Base case: If the row has only one block, the pyramid is complete.
        if (row.length() == 1) return true;
        
        // Memoization check
        if (memo.count(row)) return memo[row];

        string nextRow = "";
        return memo[row] = generateNextRow(row, nextRow, 0);
    }

    /**
     * Helper backtracking function to generate all possible strings for the level above.
     * @param currentRow: The base row we are building upon.
     * @param nextRow: The row currently being constructed for the level above.
     * @param index: The current position in currentRow we are evaluating.
     */
    bool generateNextRow(const string& currentRow, string& nextRow, int index) {
        // If we've processed all pairs in the current row, we've finished the next row.
        // Now, we check if this newly completed nextRow can reach the top.
        if (index == currentRow.length() - 1) {
            return canReachTop(nextRow);
        }

        int left = currentRow[index] - 'A';
        int right = currentRow[index + 1] - 'A';
        int possibilities = adj[left][right];

        // If no blocks are allowed to be placed on these two, this path fails.
        if (possibilities == 0) return false;

        // Try every character that is allowed to be on top of (left, right)
        for (int i = 0; i < 7; ++i) {
            if (possibilities & (1 << i)) {
                nextRow.push_back((char)('A' + i));
                
                // Recurse to fill the next position in the current row being built
                if (generateNextRow(currentRow, nextRow, index + 1)) return true;
                
                // Backtrack
                nextRow.pop_back();
            }
        }

        return false;
    }
};
