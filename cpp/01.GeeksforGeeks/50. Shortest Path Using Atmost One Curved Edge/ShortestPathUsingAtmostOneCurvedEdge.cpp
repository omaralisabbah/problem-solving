/*

    Given an undirected, connected graph with V vertices numbered from 0 to V-1 and E double-edges, represented as a 2D array edges[][]. Each double-edge is represented by a tuple (x, y, w1, w2), which indicates that there are two edges between vertices x and y: a straight edge with weight w1 and a curved edge with weight w2.

You are given two vertices a and b and you have to go from a to b through a series of edges such that in the entire path, you can use at most 1 curved edge. Your task is to find the shortest path from a to b satisfying the above condition.
If no such path exists that satisfies this restriction, return -1.

Note: It is guaranteed that the shortest path value will fit in a 32-bit integer.

Examples:

Input: V = 4, E = 4, a = 1, b = 3, edges[][] = [[0, 1, 1, 4], [0, 2, 2, 4], [0, 3, 3, 1], [1, 3, 6, 5]]

Output: 2
Explanation:
We can follow the path 1 -> 0 -> 3, this gives a distance of 1+3 = 4 if we follow all straight paths. But we can take the curved path  from 0 -> 3, which costs 1. This will result in a cost of 1 + 1 = 2.

Input: V = 2, E = 1, a = 0, b = 1, edges[][] = [[0, 1, 4, 1]]

Output: 1
Explanation:
Take the curved path from 0 to 1 which costs 1. 

Constraints:
1 ≤ V ≤ 106
0 ≤ E ≤ 106
0 ≤ a, b ≤ V - 1
0 ≤ edges[i][0], edges[i][1] ≤ V-1
0 ≤ edges[i][2], edges[i][3] ≤ 104




Got it — this is a nice graph problem with a twist: you can use at most one curved edge. The trick is to compute shortest paths using only straight edges first, then try inserting exactly one curved edge and see if it improves the path. Let me walk you through the approach and then give you the code.
🔑 Key Idea

    Build two adjacency lists:

        One for straight edges (weight = w1).

        One for curved edges (weight = w2).

    Run Dijkstra’s algorithm twice:

        From a using only straight edges → distA[].

        From b using only straight edges → distB[].

    This gives the shortest distance from a to every node and from b to every node using only straight edges.

    Now, consider using one curved edge (x, y, w2):

        Path option 1: a → ... → x →(curved)→ y → ... → b Cost = distA[x] + w2 + distB[y]

        Path option 2: a → ... → y →(curved)→ x → ... → b Cost = distA[y] + w2 + distB[x]

    Take the minimum of all such options.

    Answer = min(straight path from a to b, best curved path). If unreachable, return -1.
*/

/*
    Problem:
    --------
    Given an undirected, connected graph with V vertices (0 to V-1) and E double-edges.
    Each double-edge is represented as (x, y, w1, w2):
        - Straight edge between x and y with weight w1
        - Curved edge between x and y with weight w2

    Task:
    -----
    Find the shortest path from vertex a to vertex b such that
    you can use at most ONE curved edge in the entire path.
    If no such path exists, return -1.

    Approach:
    ---------
    1. Build adjacency list using only straight edges (w1).
    2. Run Dijkstra’s algorithm twice:
       - From source 'a' → distA[]
       - From destination 'b' → distB[]
       These give shortest distances using only straight edges.
    3. Consider each curved edge (x, y, w2):
       - Path option 1: a → ... → x → curved(x,y) → y → ... → b
         Cost = distA[x] + w2 + distB[y]
       - Path option 2: a → ... → y → curved(y,x) → x → ... → b
         Cost = distA[y] + w2 + distB[x]
       Take minimum of all such options.
    4. Answer = min(straight path distA[b], best curved path).
       If unreachable, return -1.

    Complexity:
    -----------
    - Dijkstra: O((V + E) log V)
    - Works efficiently for up to 10^6 vertices and edges.

    Example:
    --------
    Input:
        V = 4, E = 4, a = 1, b = 3
        edges = [[0,1,1,4], [0,2,2,4], [0,3,3,1], [1,3,6,5]]

    Output:
        2
    Explanation:
        Straight path 1→0→3 = 1+3 = 4
        Curved path 1→0→(curved)→3 = 1+1 = 2
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Dijkstra’s algorithm for shortest paths using straight edges
    vector<long long> dijkstra(int V, int src, vector<vector<pair<int,int>>> &adj) {
        vector<long long> dist(V, LLONG_MAX);
        dist[src] = 0;
        priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
        pq.push({0, src});
        
        while(!pq.empty()) {
            auto [d,u] = pq.top(); pq.pop();
            if(d > dist[u]) continue;
            for(auto &edge : adj[u]) {
                int v = edge.first, w = edge.second;
                if(dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }
    
    int shortestPath(int V, int a, int b, vector<vector<int>> &edges) {
        // Build adjacency list for straight edges
        vector<vector<pair<int,int>>> adj(V);
        for(auto &e : edges) {
            int x = e[0], y = e[1], w1 = e[2];
            adj[x].push_back({y, w1});
            adj[y].push_back({x, w1});
        }
        
        // Shortest distances using only straight edges
        vector<long long> distA = dijkstra(V, a, adj);
        vector<long long> distB = dijkstra(V, b, adj);
        
        long long ans = distA[b]; // straight path
        
        // Try using one curved edge
        for(auto &e : edges) {
            int x = e[0], y = e[1], w2 = e[3];
            if(distA[x] != LLONG_MAX && distB[y] != LLONG_MAX)
                ans = min(ans, distA[x] + w2 + distB[y]);
            if(distA[y] != LLONG_MAX && distB[x] != LLONG_MAX)
                ans = min(ans, distA[y] + w2 + distB[x]);
        }
        
        return (ans == LLONG_MAX ? -1 : (int)ans);
    }
};

// ------------------ DRIVER CODE ------------------
int main() {
    Solution sol;
    
    // Example 1
    int V = 4, a = 1, b = 3;
    vector<vector<int>> edges = {{0,1,1,4}, {0,2,2,4}, {0,3,3,1}, {1,3,6,5}};
    cout << sol.shortestPath(V, a, b, edges) << endl; // Output: 2
    
    // Example 2
    V = 2; a = 0; b = 1;
    edges = {{0,1,4,1}};
    cout << sol.shortestPath(V, a, b, edges) << endl; // Output: 1
    
    return 0;
}
