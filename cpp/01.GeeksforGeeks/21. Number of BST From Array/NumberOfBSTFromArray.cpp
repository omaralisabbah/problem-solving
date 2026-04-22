/*
You are given an integer array arr[] containing distinct elements.

Your task is to return an array where the ith element denotes the number of unique BSTs formed when arr[i] is chosen as the root.

Examples :

Input: arr[] = [2, 1, 3]
Output: [1, 2, 2]
Explanation: 
4

Input: arr[] = [2, 1]
Ouput: [1, 1]

Constraints:
1 ≤ arr.size() ≤ 6
1 ≤ arr[i] ≤ 15


To solve the problem, we need to determine how many unique Binary Search Trees (BSTs) can be formed when each element in the array is chosen as the root.

Key Concepts:

Unique Binary Search Trees (BSTs):
A binary search tree (BST) follows the property where for any given node:

All nodes in its left subtree are smaller than the node.

All nodes in its right subtree are larger than the node.

Number of Unique BSTs:

If we take a number 
n
n, the number of unique BSTs that can be formed with 
n
n nodes is a well-known combinatorics problem. The number of unique BSTs that can be formed with 
n
n nodes is given by the Catalan number for 
n
n, and it can be calculated using dynamic programming.

Dynamic Programming Approach:

Given a root element from the array, we can calculate the number of unique BSTs formed by:

Choosing the element as the root.

Dividing the remaining elements into two subarrays:

Left subarray: All elements smaller than the root.

Right subarray: All elements larger than the root.

The number of BSTs for a specific root is the product of the number of BSTs that can be formed from the left and right subarrays.

Steps:

For each element 
arr[i]
arr[i] in the array:

Consider it as the root.

Calculate how many elements are smaller (left subtree) and how many are larger (right subtree).

The result for that root is the product of the number of BSTs for the left and right subtrees.

Approach:

For each element in the input array, treat it as a root.

Split the array into left and right subarrays.

Count how many unique BSTs can be formed using dynamic programming.

Return the results for each element.

Explanation:

numUniqueBSTs Function:

This function computes the number of unique BSTs that can be formed with 
n
n nodes. It uses dynamic programming (DP) to compute this value for all values from 0 to 
n
n.

The idea is that for a given number of nodes 
n
n, the number of unique BSTs can be computed by selecting each node as the root and multiplying the number of BSTs on the left and right subtrees.

countBSTs Function:

For each element in the array, we count how many nodes are smaller and how many are larger, which gives the sizes of the left and right subtrees.

Then, we calculate the total number of unique BSTs using the numUniqueBSTs function for each subtree size.

Time Complexity:

The time complexity of the numUniqueBSTs function is 
O(n2)
O(n
2
) due to the double loop in the dynamic programming computation.

For each element in the array (of size 
N
N), we are computing the number of unique BSTs for both the left and right subarrays. This results in a time complexity of 
O(N⋅N2)
O(N⋅N
2
), which is efficient enough given the constraints.

*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Function to compute the number of unique BSTs for a given number of nodes
    int numUniqueBSTs(int n) {
        vector<int> dp(n + 1, 0);  // dp[i] will store the number of unique BSTs with i nodes
        dp[0] = 1;  // There's one BST with zero nodes (empty tree)
        dp[1] = 1;  // There's one BST with one node
        
        // Fill dp[] for all values from 2 to n
        for (int nodes = 2; nodes <= n; ++nodes) {
            for (int root = 1; root <= nodes; ++root) {
                // The number of unique BSTs with `root` as root is the product
                // of the number of BSTs in the left and right subtrees
                dp[nodes] += dp[root - 1] * dp[nodes - root];
            }
        }
        
        return dp[n];  // Return the number of unique BSTs for n nodes
    }

    vector<int> countBSTs(vector<int>& arr) {
        vector<int> result;
        
        // For each element in the array, compute the number of unique BSTs
        for (int i = 0; i < arr.size(); ++i) {
            // Get the number of unique BSTs when arr[i] is the root
            int leftSize = 0, rightSize = 0;
            for (int j = 0; j < arr.size(); ++j) {
                if (arr[j] < arr[i]) {
                    leftSize++;
                } else if (arr[j] > arr[i]) {
                    rightSize++;
                }
            }
            
            // The number of unique BSTs with arr[i] as the root is the product
            // of the number of BSTs for the left and right subtrees
            int totalBSTs = numUniqueBSTs(leftSize) * numUniqueBSTs(rightSize);
            result.push_back(totalBSTs);
        }

        return result;
    }
};

int main() {
    Solution solution;
    
    // Test case 1
    vector<int> arr1 = {2, 1, 3};
    vector<int> result1 = solution.countBSTs(arr1);
    for (int i : result1) {
        cout << i << " ";
    }
    cout << endl;  // Expected output: [1, 2, 2]

    // Test case 2
    vector<int> arr2 = {2, 1};
    vector<int> result2 = solution.countBSTs(arr2);
    for (int i : result2) {
        cout << i << " ";
    }
    cout << endl;  // Expected output: [1, 1]
    
    return 0;
}
