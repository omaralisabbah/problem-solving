/*

Given the root of a BST and an integer k, the task is to find the kth smallest element in the BST. If there is no kth smallest element present then return -1.

Examples:
Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14], k = 3
    
Output: 10
Explanation: 10 is the 3rd smallest element in the BST.

Input: root = [2, 1, 3], k = 5
    
Output: -1
Explanation: There is no 5th smallest element in the BST as the size of BST is 3.

Constraints:
1 ≤ number of nodes, k ≤ 104
1 ≤ node->data ≤ 104


To solve the problem of finding the k-th smallest element in a Binary Search Tree (BST), we can leverage the in-order traversal. In a BST, the in-order traversal will visit the nodes in ascending order, so the k-th smallest element corresponds to the k-th node visited in this traversal.

Here's the plan:

Plan:

In-order Traversal: In-order traversal visits the nodes of a BST in the order: left subtree, root, right subtree.

Count until k: As we traverse the tree, we keep a counter. Once the counter reaches k, we've found the k-th smallest element.

Edge case: If k exceeds the number of nodes in the BST, we return -1.

Approach:

Perform an in-order traversal.

During traversal, maintain a count of how many nodes we have visited.

When we reach the k-th node, return its value.

If we complete the traversal without finding the k-th node, return -1.
*/


#include <iostream>
using namespace std;

// Definition for a binary tree node
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to create a new node
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class Solution {
public:
    int kthSmallest(Node* root, int k) {
        int count = 0;
        return inorder(root, k, count);
    }

private:
    int inorder(Node* root, int k, int &count) {
        if (root == nullptr) {
            return -1;  // If we reach a null node, return -1
        }
        
        // Traverse left subtree
        int left = inorder(root->left, k, count);
        if (left != -1) {
            return left;  // If we found the kth smallest in the left subtree, return it
        }
        
        // Visit the current node
        count++;
        if (count == k) {
            return root->data;  // If count reaches k, return the kth smallest element
        }
        
        // Traverse right subtree
        return inorder(root->right, k, count);
    }
};

// Utility function to insert a node into the BST
Node* insert(Node* root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

int main() {
    // Create a BST
    Node* root = nullptr;
    root = insert(root, 20);
    root = insert(root, 8);
    root = insert(root, 22);
    root = insert(root, 4);
    root = insert(root, 12);
    root = insert(root, 10);
    root = insert(root, 14);

    int k = 3;
    
    // Find the kth smallest element
    Solution solution;
    int result = solution.kthSmallest(root, k);
    
    if (result != -1) {
        cout << "The " << k << "-th smallest element is: " << result << endl;
    } else {
        cout << "There is no " << k << "-th smallest element in the BST." << endl;
    }

    return 0;
}