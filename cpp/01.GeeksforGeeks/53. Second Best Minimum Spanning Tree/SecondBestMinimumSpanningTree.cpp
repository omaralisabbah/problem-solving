/*
    Given an undirected graph of V vertices numbered from (0 to V-1) and E edges represented by a 2D array edges[][],
    where each edges[i] contains three integers [u, v, w], representing an undirected edge from u to v, having weight w.
    
    Your task is to find the weight of the second best minimum spanning tree of the given graph.
    A second best MST is defined as the minimum-weight spanning tree whose total weight is strictly greater than the weight of the minimum spanning tree.

    Note: If no such second best MST exists, return -1. 

    Examples:

    Input: V = 5, E = 7, edges[][] = [[0, 1, 4], [0, 2, 3], [1, 2, 1], [1, 3, 5], [2, 4, 10], [2, 3, 7], [3, 4, 2]]
    Output: 12
    Explanation:
    

    Input: V = 5, E = 4, edges[][] = [[0, 1, 2], [1, 2, 3], [2, 3, 4], [3, 4, 5]] 
    Output: -1
    Explanation: No second best MST exists for this graph.
    

    Constraints:
    1 ≤ V ≤ 100
    V-1 ≤ E ≤ V*(V-1)/2
    0 ≤ edges[i][2] ≤ 103
*/

/*
    Program: Second Best Minimum Spanning Tree (MST)
    ------------------------------------------------
    Given an undirected weighted graph with V vertices and E edges,
    this program computes the weight of the "second best" MST.

    A second best MST is defined as the minimum spanning tree whose
    total weight is strictly greater than the weight of the MST.

    Approach:
    1. Build the MST using Kruskal's algorithm.
    2. Record the MST weight and the set of edges used.
    3. For each edge in the MST, try to rebuild a spanning tree
       while excluding that edge (rerun Kruskal).
       - If the graph is still connected, compute the new weight.
       - Track the smallest weight strictly greater than MST.
    4. Return that value, or -1 if no second MST exists.

    Complexity:
    - Kruskal runs in O(E log E).
    - We rerun Kruskal up to V-1 times (for each MST edge).
    - With V ≤ 100 and E ≤ V*(V-1)/2, this is efficient enough.

    Input format (example):
    -----------------------
    V
    E
    u v w   (E lines of edges)

    Example:
    5
    7
    0 1 4
    0 2 3
    1 2 1
    1 3 5
    2 4 10
    2 3 7
    3 4 2

    Output:
    12
*/

#include <bits/stdc++.h>
using namespace std;

// Disjoint Set Union (Union-Find) structure
struct DSU {
    vector<int> parent, rank;
    DSU(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rank[a] < rank[b]) swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b]) rank[a]++;
        return true;
    }
};

class Solution {
public:
    int secondMST(int V, vector<vector<int>> &edges) {
        // Prepare edges as (weight, u, v, index)
        struct Edge { int w, u, v, idx; };
        vector<Edge> es;
        for (int i = 0; i < (int)edges.size(); ++i)
            es.push_back({edges[i][2], edges[i][0], edges[i][1], i});
        sort(es.begin(), es.end(), [](const Edge& a, const Edge& b){ return a.w < b.w; });

        // Build MST
        DSU dsu(V);
        int mstWeight = 0;
        vector<int> mstEdgeIdx;
        for (auto &e : es) {
            if (dsu.unite(e.u, e.v)) {
                mstWeight += e.w;
                mstEdgeIdx.push_back(e.idx);
            }
        }

        // Check connectivity
        int root = dsu.find(0);
        for (int i = 1; i < V; ++i)
            if (dsu.find(i) != root) return -1;

        // Try excluding each MST edge
        int secondBest = INT_MAX;
        for (int bannedIdx : mstEdgeIdx) {
            DSU cur(V);
            int total = 0, taken = 0;
            for (auto &e : es) {
                if (e.idx == bannedIdx) continue; // forbid this MST edge
                if (cur.unite(e.u, e.v)) {
                    total += e.w;
                    taken++;
                    if (taken == V-1) break;
                }
            }
            if (taken == V-1 && total > mstWeight) {
                secondBest = min(secondBest, total);
            }
        }

        return (secondBest == INT_MAX ? -1 : secondBest);
    }
};

// Driver code
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int V, E;
    cin >> V >> E;
    vector<vector<int>> edges(E, vector<int>(3));
    for (int i = 0; i < E; i++) {
        cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    Solution sol;
    cout << sol.secondMST(V, edges) << "\n";
    return 0;
}
