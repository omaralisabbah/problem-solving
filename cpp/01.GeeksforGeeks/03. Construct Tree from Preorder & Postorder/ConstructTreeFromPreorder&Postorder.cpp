/*
    Given two arrays pre[] and post[] that represent the preorder and postorder traversals of a full binary tree.
    Your task is to construct the binary tree and return its root.

    Note:  Full Binary Tree is a binary tree where every node has either 0 or 2 children.
    The preorder and postorder traversals contain unique values,
    and every value present in the preorder traversal is also found in the postorder traversal.
    
    Examples:

    Input: pre[] = [1, 2, 4, 8, 9, 5, 3, 6, 7], post[] = [8, 9, 4, 5, 2, 6, 7, 3, 1]
    Output: [1, 2, 3, 4, 5, 6, 7, 8, 9]
    Explanation: The tree will look like

    Input: pre[] = [1, 2, 4, 5, 3, 6, 7] , post[] = [4, 5, 2, 6, 7, 3, 1]
    Output: [1, 2, 3, 4, 5, 6, 7]
    Explanation: The tree will look like


*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

// ----------------- Node Definition -----------------

/**
 * Class representing a node in the binary tree.
 */
class Node {
public:
    int data;      // Value stored in the node
    Node* left;    // Pointer to left child
    Node* right;   // Pointer to right child

    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

// ----------------- Solution Class -----------------

/**
 * Class containing the method to construct a full binary tree
 * from preorder and postorder traversals.
 */
class Solution {
public:
    int preIndex = 0;  // Global index for preorder traversal

    /**
     * Recursive helper function to construct the binary tree.
     * 
     * @param pre Preorder traversal array
     * @param post Postorder traversal array
     * @param l Left boundary index in post[]
     * @param r Right boundary index in post[]
     * @param postIndexMap Map from value to index in post[]
     * @return Pointer to the constructed subtree root
     */
    Node* constructTreeUtil(vector<int>& pre, vector<int>& post, int l, int r, unordered_map<int, int>& postIndexMap) {
        // Base case: no elements to process
        if (preIndex >= pre.size() || l > r)
            return nullptr;

        // Create the root node with the current element in preorder
        Node* root = new Node(pre[preIndex++]);

        // If it's a leaf node (no children), return it
        if (l == r || preIndex >= pre.size())
            return root;

        // Find index of the next element in preorder (left child) in postorder
        int postIndex = postIndexMap[pre[preIndex]];

        // Recursively construct the left and right subtrees
        root->left = constructTreeUtil(pre, post, l, postIndex, postIndexMap);
        root->right = constructTreeUtil(pre, post, postIndex + 1, r - 1, postIndexMap);

        return root;
    }

    /**
     * Constructs the full binary tree from preorder and postorder traversals.
     * 
     * @param pre Preorder traversal array
     * @param post Postorder traversal array
     * @return Pointer to the root of the constructed binary tree
     */
    Node* constructTree(vector<int>& pre, vector<int>& post) {
        int n = pre.size();

        // Map to quickly find index of any value in post[]
        unordered_map<int, int> postIndexMap;
        for (int i = 0; i < n; ++i)
            postIndexMap[post[i]] = i;

        return constructTreeUtil(pre, post, 0, n - 1, postIndexMap);
    }
};

// ----------------- Utility: Level Order Traversal -----------------

/**
 * Prints the level order (breadth-first) traversal of the binary tree.
 * 
 * @param root Pointer to the root of the tree
 */
void printLevelOrder(Node* root) {
    if (!root) return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        cout << curr->data << " ";

        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

// ----------------- Main Function -----------------

int main() {
    // Example input: preorder and postorder traversals of a full binary tree
    vector<int> pre  = {1, 2, 4, 8, 9, 5, 3, 6, 7};
    vector<int> post = {8, 9, 4, 5, 2, 6, 7, 3, 1};

    // Create solution object and build the tree
    Solution sol;
    Node* root = sol.constructTree(pre, post);

    // Print the tree using level order traversal to verify structure
    cout << "Level Order Traversal of the constructed tree:\n";
    printLevelOrder(root);
    cout << endl;

    return 0;
}
