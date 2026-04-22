/*
    Given the root of a binary tree. You have to find the zig-zag level order traversal of the binary tree.
    Note: In zig zag traversal we traverse the nodes from left to right for odd-numbered levels, and from right to left for even-numbered levels.

    Examples:

    Input: root = [7, 9, 7, 8, 8, 6, N, 10, 9]
    Output: [7, 7, 9, 8, 8, 6, 9, 10] 
    Explanation:
    Level 1 (left to right): [7]
    Level 2 (right to left): [7, 9]
    Level 3 (left to right): [8, 8, 6]
    Level 4 (right to left): [9, 10]
    Final result: [7, 7, 9, 8, 8, 6, 9, 10]

*/

#include <iostream>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;

// -------------------- Tree Node Definition --------------------
class Node {
  public:
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

// -------------------- Solution Class with Zigzag --------------------
class Solution {
  public:
    vector<int> zigZagTraversal(Node* root) {
        vector<int> result;
        if (!root) return result;

        queue<Node*> q;
        q.push(root);
        bool leftToRight = true;

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> level(levelSize);  // store values of the current level

            for (int i = 0; i < levelSize; ++i) {
                Node* curr = q.front(); q.pop();

                int index = leftToRight ? i : (levelSize - 1 - i);
                level[index] = curr->data;

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            // Add level values to result
            result.insert(result.end(), level.begin(), level.end());
            leftToRight = !leftToRight;
        }

        return result;
    }
};

// -------------------- Helper to Build Tree from Input --------------------
Node* buildTree(const vector<string>& nodes) {
    if (nodes.empty() || nodes[0] == "N")
        return nullptr;

    Node* root = new Node(stoi(nodes[0]));
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < nodes.size()) {
        Node* current = q.front();
        q.pop();

        // Left child
        if (i < nodes.size() && nodes[i] != "N") {
            current->left = new Node(stoi(nodes[i]));
            q.push(current->left);
        }
        i++;

        // Right child
        if (i < nodes.size() && nodes[i] != "N") {
            current->right = new Node(stoi(nodes[i]));
            q.push(current->right);
        }
        i++;
    }

    return root;
}

// -------------------- Main Function --------------------
int main() {
    // Example input: tree = [7, 9, 7, 8, 8, 6, N, 10, 9]
    // Represented as strings to support "N"
    vector<string> input = {"7", "9", "7", "8", "8", "6", "N", "10", "9"};

    Node* root = buildTree(input);

    Solution sol;
    vector<int> result = sol.zigZagTraversal(root);

    cout << "Zigzag Traversal: [";
    for (size_t i = 0; i < result.size(); ++i) {
        cout << result[i];
        if (i != result.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    return 0;
}
