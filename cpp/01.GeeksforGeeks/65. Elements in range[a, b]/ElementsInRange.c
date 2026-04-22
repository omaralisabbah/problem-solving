/*
    Given an unsorted array arr[] and a 2D array queries[][] of size q, where each query is in the form of [a, b]. For each query, count how many elements in arr[] lie within the range [a, b], i.e., elements satisfying a ≤ x ≤ b.

Return the results for all queries as a list of integers, where each integer corresponds to the count of elements in the respective query range.

Examples

Input arr[] = [1, 4, 2, 8, 5], queries[][] = [[1, 4], [3, 6], [0, 10]]
Output [3, 2, 5]
Explanation Query [1, 4] Elements in range → [1, 4, 2] → Count = 3
Query [3, 6] Elements in range → [4, 5] → Count = 2
Query [0, 10] All elements → [1, 4, 2, 8, 5] → Count = 5

Input arr[] = [10, 20, 30, 40, 50], queries[][] = [[5, 15], [25, 45], [10, 50]]
Output [1, 2, 5]
Explanation Query [5, 15] Elements in range → [10] → Count = 1
Query [25, 45] Elements in range → [30, 40] → Count = 2
Query [10, 50] Elements in range → [10, 20, 30, 40, 50] → Count = 5

Constraints
1 ≤ arr.size(), q ≤ 105
0 ≤ arr[i] ≤ 106
0 ≤ queries[i][0] ≤ queries[i][1] ≤ 106


*/

#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    --------
    Given an unsorted array arr[] and a list of queries, where each query is [a, b],
    count how many elements in arr[] lie within the inclusive range [a, b].

    Constraints:
    ------------
    - 1 ≤ arr.size(), q ≤ 1e5
    - 0 ≤ arr[i] ≤ 1e6
    - 0 ≤ queries[i][0] ≤ queries[i][1] ≤ 1e6

    Approach:
    ---------
    1. Sort the array arr.
    2. For each query [a, b]:
       - Use lower_bound(arr.begin(), arr.end(), a) → gives first index with value >= a.
       - Use upper_bound(arr.begin(), arr.end(), b) → gives first index with value > b.
       - Count = (upper_bound - lower_bound).
    3. Store results in a vector and return.

    Time Complexity:
    ----------------
    - Sorting: O(n log n)
    - Each query: O(log n)
    - Total: O(n log n + q log n), efficient for n, q ≤ 1e5.
*/

class Solution {
public:
    vector<int> cntInRange(vector<int> &arr, vector<vector<int>> &queries) {
        // Step 1: Sort the array for binary search
        sort(arr.begin(), arr.end());

        vector<int> result;
        result.reserve(queries.size()); // reserve space for efficiency

        // Step 2: Process each query
        for (auto &q : queries) {
            int a = q[0], b = q[1];

            // lower_bound: first index with value >= a
            auto low = lower_bound(arr.begin(), arr.end(), a);

            // upper_bound: first index with value > b
            auto high = upper_bound(arr.begin(), arr.end(), b);

            // Count = difference in indices
            result.push_back(high - low);
        }

        return result;
    }
};

// -------------------
// Example Usage (Driver Code)
// -------------------
int main() {
    Solution sol;

    vector<int> arr = {1, 4, 2, 8, 5};
    vector<vector<int>> queries = {{1, 4}, {3, 6}, {0, 10}};

    vector<int> ans = sol.cntInRange(arr, queries);

    cout << "Results: ";
    for (int x : ans) cout << x << " ";
    cout << endl;

    // Expected Output: [3, 2, 5]
    return 0;
}
