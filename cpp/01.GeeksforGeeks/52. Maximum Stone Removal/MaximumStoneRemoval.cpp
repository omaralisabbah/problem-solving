/*

    Given an 2D array of non-negative integers stones[][] where stones[i] = [xi , yi] represents the location of the ith stone on a 2D plane, the task is to return the maximum possible number of stones that you can remove.

A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.

Note: Each coordinate point may have at most one stone.

Examples:

Input: stones[][] = [[0, 0], [0, 1], [1, 0], [1, 2], [2, 1], [2, 2]]
Output: 5
Explanation:
      
One way to remove 5 stones is as follows:
1. Remove stone [2, 2] because it shares the same row as [2, 1].
2. Remove stone [2, 1] because it shares the same column as [0, 1].
3. Remove stone [1, 2] because it shares the same row as [1, 0].
4. Remove stone [1, 0] because it shares the same column as [0, 0].
5. Remove stone [0, 1] because it shares the same row as [0, 0].
Stone [0, 0] cannot be removed since it does not share any row/column with another stone still on the plane.

Input: stones[][] = [[0, 0], [0, 2], [1, 1], [2, 0], [2, 2]]
Output: 3
Explanation:
     
One way to remove 3 stones is as follows:
1. Remove stone [2, 2] because it shares the same row as [2, 0].
2. Remove stone [2, 0] because it shares the same column as [0, 0].
3. Remove stone [0, 2] because it shares the same row as [0, 0].
Stones [0, 0] and [1, 1] cannot be removed since they do not share any row/column with another stone still on the plane.

Constraints:
1 ≤ stones.size() ≤ 1000
0 ≤ xi, yi ≤ 104
No two stones are at same position.






Great problem! 🚀 This is a classic graph connectivity / union-find problem. Let me break it down clearly:
🔑 Key Insight

    Stones can be removed if they share a row or column with another stone.

    This essentially forms connected components in a graph:

        Each stone is a node.

        An edge exists between two stones if they share the same row or column.

    In each connected component of size k, we can remove k - 1 stones (leaving one stone behind).

    Therefore, the answer is:

maxRemovable=totalStones−numberOfConnectedComponents\text{maxRemovable} = \text{totalStones} - \text{numberOfConnectedComponents}
🛠️ Approach

    Build a graph where stones are connected if they share row or column.

    Use DFS/BFS or Union-Find (Disjoint Set Union) to count connected components.

    Return n - components.  

*/

/*
    Problem:
    --------
    Given a 2D array of non-negative integers stones[][] where stones[i] = [xi , yi]
    represents the location of the ith stone on a 2D plane, return the maximum possible
    number of stones that can be removed.

    Rule:
    -----
    A stone can be removed if it shares either the same row or the same column
    as another stone that has not been removed.

    Key Insight:
    ------------
    - Stones form connected components (graph).
    - Within each connected component of size k, we can remove (k - 1) stones.
    - Therefore, answer = total stones - number of connected components.

    Approach:
    ---------
    1. Treat each stone as a node.
    2. Connect nodes if they share a row or column.
    3. Use DFS to count connected components.
    4. Return n - components.

    Complexity:
    -----------
    - Time: O(n^2) due to pairwise checks (acceptable for n ≤ 1000).
    - Space: O(n) for visited array.

    Example:
    --------
    Input: [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
    Output: 5
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Depth First Search to mark all stones in the same connected component
    void dfs(int idx, vector<vector<int>>& stones, vector<bool>& visited) {
        visited[idx] = true;
        for (int j = 0; j < stones.size(); j++) {
            if (!visited[j]) {
                // If same row or same column, they are connected
                if (stones[idx][0] == stones[j][0] || stones[idx][1] == stones[j][1]) {
                    dfs(j, stones, visited);
                }
            }
        }
    }

    int maxRemove(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<bool> visited(n, false);
        int components = 0;

        // Count connected components
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                components++;
                dfs(i, stones, visited);
            }
        }

        // Maximum stones removable = total stones - number of components
        return n - components;
    }
};

// Driver code for testing
int main() {
    Solution sol;

    vector<vector<int>> stones1 = {{0,0},{0,1},{1,0},{1,2},{2,1},{2,2}};
    cout << "Output: " << sol.maxRemove(stones1) << endl; // Expected 5

    vector<vector<int>> stones2 = {{0,0},{0,2},{1,1},{2,0},{2,2}};
    cout << "Output: " << sol.maxRemove(stones2) << endl; // Expected 3

    return 0;
}

