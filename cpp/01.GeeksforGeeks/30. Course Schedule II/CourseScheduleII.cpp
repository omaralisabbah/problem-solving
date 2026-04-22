/*
    You are given n courses, labeled from 0 to n - 1 and a 2d array prerequisites[][] where prerequisites[i] = [x, y]
    indicates that we need to take course  y first if we want to take course x.

    Find the ordering of courses we should take to complete all the courses.

    Note: There may be multiple correct orders, you just need to return any one of them.
    If it is impossible to finish all tasks, return an empty array.
    The Driver code will print true if you return any correct order of courses else it will print false. 

    Examples:

    Input: n = 3, prerequisites[][] = [[1, 0], [2, 1]]
    Output: true
    Explanation: To take course 1, you must finish course 0. To take course 2, you must finish course 1. So the only valid order is [0, 1, 2].

    Input: n = 4, prerequisites[][] = [[2, 0], [2, 1], [3, 2]]
    Output: true
    Explanation: Course 2 requires both 0 and 1. Course 3 requires course 2. Hence, both [0, 1, 2, 3] and [1, 0, 2, 3] are valid.

    Constraints:
    1 ≤ n ≤ 104
    0 ≤ prerequisites.size() ≤ 105
    0 ≤ prerequisites[i][0], prerequisites[i][1] < n
    All prerequisite pairs are unique
    prerequisites[i][0] ≠ prerequisites[i][1]

*/

#include <bits/stdc++.h>
using namespace std;

/*
    Problem: Course Schedule II (Find course order)
    -----------------------------------------------
    We are given `n` courses labeled from 0 to n-1.
    Each prerequisite pair [a, b] means that you must take course `b` before course `a`.

    Our goal is to return a valid order to complete all courses.
    If it’s impossible (due to a cycle in dependencies), return an empty vector.

    Example:
    Input:
        n = 4
        prerequisites = [[2, 0], [2, 1], [3, 2]]
    Output:
        [0, 1, 2, 3]   or   [1, 0, 2, 3]
*/

class Solution {
public:
    /*
        Function: findOrder
        -------------------
        Returns a valid order of courses to complete all tasks, if possible.
        Otherwise, returns an empty vector.

        Parameters:
            - n: number of courses
            - prerequisites: list of prerequisite pairs

        Approach:
            - Build a directed graph (adjacency list)
            - Compute indegree (number of incoming edges) for each node
            - Use a queue to process nodes with indegree 0 (no prerequisites)
            - Remove edges and update indegrees
            - If all nodes are processed, return the order
            - Otherwise, there’s a cycle → return empty
    */
    vector<int> findOrder(int n, vector<vector<int>> &prerequisites) {
        // Step 1: Build adjacency list and indegree array
        vector<vector<int>> adj(n);     // adjacency list
        vector<int> indegree(n, 0);     // indegree of each node

        for (auto &p : prerequisites) {
            int course = p[0];
            int prereq = p[1];
            adj[prereq].push_back(course);  // edge: prereq -> course
            indegree[course]++;             // increment indegree of course
        }

        // Step 2: Push all courses with indegree 0 into queue
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0)
                q.push(i);
        }

        // Step 3: Perform BFS (Kahn's Algorithm)
        vector<int> order;  // stores the final course order

        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);

            // Reduce indegree of neighboring courses
            for (int next : adj[course]) {
                indegree[next]--;
                if (indegree[next] == 0)
                    q.push(next);
            }
        }

        // Step 4: Check if all courses are included (no cycle)
        if (order.size() == n)
            return order;
        else
            return {};  // cycle detected
    }
};

// ---------------------------
// Driver code (for testing)
// ---------------------------
int main() {
    Solution sol;

    // Example 1
    int n1 = 3;
    vector<vector<int>> pre1 = {{1, 0}, {2, 1}};
    vector<int> order1 = sol.findOrder(n1, pre1);

    cout << "Example 1: ";
    if (!order1.empty()) {
        for (int c : order1) cout << c << " ";
        cout << endl;
    } else {
        cout << "No valid order (cycle detected)" << endl;
    }

    // Example 2
    int n2 = 4;
    vector<vector<int>> pre2 = {{2, 0}, {2, 1}, {3, 2}};
    vector<int> order2 = sol.findOrder(n2, pre2);

    cout << "Example 2: ";
    if (!order2.empty()) {
        for (int c : order2) cout << c << " ";
        cout << endl;
    } else {
        cout << "No valid order (cycle detected)" << endl;
    }

    // Example 3 (cycle)
    int n3 = 2;
    vector<vector<int>> pre3 = {{1, 0}, {0, 1}};
    vector<int> order3 = sol.findOrder(n3, pre3);

    cout << "Example 3: ";
    if (!order3.empty()) {
        for (int c : order3) cout << c << " ";
        cout << endl;
    } else {
        cout << "No valid order (cycle detected)" << endl;
    }

    return 0;
}
