/*
Given the root of a Binary Search Tree (BST) and two integers l and r, remove all the nodes whose values lie outside the range [l, r].

Note: The modified tree should also be BST.

Examples:

Input: root = [6, -13, 14, N, -8, 13, 15, N, N, 7], l = -10, r = 13

Output: [6, -8, 13, N, N, 7]
Explanation: All the nodes outside the range [-10, 13] are removed and the modified tree is a valid BST.

Input: root = [14, 4, 16, 2, 8, 15, N, -8, 3, 7, 10], l = 2, r = 6
 
Output: [4, 2, N, N, 3]
Explanation: All the nodes outside the range [2, 6] are removed and the modified tree is a valid BST.

   

Constraints:
1 ≤ number of nodes ≤ 104
1 ≤ node->data ≤ 104
1 ≤ l ≤ r ≤ 104


To solve this problem, we need to remove all the nodes in a Binary Search Tree (BST) whose values fall outside the range 
[l,r]
[l,r], and we need to ensure that the modified tree still remains a valid BST.

Approach:

We can use a recursive approach to traverse the tree and process each node. For each node:

If the node’s value is less than l:

This means the current node and all nodes in its left subtree must be removed because they cannot be part of the valid BST (since all left children are smaller).

Therefore, we should recursively process the right subtree and return it as the new subtree for this node.

If the node’s value is greater than r:

Similarly, the current node and all nodes in its right subtree need to be removed because they are greater than r.

We should recursively process the left subtree and return it as the new subtree for this node.

If the node’s value lies between l and r (inclusive):

This node is valid, and we recursively fix both its left and right subtrees, keeping them in the valid range.

The recursion will ensure that each node either gets pruned (if it falls outside the range) or is retained if it lies within the range.

Algorithm:

Start at the root of the tree.

For each node:

If the value of the node is less than l, move to its right child (since left subtree is irrelevant).

If the value of the node is greater than r, move to its left child (since right subtree is irrelevant).

Otherwise, recursively ensure that both the left and right children also lie within the range 
[l,r]
[l,r].

Return the modified tree.

*/

#include <iostream>
using namespace std;

/*
 * Definition for a Binary Tree Node
 */
class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a node with a given value
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

/*
 * Solution class contains the method to remove nodes outside the range [l, r]
 */
class Solution {
public:
    /*
     * The removekeys function modifies the BST by removing all nodes whose values 
     * lie outside the range [l, r]. It maintains the BST property.
     * 
     * Arguments:
     * - root: The root of the binary search tree (BST).
     * - l: The lower bound of the range.
     * - r: The upper bound of the range.
     * 
     * Returns:
     * - The modified root of the BST.
     */
    Node* removekeys(Node* root, int l, int r) {
        // Base case: If the tree is empty, return NULL
        if (root == NULL) {
            return NULL;
        }

        // Case 1: If the node's value is less than the lower bound `l`
        // In this case, we remove the current node and its left subtree
        if (root->data < l) {
            // The right child of the current node will be the new root for this subtree
            return removekeys(root->right, l, r);
        }

        // Case 2: If the node's value is greater than the upper bound `r`
        // In this case, we remove the current node and its right subtree
        if (root->data > r) {
            // The left child of the current node will be the new root for this subtree
            return removekeys(root->left, l, r);
        }

        // Case 3: If the node's value lies within the range [l, r]
        // Recursively fix the left and right subtrees
        root->left = removekeys(root->left, l, r);
        root->right = removekeys(root->right, l, r);
        
        // Return the current node (as it's within the valid range)
        return root;
    }
};

/*
 * Helper function to print the inorder traversal of the tree
 * This is used to verify the structure of the tree after modification.
 */
void inorderTraversal(Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }
}

/*
 * Helper function to create a new node in the tree
 */
Node* createNode(int data) {
    return new Node(data);
}

int main() {
    // Example 1:
    // Construct the tree: [6, -13, 14, N, -8, 13, 15, N, N, 7]
    Node* root1 = createNode(6);
    root1->left = createNode(-13);
    root1->right = createNode(14);
    root1->left->right = createNode(-8);
    root1->right->left = createNode(13);
    root1->right->right = createNode(15);
    root1->left->right->right = createNode(7);
    
    // Creating solution object and calling removekeys
    Solution sol;
    root1 = sol.removekeys(root1, -10, 13);
    
    cout << "Inorder traversal of modified tree (Example 1): ";
    inorderTraversal(root1);
    cout << endl;

    // Example 2:
    // Construct the tree: [14, 4, 16, 2, 8, 15, N, -8, 3, 7, 10]
    Node* root2 = createNode(14);
    root2->left = createNode(4);
    root2->right = createNode(16);
    root2->left->left = createNode(2);
    root2->left->right = createNode(8);
    root2->right->left = createNode(15);
    root2->left->left->left = createNode(-8);
    root2->left->left->right = createNode(3);
    root2->left->right->left = createNode(7);
    root2->left->right->right = createNode(10);
    
    // Calling removekeys on the second example
    root2 = sol.removekeys(root2, 2, 6);
    
    cout << "Inorder traversal of modified tree (Example 2): ";
    inorderTraversal(root2);
    cout << endl;

    return 0;
}


/*
    Explanation:
1. Node Class:

This class represents a node in the Binary Search Tree (BST). Each node contains:

data: The value stored in the node.

left: A pointer to the left child.

right: A pointer to the right child.

2. Solution Class:

removekeys(Node root, int l, int r):*

This is the key function that removes all nodes outside the range [l, r] while maintaining the BST properties.

The function checks the value of each node and decides whether to keep it or prune it (remove it and its subtrees).

3. Helper Functions:

inorderTraversal(Node root):*

This function performs an inorder traversal of the tree. In an inorder traversal, the left subtree is visited first, followed by the node itself, and then the right subtree. This function is used to print the tree after modification.

createNode(int data):

This is a helper function to create new nodes. It initializes a node with the given value and returns it.

4. Main Function:

Two example trees are created, and the removekeys function is applied to both trees to remove nodes outside the specified range [l, r].

The trees are then printed using the inorderTraversal function to verify the correctness of the modified BST.
*/