/*
    You are given the root of a binary tree with n nodes, where each node contains a certain number of candies,
    and the total number of candies across all nodes is n.
    In one move, you can select any two adjacent nodes and transfer one candy from one node to the other.
    The transfer can occur between a parent and child in either direction.

    The task is to determine the minimum number of moves required to ensure that every node in the tree has exactly one candy.
    Note: The testcases are framed such that it is always possible to achieve a configuration
    in which every node has exactly one candy, after some moves.

    Examples:
    
    Input: root = [5, 0, 0, N, N, 0, 0]
    Output: 6
    Explanation:
    Move 1 candy from root to left child
    Move 1 candy from root to right child
    Move 1 candy from right child to root->right->left node
    Move 1 candy from root to right child
    Move 1 candy from right child to root->right->right node
    Move 1 candy from root to right child
    so, total 6 moves required.

    Input: root = [2, 0, 0, N, N, 3, 0]
    Output: 4
    Explanation:
    Move 1 candy from root to left child
    Move 1 candy from root->right->left node to root->right node
    Move 1 candy from root->right node to root->right->right node
    Move 1 candy from root->right->left node to root->right node
    so, total 4 moves required.
*/

#include <iostream>
#include <cmath>

using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a node with a given number of candies
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};

class Solution {
public:
    // Main function to calculate the minimum number of moves required
    int distCandy(Node* root) {
        int moves = 0;  // This will keep track of the total number of moves
        // Call the helper function to perform DFS and calculate moves
        dfs(root, moves);
        return moves;  // Return the total number of moves
    }

    // Helper function for post-order DFS traversal
    // It returns the total excess of candies for the current subtree
    int dfs(Node* root, int& moves) {
        if (root == nullptr) {
            return 0;  // If the node is NULL, return 0 as there is no excess candy
        }

        // Recursively calculate the excess of candies in the left and right subtrees
        int leftExcess = dfs(root->left, moves);
        int rightExcess = dfs(root->right, moves);

        // Calculate the total excess for the current node
        // The excess for the node is its candies minus 1 (since each node needs exactly 1 candy)
        int totalExcess = leftExcess + rightExcess + (root->data - 1);

        // The number of moves required to balance the current node is the absolute value of the total excess
        // We add the absolute excess of candies to the move count
        moves += abs(totalExcess);

        // Return the total excess of candies to be propagated upwards
        return totalExcess;
    }
};


int main() {
    // Construct the tree: 
    //         5
    //        / \
    //       0   0
    //          / \
    //         0   0
    Node* root = new Node(5);
    root->left = new Node(0);
    root->right = new Node(0);
    root->right->left = new Node(0);
    root->right->right = new Node(0);

    // Create an object of Solution class and call distCandy method
    Solution sol;
    int result = sol.distCandy(root);

    // Output the result
    cout << "Minimum moves required: " << result << endl;

    return 0;
}