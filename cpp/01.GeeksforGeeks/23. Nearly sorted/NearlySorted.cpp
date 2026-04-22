/*

Given an array arr[], where each element is at most k positions away from its correct position in the sorted order.
Your task is to restore the sorted order of arr[] by rearranging the elements in place.

Note: Don't use any sort() method.

Examples:

Input: arr[] = [2, 3, 1, 4], k = 2
Output: [1, 2, 3, 4]
Explanation: All elements are at most k = 2 positions away from their correct positions.
Element 1 moves from index 2 to 0
Element 2 moves from index 0 to 1
Element 3 moves from index 1 to 2
Element 4 stays at index 3

Input: arr[]= [7, 9, 14], k = 1
Output: [7, 9, 14]
Explanation: All elements are already stored in the sorted order.

Constraints:
1 ≤ arr.size() ≤ 106
0 ≤ k < arr.size()
1 ≤ arr[i] ≤ 106


Since any element is at most k positions away from its correct position, the smallest element among the first k + 1 elements must be the first element of the sorted array. So, we can:

Maintain a min-heap of size k + 1.

Pop the smallest element and place it in the correct position in the array.

Push the next element from the array into the heap.

This results in a time complexity of O(n log k) and space complexity of O(k).


Explanation of the code:

Solution class: It contains the nearlySorted function that sorts the array.

priority_queue: We use a min-heap to always extract the smallest element from the first k+1 elements.

Loop logic:

First, fill the min-heap with the first k + 1 elements.

Then, for the remaining elements, push the current element into the heap and pop the smallest element from the heap to place it in the correct position in the array.

Finally, empty the heap by placing the remaining elements in the array.

Test Cases: Two test cases are demonstrated in the main function.

Example Output:
Sorted array 1: 1 2 3 4
Sorted array 2: 7 9 14

*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
  public:
    void nearlySorted(vector<int>& arr, int k) {
        // Min-heap
        priority_queue<int, vector<int>, greater<int>> minHeap;

        int n = arr.size();
        int index = 0;

        // Step 1: Push first k+1 elements into the min-heap
        for (int i = 0; i <= k && i < n; ++i) {
            minHeap.push(arr[i]);
        }

        // Step 2: For the rest of the elements, push into heap and pop the smallest
        for (int i = k + 1; i < n; ++i) {
            arr[index++] = minHeap.top();
            minHeap.pop();
            minHeap.push(arr[i]);
        }

        // Step 3: Pop remaining elements from heap and place in array
        while (!minHeap.empty()) {
            arr[index++] = minHeap.top();
            minHeap.pop();
        }
    }
};

int main() {
    Solution sol;

    // Test case 1
    vector<int> arr1 = {2, 3, 1, 4};
    int k1 = 2;
    sol.nearlySorted(arr1, k1);
    cout << "Sorted array 1: ";
    for (int num : arr1) {
        cout << num << " ";
    }
    cout << endl;

    // Test case 2
    vector<int> arr2 = {7, 9, 14};
    int k2 = 1;
    sol.nearlySorted(arr2, k2);
    cout << "Sorted array 2: ";
    for (int num : arr2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
