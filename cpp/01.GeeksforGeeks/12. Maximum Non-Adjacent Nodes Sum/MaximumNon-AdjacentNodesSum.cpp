/*
    Given the root of a binary tree with integer values.
    Your task is to select a subset of nodes such that the sum of their values is maximized,
    with the condition that no two selected nodes are directly connected that is,
    if a node is included in the subset, neither its parent nor its children can be included.

    Examples:

    Input: root = [11, 1, 2]
    Output: 11
    Explanation: The maximum sum is obtained by selecting the node 11.

    Input: root = [1, 2, 3, 4, N, 5, 6]
    Output: 16
    Explanation: The maximum sum is obtained by selecting the nodes 1, 4, 5 and 6,
    which are not directly connected to each other. Their total sum is 16.

    Constraints:
    1 ≤ number of nodes ≤ 104
    1 ≤ node.data ≤ 105

    To solve this problem, we need to find a subset of nodes such that the sum of their values is maximized, with the constraint that no two selected nodes are directly connected. This problem can be efficiently solved using dynamic programming with the concept of tree DP.

Approach:

We can think of two choices for each node:

Include the node in the subset: If we include the node in our subset, we cannot include its children, so we need to add the value of this node to the sum of the optimal solution for its left and right subtrees (but excluding its children).

Exclude the node from the subset: If we exclude the node, we can freely choose to include or exclude its left and right children.

To keep track of this, we'll define a helper function getMaxSum(Node* root) that will return the maximum sum for the subtree rooted at the current node. We will compute two values for each node:

The maximum sum when including the node.

The maximum sum when excluding the node.

Dynamic Programming States:

For each node:

include[node]: The maximum sum when the node is included in the subset.

exclude[node]: The maximum sum when the node is excluded from the subset.

Transition:

If we include a node, we cannot include its left or right child. Therefore:

include[node] = node->data + exclude[left] + exclude[right]

If we exclude a node, we can freely include or exclude its children:

exclude[node] = max(include[left], exclude[left]) + max(include[right], exclude[right])



Explanation:

Node Class: Represents a binary tree node with a value (data) and two pointers to the left and right children.

Solution Class:

The getMaxSumUtil function calculates the maximum sum for a given node, returning both possible results: when the node is included and when it is excluded.

The getMaxSum function calls getMaxSumUtil and returns the maximum of the two options for the root node.

Main Function:

Creates a simple binary tree with the root node value 11 and its children 1 and 2.

Then, it calls the getMaxSum method to compute the maximum sum and prints it.
*/

#include <iostream>
#include <algorithm>
using namespace std;

// Definition for a binary tree node.
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    // Helper function to calculate the maximum sum in a tree
    pair<int, int> getMaxSumUtil(Node* root) {
        if (root == nullptr) {
            return {0, 0};  // No node, no sum
        }

        // Get the results from the left and right subtree
        pair<int, int> left = getMaxSumUtil(root->left);
        pair<int, int> right = getMaxSumUtil(root->right);

        // Calculate the maximum sum when including the current node
        int include = root->data + left.second + right.second;

        // Calculate the maximum sum when excluding the current node
        int exclude = max(left.first, left.second) + max(right.first, right.second);

        // Return both include and exclude values
        return {include, exclude};
    }

    // Main function to return the maximum sum
    int getMaxSum(Node* root) {
        pair<int, int> result = getMaxSumUtil(root);
        // We return the maximum of including or excluding the root node
        return max(result.first, result.second);
    }
};

int main() {
    // Creating a sample tree
    Node* root = new Node(11);
    root->left = new Node(1);
    root->right = new Node(2);

    // Creating an instance of Solution and getting the result
    Solution solution;
    cout << "Maximum sum of non-adjacent nodes: " << solution.getMaxSum(root) << endl;

    return 0;
}
