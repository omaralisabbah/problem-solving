/*

Given the root of a Binary Search Tree, a target value, and an integer k. Your task is to find the k values in the BST that are closest to the target.

The closest value is taken by choosing the one that gives minimum absolute difference from target.

Note: In case two values have same absolute difference from target, choose the smaller one. The target may or may not be present in BST.
You can return the values in any order the driver code will print them in sorted order only.

Examples:

Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14], target = 17, k = 3
     
Output: [14, 20, 12]
Explanation: Absolute difference of 17 wrt 14 and 20 is 3 and 3, but we choose the smaller value in case of same absolute difference. So, 14 coes first and then 20. Then, 12 and 22 have same absolute difference, i.e., 5 from 17. But we choose the smaller value, i.e., 12.
     

Input: root = [5, 4, 8, 1], target = 5, k = 2
     
Output: [5, 4]
Explanation: The absolute difference of 5 wrt 5 is 0, and for 4, the absolute difference is 1.
    

Constraints:
1 ≤ number of nodes, k ≤ 104
1 ≤ node->data, target ≤ 104

To solve this problem, we need to find the k closest values to a given target in a Binary Search Tree (BST). The closest value is defined by the minimum absolute difference between the node's value and the target. If two values have the same difference, we should pick the smaller value.

Approach:

Inorder Traversal for BST:
In a BST, an inorder traversal will give us the elements in sorted order. By leveraging this property, we can easily find the closest values, but instead of traversing the entire tree, we can utilize a more efficient approach using a two-pointer technique or priority queue.

Two-pointer approach:

The idea is to perform a modified inorder traversal to traverse the tree and keep track of the closest k values. We can maintain a max-heap (or a priority queue) to store the k closest elements.

As we traverse the tree, we calculate the absolute difference between each node's value and the target. If the heap has fewer than k elements, we add the current node. If the heap has k elements, we compare the current node's value with the largest value in the heap (the root of the max-heap). If the current value is closer to the target, we replace the largest element.

Heap-based solution:
We will use a min-heap based on the absolute difference from the target. Python's heapq library provides a min-heap by default, but we can simulate a max-heap by storing the negative of the differences.

Steps:

Traverse the BST using inorder traversal or DFS.

Keep track of the closest k nodes using a max-heap of size k.

After the traversal is done, extract the k closest nodes.

Correct Approach:

Inorder traversal: Traverse the BST to process nodes in increasing order (since it's a BST, this is the property we can use).

Max-heap for closest values: Instead of storing all values, we use a max-heap to store the closest k values.

If the heap size exceeds k, we remove the largest element (the one with the largest absolute difference from the target).

Heap comparison: While adding elements to the heap, we will compare their absolute difference with the target. If two values have the same difference, we choose the smaller one.

Return the closest k elements: Once the traversal is complete, the heap will contain the k closest values, which we can return.

Let's fix the solution using this approach.

        8
       / \
      3   9
     / \   
    2   4
         /  
        5
         \
          6

          Inorder Traversal will give: [2, 3, 4, 5, 6, 8, 9]

Absolute Differences from 4:

|2 - 4| = 2

|3 - 4| = 1

|4 - 4| = 0

|5 - 4| = 1

|6 - 4| = 2

|8 - 4| = 4

|9 - 4| = 5

The closest 4 values are: [4, 3, 5, 2].

Final output: [4, 3, 5, 2] or in any order as required.

Time Complexity:

Time Complexity: O(n log k)

We perform an inorder traversal of the tree, which is O(n) where n is the number of nodes.

For each node, we perform O(log k) operations on the max-heap (since the heap has at most k elements).

Space Complexity: O(k)

We maintain a max-heap of size k, which uses O(k) space.

This approach should now work for all test cases correctly.

Let me know if you have further questions!
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

// Definition for a binary tree node.
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    vector<int> getKClosest(Node* root, int target, int k) {
        // Max-heap to store k closest elements (will store pairs of absolute difference and the node value)
        priority_queue<pair<int, int>> maxHeap;
        
        // Helper function for inorder traversal
        inorderTraversal(root, target, k, maxHeap);
        
        // Extract the elements from the heap into a result vector
        vector<int> result;
        while (!maxHeap.empty()) {
            result.push_back(maxHeap.top().second);
            maxHeap.pop();
        }
        
        // Since we want the closest values in any order, we can return as is.
        return result;
    }

private:
    void inorderTraversal(Node* root, int target, int k, priority_queue<pair<int, int>>& maxHeap) {
        if (!root) return;
        
        // Traverse left subtree
        inorderTraversal(root->left, target, k, maxHeap);
        
        // Calculate the absolute difference between the node's value and target
        int diff = abs(root->data - target);
        
        // Push the current node value and its difference into the max heap
        maxHeap.push({diff, root->data});
        
        // If the heap size exceeds k, remove the element with the largest difference
        if (maxHeap.size() > k) {
            maxHeap.pop();
        }
        
        // Traverse right subtree
        inorderTraversal(root->right, target, k, maxHeap);
    }
};

// Helper function to build a Binary Search Tree from an array
Node* buildTree(const vector<int>& arr, int& idx) {
    if (idx >= arr.size() || arr[idx] == -1) {
        idx++;
        return nullptr;
    }
    Node* node = new Node(arr[idx++]);
    node->left = buildTree(arr, idx);
    node->right = buildTree(arr, idx);
    return node;
}

int main() {
    // Test case input
    vector<int> treeValues = {8, 3, 9, 2, 4, -1, -1, -1, -1, 5, -1, 6, -1, -1};
    int target = 4, k = 4;
    
    int idx = 0;
    Node* root = buildTree(treeValues, idx);
    
    Solution solution;
    vector<int> closestValues = solution.getKClosest(root, target, k);
    
    // Output the result
    cout << "The " << k << " closest values to " << target << " are: ";
    for (int val : closestValues) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
