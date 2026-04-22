/*
    You are given the root of a binary tree, and your task is to return its bottom view.
    The bottom view of a binary tree is the set of nodes visible when the tree is viewed from the bottom.

    Note: If there are multiple bottom-most nodes for a horizontal distance from the root,
    then the latter one in the level order traversal is considered.

    Examples :

    Input: root = [1, 2, 3, 4, 5, N, 6]
    Output: [4, 2, 5, 3, 6]
    Explanation: The Green nodes represent the bottom view of below binary tree.

         1
        / \
       2   3
    / \    \
   4   5    6


    Input: root = [20, 8, 22, 5, 3, 4, 25, N, N, 10, 14, N, N, 28, N]        
    Output: [5, 10, 4, 28, 25]
    Explanation: The Green nodes represent the bottom view of below binary tree.

    Tree:
            20
           /  \
          8   22
         / \   \ 
        5   3   25
           / \    
         10  14
             /
           28
    
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

// --------------------- Node Definition ---------------------

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

// --------------------- Solution Class ---------------------

class Solution {
public:
    /**
     * Function to return the bottom view of a binary tree.
     *
     * @param root Pointer to the root of the binary tree
     * @return Vector containing the bottom view from left to right
     */
    vector<int> bottomView(Node* root) {
        vector<int> result;
        if (!root) return result;

        // Map to store the bottommost node at each horizontal distance (HD)
        map<int, int> hdNodeMap;

        // Queue to hold pairs of (node, HD) for level order traversal
        queue<pair<Node*, int>> q;

        // Start with root at horizontal distance 0
        q.push({root, 0});

        while (!q.empty()) {
            auto [node, hd] = q.front();
            q.pop();

            // For bottom view: overwrite previous entry at hd
            hdNodeMap[hd] = node->data;

            if (node->left)
                q.push({node->left, hd - 1});

            if (node->right)
                q.push({node->right, hd + 1});
        }

        // Extract the bottom view from the map
        for (auto& [hd, value] : hdNodeMap) {
            result.push_back(value);
        }

        return result;
    }
};


int main() {
    /*
        Tree:
            20
           /  \
          8   22
         / \   \ 
        5   3   25
           / \    
         10  14
             /
           28
    */

    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(5);
    root->left->right = new Node(3);
    root->right->right = new Node(25);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);
    root->left->right->right->left = new Node(28);

    Solution sol;
    vector<int> view = sol.bottomView(root);

    cout << "Bottom View: ";
    for (int val : view)
        cout << val << " ";
    cout << endl;

    return 0;
}