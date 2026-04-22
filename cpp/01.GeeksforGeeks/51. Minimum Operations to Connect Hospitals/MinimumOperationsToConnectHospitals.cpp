/*

    You are given an undirected network of V hospitals numbered from 0 to V - 1, represented as a 2D array edges[][], where each element edges[i] = [u, v] denotes a direct connection between hospital u and hospital v.
In one operation, you are allowed to remove any existing link and reconnect it between two hospitals that are currently not directly or indirectly connected.

Your task is to determine the minimum number of operations required to make sure that all hospitals become connected, either directly or indirectly, using the given links.

Note: If it is impossible to connect all hospitals into a single network, return -1.

Examples:

Input: V = 4, E = 3, edges[][] = [[0, 1], [0, 2], [1, 2]]
Output: 1
Explanation: Remove the connection between hospitals 1 and 2 and connect the hospitals 1 and 3.

Input: V = 5, E = 4, edges[][] = [[0, 1], [0, 2], [2, 3], [3, 4]]
Output: 0
Explanation: All hospitals are already connected directly or indirectly. No rearrangement of connections is required.

Constraints:
1 ≤ V ≤ 103
0 ≤ E ≤ V*(V-1)/2
0 ≤ edges[i][0], edges[i][1] < V



Got it — this is a graph connectivity problem. Let’s break it down clearly:
🔎 Problem Understanding

    We have V hospitals (nodes) and E connections (edges).

    We want to connect all hospitals into one connected component.

    Allowed operation: remove an existing edge and reconnect it between two hospitals that are currently in different components.

    If impossible, return -1.

✅ Key Observations

    To connect V nodes into one connected component, we need at least V - 1 edges.

        If E < V - 1, impossible → return -1.

    Count the number of connected components (C).

        To connect them, we need at least C - 1 edges.

    If we have enough edges (E ≥ V - 1), we can rearrange redundant edges (extra edges forming cycles) to connect components.

        Answer = C - 1.

🛠️ Approach

    Build adjacency list from edges.

    Use DFS/BFS/Union-Find to count connected components.

    If E < V - 1 → return -1.

    Otherwise → return C - 1.
*/


#include <bits/stdc++.h>
using namespace std;

/*
 Problem:
 --------
 We are given V hospitals (nodes) and a list of edges representing direct connections.
 We want to connect all hospitals into one connected network.

 Allowed operation:
 - Remove an existing edge and reconnect it between two hospitals that are currently
   in different components.

 Goal:
 - Find the minimum number of operations required to connect all hospitals.
 - If impossible, return -1.

 Key Observations:
 -----------------
 1. To connect V nodes, we need at least V - 1 edges.
    -> If E < V - 1, impossible.
 2. Count the number of connected components (C).
    -> To connect them, we need C - 1 edges.
 3. If E >= V - 1, we can rearrange redundant edges to connect components.
    -> Answer = C - 1.

 Approach:
 ---------
 1. Build adjacency list from edges.
 2. Use DFS/BFS to count connected components.
 3. If E < V - 1, return -1.
 4. Otherwise, return C - 1.
*/

class Solution {
public:
    int minConnect(int V, vector<vector<int>>& edges) {
        int E = edges.size();

        // Step 1: Check if enough edges exist
        if (E < V - 1) return -1;

        // Step 2: Build adjacency list
        vector<vector<int>> adj(V);
        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        // Step 3: Count connected components using DFS
        vector<bool> visited(V, false);
        int components = 0;

        function<void(int)> dfs = [&](int u) {
            visited[u] = true;
            for (int v : adj[u]) {
                if (!visited[v]) dfs(v);
            }
        };

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                components++;
                dfs(i);
            }
        }

        // Step 4: Minimum operations = components - 1
        return components - 1;
    }
};

// Example usage
int main() {
    Solution sol;

    int V1 = 4;
    vector<vector<int>> edges1 = {{0,1},{0,2},{1,2}};
    cout << sol.minConnect(V1, edges1) << endl; // Output: 1

    int V2 = 5;
    vector<vector<int>> edges2 = {{0,1},{0,2},{2,3},{3,4}};
    cout << sol.minConnect(V2, edges2) << endl; // Output: 0

    return 0;
}
