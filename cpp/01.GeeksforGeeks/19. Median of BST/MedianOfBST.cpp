/*

You are given the root of a Binary Search Tree, find the median of it. 

Let the nodes of the BST, when written in ascending order (inorder traversal), be represented as V1, V2, V3, …, Vn, where n is the total number of nodes in the BST.

    If number of nodes are even: return V(n/2)
    If number of nodes are odd: return V((n+1)/2)

Examples:

Input: root = [20, 8, 22, 4, 12, N, N, N, N, 10, 14]
2
Output: 12
Explanation: The inorder of given BST is 4, 8, 10, 12, 14, 20, 22. Here, n = 7, so, here median will be ((7+1)/2)th value, i.e., 4th value, i.e, 12.


Input: root = [5, 4, 8, 1]
1 
Output: 4
Explanation: The inorder of given BST is 1, 4, 5, 8. Here, n = 4(even), so, here median will be (4/2)th value, i.e., 2nd value, i.e, 4.

Constraints:
1 ≤ number of nodes ≤ 105
1 ≤ node.data ≤  105

      20
     /  \
    8    22
   / \   
  4  12  
     /  \
    10  14


    Problem Explanation:

The problem statement mentions that:

For odd number of nodes, the median is the element at position (n+1)/2 (1-based index).

For even number of nodes, the median is at position n/2 (1-based index).

However, in the previous code, we incorrectly assumed that when the number of nodes is even, we return the element at n/2 (0-based index), while we should be returning the n/2-th element based on 1-based indexing.

Let's Correct the Code:

In the case of odd nodes, (n+1)/2 works as expected in both 1-based and 0-based index. This is fine.

For even nodes, we should return the element at index n/2 - 1 based on 0-based indexing (since the problem statement says to use 1-based indexing for median when the total count is even).
*/

#include <iostream>
#include <vector>

using namespace std;

class Node {
  public:
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class Solution {
  public:
    // Helper function to perform inorder traversal
    void inorderTraversal(Node* root, vector<int>& nodes) {
        if (root == nullptr) return;
        
        inorderTraversal(root->left, nodes);
        nodes.push_back(root->data);
        inorderTraversal(root->right, nodes);
    }

    int findMedian(Node* root) {
        // Step 1: Perform inorder traversal and store the nodes in a vector
        vector<int> nodes;
        inorderTraversal(root, nodes);
        
        // Step 2: Find the size of the vector
        int n = nodes.size();
        
        // Step 3: Return the median based on the size of the array
        if (n % 2 == 1) {
            // If odd, return the middle element (0-indexed)
            return nodes[n / 2];
        } else {
            // If even, return the element at index n/2 - 1 (0-indexed) for 1-based indexing
            return nodes[n / 2 - 1];
        }
    }
};

// Main function to test the solution
int main() {
    // Create a simple BST: 5 -> 4 -> 8 -> 1
    Node* root = new Node(5);
    root->right = new Node(4);
    root->right->right = new Node(8);
    root->right->right->right = new Node(1);

    // Create an instance of Solution class
    Solution solution;

    // Find the median
    int median = solution.findMedian(root);
    cout << "Median of the BST is: " << median << endl;

    return 0;
}
