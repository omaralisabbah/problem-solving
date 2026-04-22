/*
    Given a directed acyclic graph (DAG) with V vertices numbered from 0 to V-1 and E edges, represented as a 2D array edges[][], where each entry edges[i] = [u, v] denotes a directed edge from vertex u to vertex v, find the maximum number of additional edges that can be added to the graph without forming any cycles.

Note: The resulting graph must remain a DAG, meaning that adding any further edge would not create a cycle.

Examples:

Input: V = 3, E = 2, edges[][] = [[0, 1], [1, 2]]
Output: 1
Explanation: The given DAG allows one more edge, 0 -> 2, which keeps the structure acyclic. Adding anything else would create a cycle.

Input: V = 4, E = 4, edges[][] = [[0, 1], [0, 2], [1, 2], [2, 3]]
Output: 2
Explanation: Two additional edges (0 -> 3, 1 -> 3) can be added without forming cycles.

Constraints:
1 ≤ V ≤ 103
0 ≤ E ≤ (V*(V-1))/2
0 ≤ edges[i][0], edges[i][1] < V
*/

#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Maximum Additional Edges in a DAG
    ------------------------------------------
    Given a DAG, find the maximum number of edges that can be added 
    without forming a cycle.
*/

class Solution {
public:
    int maxEdgesToAdd(int V, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list
        vector<vector<int>> adj(V);
        vector<int> indegree(V, 0);

        // Store existing edges for quick lookup
        vector<vector<bool>> hasEdge(V, vector<bool>(V, false));

        for (auto &e : edges) {
            int u = e[0], v = e[1];
            adj[u].push_back(v);
            indegree[v]++;
            hasEdge[u][v] = true;
        }

        // Step 2: Topological sort (Kahn's algorithm)
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) q.push(i);
        }

        vector<int> topo;  // topological order
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topo.push_back(u);
            for (int v : adj[u]) {
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }

        // Step 3: Count how many additional edges we can add
        int count = 0;

        // For each pair (i, j) in topological order
        for (int i = 0; i < V; i++) {
            for (int j = i + 1; j < V; j++) {
                int from = topo[i];
                int to = topo[j];
                // If edge does not already exist, we can add it
                if (!hasEdge[from][to]) {
                    count++;
                }
            }
        }

        return count;
    }
};

// ---------------------------
// Driver Code for Testing
// ---------------------------
int main() {
    Solution sol;

    int V1 = 3;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}};
    cout << "Example 1: " << sol.maxEdgesToAdd(V1, edges1) << endl;
    // Expected: 1 (edge 0 -> 2)

    int V2 = 4;
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {1, 2}, {2, 3}};
    cout << "Example 2: " << sol.maxEdgesToAdd(V2, edges2) << endl;
    // Expected: 2 (edges 0->3, 1->3)

    int V3 = 4;
    vector<vector<int>> edges3 = {};
    cout << "Example 3: " << sol.maxEdgesToAdd(V3, edges3) << endl;
    // Expected: 6 (fully acyclic with no edges yet)

    return 0;
}
