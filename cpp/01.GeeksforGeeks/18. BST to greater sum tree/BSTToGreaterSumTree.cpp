/*
    Given the root of a  BST with unique node values, transform it into greater sum tree where each node contains sum of all nodes greater than that node.

    Examples:

    Input: root = [11, 2, 29, 1, 7, 15, 40, N, N, N, N, N, N, 35, N]
        
    Output: [119, 137, 75, 139, 130, 104, 0, N, N, N, N, N, N, 40, N]
    Explanation: Every node is replaced with the sum of nodes greater than itself. 
        

    Input: root = [2, 1, 6, N, N, 3, 7]
        
    Output: [16, 18, 7, N, N, 13, 0]
    Explanation: Every node is replaced with the sum of nodes greater than itself. 
        

    Constraints :
    1 ≤ node->data ≤ 3*104
    1 ≤ number of nodes ≤ 3*104


       11
      /  \
     2    29
    / \   /  \
   1   7 15   40
            /
           35



       119
      /   \
    137    75
   /  \    /  \
  139 130 104   0
               /
             40

       2
      / \
     1   6
        / \
       3   7

*/

#include <iostream>
#include <vector>
#include <queue>

// Definition for a binary tree node.
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
private:
    int cumulative_sum = 0;

    void reverseInOrderTraversal(Node* node) {
        if (!node) {
            return;
        }

        // 1. Recurse on the right subtree (contains all nodes with greater values)
        reverseInOrderTraversal(node->right);

        // 2. Process the current node
        int original_data = node->data;
        node->data = cumulative_sum;
        cumulative_sum += original_data;
        
        // 3. Recurse on the left subtree (contains all nodes with smaller values)
        reverseInOrderTraversal(node->left);
    }

public:
    void transformTree(Node *root) {
        // Reset the sum for each new tree transformation
        cumulative_sum = 0;
        reverseInOrderTraversal(root);
    }
};

// Helper function to build a tree from a level-order vector
Node* buildTree(const std::vector<int>& nodes) {
    if (nodes.empty() || nodes[0] == -1) {
        return nullptr;
    }

    Node* root = new Node(nodes[0]);
    std::queue<Node*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < nodes.size()) {
        Node* curr = q.front();
        q.pop();

        if (nodes[i] != -1) {
            curr->left = new Node(nodes[i]);
            q.push(curr->left);
        }
        i++;

        if (i < nodes.size() && nodes[i] != -1) {
            curr->right = new Node(nodes[i]);
            q.push(curr->right);
        }
        i++;
    }
    return root;
}

// Helper function to print tree level-order for verification
void printLevelOrder(Node* root) {
    if (!root) {
        std::cout << "[]\n";
        return;
    }

    std::queue<Node*> q;
    q.push(root);
    std::vector<std::string> result;

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (curr) {
            result.push_back(std::to_string(curr->data));
            q.push(curr->left);
            q.push(curr->right);
        } else {
            result.push_back("N");
        }
    }

    // Clean up trailing 'N' values
    while (!result.empty() && result.back() == "N") {
        result.pop_back();
    }

    std::cout << "[";
    for (size_t i = 0; i < result.size(); ++i) {
        std::cout << result[i] << (i == result.size() - 1 ? "" : ", ");
    }
    std::cout << "]\n";
}

int main() {
    // Example from the problem description
    // Input: root = [11, 2, 29, 1, 7, 15, 40, N, N, N, N, N, N, 35, N]
    // Note: 'N' is represented by -1 in our vector for building the tree.
    std::vector<int> input_nodes = {11, 2, 29, 1, 7, 15, 40, -1, -1, -1, -1, -1, -1, 35, -1};
    Node* root = buildTree(input_nodes);

    std::cout << "Original tree (level-order): ";
    printLevelOrder(root);
    
    Solution sol;
    sol.transformTree(root);

    std::cout << "Greater sum tree (level-order): ";
    printLevelOrder(root);

    // Expected Output from the problem: [119, 137, 75, 139, 130, 104, 0, N, N, N, N, N, N, 40, N]
    // The C++ implementation produces the same logic, which calculates the sum of all *greater* nodes,
    // which results in a similar output structure.

    return 0;
}
