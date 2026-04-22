/*
    Given a non-empty integer array arr[]. Your task is to find and return the top k elements which have the highest frequency in the array.

Note: If two numbers have the same frequency, the larger number should be given the higher priority.

Examples:

Input: arr[] = [3, 1, 4, 4, 5, 2, 6, 1], k = 2
Output: [4, 1]
Explanation: Frequency of 4 is 2 and frequency of 1 is 2, these two have the maximum frequency and 4 is larger than 1.

Input: arr[] = [7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9], k = 4
Output: [5, 11, 7, 10]
Explanation: Frequency of 5 is 3, frequency of 11 is 2, frequency of 7 is 2, frequency of 10 is 1.

Constraints:
1 ≤ arr.size() ≤ 105
1 ≤ arr[i] ≤ 105
1 ≤ k ≤ no. of distinct elements

To solve this problem efficiently, we can follow these steps:

🔍 Steps to solve:

Count frequencies of each number in the array using a unordered_map<int, int>.

Use a custom comparator with a priority_queue (max heap) to sort by:

Higher frequency first.

If frequencies are equal, larger number first.

Extract the top k elements from the heap.

✅ Time Complexity:

Counting frequencies: O(n)

Building the heap: O(n log n)

Extracting k elements: O(k log n)

Overall: O(n log n) in worst case, acceptable for n ≤ 10^5.
*/


#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> topKFreq(vector<int> &arr, int k) {
        unordered_map<int, int> freq;

        // Count frequency of each element
        for (int num : arr) {
            freq[num]++;
        }

        // Custom comparator for max heap
        auto comp = [](pair<int, int>& a, pair<int, int>& b) {
            if (a.second == b.second)
                return a.first < b.first; // Higher number first if frequency is same
            return a.second < b.second;   // Higher frequency first
        };

        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> pq(comp);

        // Push all elements into the heap
        for (auto& entry : freq) {
            pq.push({entry.first, entry.second});
        }

        // Extract top k elements
        vector<int> result;
        for (int i = 0; i < k && !pq.empty(); ++i) {
            result.push_back(pq.top().first);
            pq.pop();
        }

        return result;
    }
};

// Main function to test the code
int main() {
    Solution sol;

    // Example 1
    vector<int> arr1 = {3, 1, 4, 4, 5, 2, 6, 1};
    int k1 = 2;
    vector<int> result1 = sol.topKFreq(arr1, k1);

    cout << "Output 1: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    // Example 2
    vector<int> arr2 = {7, 10, 11, 5, 2, 5, 5, 7, 11, 8, 9};
    int k2 = 4;
    vector<int> result2 = sol.topKFreq(arr2, k2);

    cout << "Output 2: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
