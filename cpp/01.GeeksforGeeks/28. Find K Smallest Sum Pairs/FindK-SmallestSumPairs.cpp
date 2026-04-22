/*
    Given two integer arrays arr1[] and arr2[] sorted in ascending order and an integer k,
    your task is to find k pairs with the smallest sums,
    such that one element of each pair belongs to arr1[] and the other belongs to arr2[].

    Return the list of these k pairs, where each pair is represented as [arr1[i], arr2[j]].

    Note: You can return any possible k pairs with the smallest sums, the driver code will print true if it is correct else it will print false.

    Examples:

    Input: arr1[] = [1, 7, 11], arr2[] = [2, 4, 6], k = 3
    Output: true
    Explanation: All possible combinations of elements from the two arrays are:
    [1, 2], [1, 4], [1, 6], [7, 2], [7, 4], [7, 6], [11, 2], [11, 4], [11, 6]. 
    Among these, the three pairs with the minimum sums are [1, 2], [1, 4], [1, 6].

    Input: arr1[] = [1, 3], arr2[] = [2, 4] k = 2
    Output: true
    Explanation: All possible combinations are [1, 2], [1, 4], [3, 2], [3, 4]. 
    Among these, the two pairs with the minimum sums are [1, 2], [3, 2].

    Constraints:
    1 ≤ arr1.size(), arr2.size() ≤ 5*104
    1 ≤ arr1[i], arr2[j] ≤ 109
    1 ≤ k ≤ 103
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

/*
    Problem:
    Given two sorted arrays arr1[] and arr2[], and an integer k,
    find k pairs with the smallest sums such that one element is from arr1 and the other from arr2.

    Approach:
    - Use a min-heap (priority_queue) to efficiently track the next smallest pair.
    - Start by pushing the first k pairs (arr1[i], arr2[0]) into the heap.
    - Pop the smallest sum pair and push the next pair (arr1[i], arr2[j+1]) if possible.
*/

class Solution {
public:
    vector<vector<int>> kSmallestPair(vector<int>& arr1, vector<int>& arr2, int k) {
        vector<vector<int>> result;

        // Edge case: if either array is empty or k is zero
        if (arr1.empty() || arr2.empty() || k == 0) return result;

        // Min-heap to store tuples of (sum, index in arr1, index in arr2)
        auto cmp = [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
            return get<0>(a) > get<0>(b); // Min-heap based on sum
        };
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(cmp)> minHeap(cmp);

        // Initialize heap with the first k pairs (arr1[i], arr2[0])
        for (int i = 0; i < arr1.size() && i < k; ++i) {
            minHeap.emplace(arr1[i] + arr2[0], i, 0);
        }

        // Extract k smallest pairs
        while (k-- > 0 && !minHeap.empty()) {
            auto [sum, i, j] = minHeap.top();
            minHeap.pop();

            // Add the current pair to the result
            result.push_back({arr1[i], arr2[j]});

            // If there's a next element in arr2, push the new pair (arr1[i], arr2[j+1])
            if (j + 1 < arr2.size()) {
                minHeap.emplace(arr1[i] + arr2[j + 1], i, j + 1);
            }
        }

        return result;
    }
};

// Driver code for testing
int main() {
    Solution sol;

    vector<int> arr1 = {1, 7, 11};
    vector<int> arr2 = {2, 4, 6};
    int k = 3;

    vector<vector<int>> result = sol.kSmallestPair(arr1, arr2, k);

    cout << "K smallest pairs with minimum sums:\n";
    for (const auto& pair : result) {
        cout << "[" << pair[0] << ", " << pair[1] << "]\n";
    }

    return 0;
}
