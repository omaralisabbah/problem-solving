/*
    Given an array, arr[] of rope lengths, connect all ropes into a single rope with the minimum total cost.
    The cost to connect two ropes is the sum of their lengths. 

    Examples:

    Input: arr[] = [4, 3, 2, 6]
    Output: 29
    Explanation: First connect 2 and 3 to get [4, 5, 6] with a cost of 5, then connect 4 and 5 to get [9, 6] with a cost of 9, and finally connect 9 and 6 to get one rope with a cost of 15, giving a total minimum cost of 29. Any other order, such as connecting 4 and 6 first, results in a higher total cost of 38.

    Input: arr[] = [4, 2, 7, 6, 9]
    Output: 62 
    Explanation: First, connect ropes 4 and 2, which makes the array [6, 7, 6, 9]. Cost of this operation 4 + 2 = 6. Next, add ropes 6 and 6, which results in [12, 7, 9]. Cost of this operation 6 + 6 = 12. Then, add 7 and 9, which makes the array [12,16]. Cost of this operation 7 + 9 = 16. And finally, add these two which gives [28]. Hence, the total cost is 6 + 12 + 16 + 28 = 62.

    Input: arr[] = [10]
    Output: 0
    Explanation: Since there is only one rope, no connections are needed, so the cost is 0.

    Constraints:
    1 ≤ arr.size() ≤ 105
    1 ≤ arr[i] ≤ 104





    Explanation:

    Min-Heap (Priority Queue):

    We use a min-heap to always access the smallest elements first. A priority queue in C++ defaults to a max-heap, so we specify greater<int> to create a min-heap.

    Main Steps:

    We keep extracting the two smallest ropes, calculating the cost of combining them, and pushing the new combined rope back into the heap.

    We repeat this process until only one rope remains, and the accumulated totalCost will be the minimum cost.

    Time Complexity:

    Heap Operations: Each insertion or extraction from the heap takes O(log n), and there are n-1 operations (since we combine ropes n-1 times).

    Overall Time Complexity: O(n log n), where n is the number of ropes in the input array.

    Space Complexity:

    Heap Space: The heap stores at most n ropes, so the space complexity is O(n).

    This approach should work efficiently even for the largest input sizes within the problem's constraints.
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int minCost(vector<int>& arr) {
        // If there's only one rope, no cost to connect
        if (arr.size() == 1) {
            return 0;
        }

        // Create a min-heap (priority queue)
        priority_queue<int, vector<int>, greater<int>> pq;

        // Push all elements into the min-heap
        for (int len : arr) {
            pq.push(len);
        }

        int totalCost = 0;

        // While there are more than one element in the heap
        while (pq.size() > 1) {
            // Extract the two smallest elements
            int first = pq.top();
            pq.pop();
            int second = pq.top();
            pq.pop();

            // Calculate the cost to combine these two ropes
            int cost = first + second;
            totalCost += cost;

            // Push the combined rope back into the heap
            pq.push(cost);
        }

        return totalCost;
    }
};

int main() {
    Solution solution;
    
    // Test case 1
    vector<int> arr1 = {4, 3, 2, 6};
    cout << "Minimum Cost (Test 1): " << solution.minCost(arr1) << endl;  // Output: 29

    // Test case 2
    vector<int> arr2 = {4, 2, 7, 6, 9};
    cout << "Minimum Cost (Test 2): " << solution.minCost(arr2) << endl;  // Output: 62

    // Test case 3
    vector<int> arr3 = {10};
    cout << "Minimum Cost (Test 3): " << solution.minCost(arr3) << endl;  // Output: 0

    return 0;
}
