/*
    You are given an undirected weighted graph with V vertices numbered from 0 to V-1 and E edges, represented as a 2D array edges[][], where edges[i] = [ui, vi, timei] means that there is an undirected edge between nodes ui and vi that takes timei minutes to reach.
Your task is to return in how many ways you can travel from node 0 to node V - 1 in the shortest amount of time.

Examples:

Input: V = 4, edges[][] = [[0, 1, 2], [1, 2, 3], [0, 3, 5], [1, 3, 3], [2, 3, 4]]
    
Output: 2
Explanation: The shortest path from 0 to 3 is 5.
Two ways to reach 3 in 5 minutes are:
0 -> 3
0 -> 1 -> 3

Input: V = 6, edges[][] = [[0, 2, 3], [0, 4, 2], [0, 5, 7], [2, 3, 1], [2, 5, 5], [5, 3, 3], [5, 1, 4], [1, 4, 1], [4, 5, 5]]
    
Output: 4
Explanation: The shortest path from 0 to 5 is 7.
Four ways to reach 5 in 7 minutes are:
0 -> 5
0 -> 4 -> 5
0 -> 4 -> 1 -> 5
0 -> 2 -> 3 -> 5

Constraints:
1 ≤ V ≤ 200
V - 1 ≤ edges.size() ≤ V * (V - 1) / 2
0 ≤ ui, vi ≤ V - 1
1 ≤ timei ≤ 105
ui != vi
*/

#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    Given an undirected weighted graph with V vertices (0 to V-1) and E edges,
    count the number of distinct shortest paths from node 0 to node V-1.

    Approach:
    - Use Dijkstra's algorithm to compute shortest distances from node 0.
    - Maintain an array `ways[]` where ways[u] = number of shortest paths to reach node u.
    - Relaxation rules:
        * If a shorter path to v is found, update dist[v] and set ways[v] = ways[u].
        * If another path with equal shortest distance is found, add ways[u] to ways[v].
    - At the end, ways[V-1] gives the number of shortest paths to the destination.
*/

class Solution {
public:
    int countPaths(int V, vector<vector<int>>& edges) {
        // Step 1: Build adjacency list
        vector<vector<pair<int,int>>> adj(V);
        for (auto &e : edges) {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // undirected graph
        }

        // Step 2: Initialize distance and ways arrays
        vector<long long> dist(V, LLONG_MAX); // shortest distance to each node
        vector<long long> ways(V, 0);         // number of shortest paths to each node
        dist[0] = 0;
        ways[0] = 1;

        // Step 3: Min-heap for Dijkstra (distance, node)
        using P = pair<long long,int>;
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, 0});

        // Step 4: Dijkstra's algorithm
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue; // skip outdated entry

            for (auto &[v, w] : adj[u]) {
                // Case 1: Found a shorter path to v
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    ways[v] = ways[u]; // inherit path count
                    pq.push({dist[v], v});
                }
                // Case 2: Found another shortest path to v
                else if (dist[v] == dist[u] + w) {
                    ways[v] += ways[u];
                }
            }
        }

        // Step 5: Return number of shortest paths to destination
        return (int)ways[V-1];
    }
};

// --------------------
// Example usage
// --------------------
int main() {
    Solution sol;

    int V1 = 4;
    vector<vector<int>> edges1 = {{0,1,2},{1,2,3},{0,3,5},{1,3,3},{2,3,4}};
    cout << sol.countPaths(V1, edges1) << endl; // Output: 2

    int V2 = 6;
    vector<vector<int>> edges2 = {
        {0,2,3},{0,4,2},{0,5,7},{2,3,1},{2,5,5},
        {5,3,3},{5,1,4},{1,4,1},{4,5,5}
    };
    cout << sol.countPaths(V2, edges2) << endl; // Output: 4

    return 0;
}
