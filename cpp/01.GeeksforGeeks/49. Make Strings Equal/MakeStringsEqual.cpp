/*

    Given two strings s and t, consisting of lowercase English letters. You are also given, a 2D array transform[][] of size n*2, where each entry [x, y] means that you are allowed to transform character x into character y and an array cost[], where cost[i] is the cost of transforming transform[i][0] into transform[i][1]. You can apply any transformation any number of times on either string.

Your task is to find the minimum total cost required to make the strings identical. If it is impossible to make the two strings identical using the available transformations, return -1.

Examples:

Input: s = "abcc", t = "bccc", transform[][] = [['a', 'b'], ['b', 'c'], ['c', 'a']], cost[] = [2, 1, 4]
Output: 3
Explanation: We can convert both strings into "bccc" with a cost of 3 using these operations:
transform at Position 0 in s: a -> b (cost 2)
transform at Position 1 in s: b -> c (cost 1)
Other characters already match.

Input: s = "az", t = "dc", transform[][] = [['a', 'b'], ['b', 'c'], ['c', 'd'], ['a', 'd'], ['z', 'c']], cost[] = [5, 3, 2, 50, 10]
Output: 20
Explanation: We can convert both strings into "dc" with a cost of 20 using these operations:
transform at Position 0 in s: a -> d by path a->b->c->d (cost 5+3+2=10)
transform at Position 1 in s: z -> c (cost 10)

Input: s = "xyz", t = "xzy", transform[][] = [['x', 'y'], ['x', 'z']], cost[] = [3, 3]
Output: -1
Explanation: It is not possible to make the two strings equal.

Constraints:
1 ≤ s.size() = t.size() ≤ 105
1 ≤ transform.size() = cost.size() ≤ 500
'a' ≤ transform[i][0], transform[i][1] ≤ 'z'
1 ≤ cost[i] ≤ 500

Great problem — this is essentially about finding the minimum transformation cost between characters using the given directed transformations. Let’s break it down and then I’ll provide a clean C++ solution.
🔑 Key Ideas

    Graph Representation

        Each character 'a'–'z' is a node (26 nodes total).

        Each transformation [x, y] with cost c is a directed edge x → y with weight c.

    All-Pairs Shortest Path

        Since transformations can be applied multiple times, we need the shortest path cost between any two characters.

        Use Floyd–Warshall (since only 26 nodes, O(26³) is trivial).

    Character Matching

        For each position i in strings s and t:

            If s[i] == t[i], cost = 0.

            Otherwise, we need to transform both into some common character c.

            The cost is dist[s[i]][c] + dist[t[i]][c].

            Take the minimum over all possible c.

    Impossible Case

        If no valid transformation exists for some position, return -1.

*/

#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    --------
    Given two strings s and t (same length), and a set of allowed character transformations
    with associated costs, find the minimum total cost to make s and t identical.
    If impossible, return -1.

    Approach:
    ---------
    1. Represent each lowercase character ('a'–'z') as a node in a graph (26 nodes).
    2. Each transformation [x, y] with cost c is a directed edge x -> y with weight c.
    3. Use Floyd–Warshall to compute the shortest path cost between all pairs of characters.
       - This works because we may apply transformations multiple times.
       - Complexity: O(26^3), which is trivial.
    4. For each position i in s and t:
       - If s[i] == t[i], cost = 0.
       - Otherwise, try transforming both into some common character c.
         Cost = dist[s[i]][c] + dist[t[i]][c].
       - Take the minimum over all c.
       - If no valid transformation exists, return -1.
    5. Sum costs across all positions.

    Complexity:
    -----------
    - Floyd–Warshall: O(26^3) = ~17,576 operations.
    - For each character in s (up to 1e5), we check 26 possibilities.
      Total ~ 2.6 million operations, efficient enough.

    Example:
    --------
    s = "abcc", t = "bccc"
    transform = [['a','b'], ['b','c'], ['c','a']]
    cost = [2,1,4]
    Result = 3
*/

class Solution {
public:
    int minCost(string &s, string &t, vector<vector<char>> &transform,
                vector<int> &cost) {
        const int INF = 1e9;
        int n = 26; // number of lowercase letters

        // Distance matrix initialized to INF
        vector<vector<int>> dist(n, vector<int>(n, INF));

        // Self-loops: cost 0 to transform a char into itself
        for (int i = 0; i < n; i++) dist[i][i] = 0;

        // Add given transformations
        for (int i = 0; i < transform.size(); i++) {
            int u = transform[i][0] - 'a';
            int v = transform[i][1] - 'a';
            dist[u][v] = min(dist[u][v], cost[i]); // keep minimum if multiple edges
        }

        // Floyd–Warshall: compute all-pairs shortest paths
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] < INF && dist[k][j] < INF) {
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }

        // Compute minimum cost to make s and t identical
        int totalCost = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == t[i]) continue; // already equal

            int u = s[i] - 'a';
            int v = t[i] - 'a';

            int best = INF;
            // Try transforming both into some common character c
            for (int c = 0; c < n; c++) {
                if (dist[u][c] < INF && dist[v][c] < INF) {
                    best = min(best, dist[u][c] + dist[v][c]);
                }
            }

            if (best == INF) return -1; // impossible
            totalCost += best;
        }

        return totalCost;
    }
};

// Example usage
int main() {
    Solution sol;

    string s1 = "abcc", t1 = "bccc";
    vector<vector<char>> transform1 = {{'a','b'}, {'b','c'}, {'c','a'}};
    vector<int> cost1 = {2,1,4};
    cout << sol.minCost(s1, t1, transform1, cost1) << endl; // Output: 3

    string s2 = "az", t2 = "dc";
    vector<vector<char>> transform2 = {{'a','b'}, {'b','c'}, {'c','d'}, {'a','d'}, {'z','c'}};
    vector<int> cost2 = {5,3,2,50,10};
    cout << sol.minCost(s2, t2, transform2, cost2) << endl; // Output: 20

    string s3 = "xyz", t3 = "xzy";
    vector<vector<char>> transform3 = {{'x','y'}, {'x','z'}};
    vector<int> cost3 = {3,3};
    cout << sol.minCost(s3, t3, transform3, cost3) << endl; // Output: -1

    return 0;
}
