/*
    Given the root of a binary tree, your task is to find the maximum path sum. The path may start and end at any node in the tree.

    Input: root[] = [10, 2, 10, 20, 1, N, -25, N, N, N, N, 3, 4]
    Output: 42
    Explanation: Max path sum is represented using green colour nodes in the above binary tree.


    Example Use (with tree construction)
    // Input tree: [10, 2, 10, 20, 1, N, -25, N, N, N, N, 3, 4]

            10
         /    \
        2      10
       / \       \
     20   1      -25
                   / \
                  3   4

    // Tree construction for this input:
    Node* root = new Node(10);
    root->left = new Node(2);
    root->right = new Node(10);
    root->left->left = new Node(20);
    root->left->right = new Node(1);
    root->right->right = new Node(-25);
    root->right->right->left = new Node(3);
    root->right->right->right = new Node(4);

    Solution sol;
    cout << "Max Path Sum: " << sol.findMaxSum(root) << endl;  // Output: 42

    Output: Max Path Sum: 42
*/

#include <iostream>
#include <climits>
#include <algorithm>
using namespace std;

// --------------------- Node Definition ---------------------

/**
 * Class representing a node in the binary tree.
 */
class Node {
public:
    int data;       // Node's value
    Node *left;     // Pointer to the left child
    Node *right;    // Pointer to the right child

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// --------------------- Solution Class ---------------------

/**
 * Class that provides a method to compute the maximum path sum
 * in a binary tree.
 */
class Solution {
private:
    int maxSum; // Tracks the maximum path sum found so far

    /**
     * Recursive helper function to compute maximum path sum downward from the given node.
     *
     * @param node Current node
     * @return Maximum path sum starting from this node and going down
     */
    int maxPathDown(Node* node) {
        if (!node) return 0;

        // Recurse on left and right subtrees and ignore negative sums
        int leftGain = max(0, maxPathDown(node->left));
        int rightGain = max(0, maxPathDown(node->right));

        // Maximum path sum through the current node (includes both children)
        int currentPathSum = node->data + leftGain + rightGain;

        // Update global max if this path is better
        maxSum = max(maxSum, currentPathSum);

        // Return the best one-sided path sum going up to parent
        return node->data + max(leftGain, rightGain);
    }

public:
    /**
     * Main function to be called to find the max path sum in the tree.
     *
     * @param root Root of the binary tree
     * @return Maximum path sum
     */
    int findMaxSum(Node* root) {
        maxSum = INT_MIN;
        maxPathDown(root);
        return maxSum;
    }
};

// --------------------- Tree Construction (Example) ---------------------

/**
 * Helper function to build the tree from the given input.
 * This manually constructs the tree corresponding to:
 * 
 *           10
 *         /    \
 *        2      10
 *       / \       \
 *     20   1      -25
 *                  / \
 *                 3   4
 *
 * Corresponds to input: [10, 2, 10, 20, 1, N, -25, N, N, N, N, 3, 4]
 */
Node* buildSampleTree() {
    Node* root = new Node(10);
    root->left = new Node(2);
    root->right = new Node(10);
    root->left->left = new Node(20);
    root->left->right = new Node(1);
    root->right->right = new Node(-25);
    root->right->right->left = new Node(3);
    root->right->right->right = new Node(4);
    return root;
}

// --------------------- Main Function ---------------------

int main() {
    // Build the tree
    Node* root = buildSampleTree();

    // Create solution object and compute max path sum
    Solution sol;
    int maxPathSum = sol.findMaxSum(root);

    // Output the result
    cout << "Maximum Path Sum: " << maxPathSum << endl;

    return 0;
}