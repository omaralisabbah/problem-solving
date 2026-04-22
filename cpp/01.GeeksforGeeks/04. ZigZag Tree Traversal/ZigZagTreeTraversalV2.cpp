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

    V2
    Reads the binary tree input from the user via cin.
    Accepts a level-order list of values (use "N" for null nodes).
    Builds the tree.
    Performs Zigzag Traversal.
    Prints the result.

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

// -------------------- Zigzag Traversal --------------------
class Solution {
  public:
    vector<int> zigZagTraversal(Node* root) {
        vector<int> result;
        if (!root) return result;

        queue<Node*> q;
        q.push(root);
        bool leftToRight = true;

        while (!q.empty()) {
            int size = q.size();
            vector<int> level(size);

            for (int i = 0; i < size; ++i) {
                Node* curr = q.front(); q.pop();

                int index = leftToRight ? i : (size - i - 1);
                level[index] = curr->data;

                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }

            result.insert(result.end(), level.begin(), level.end());
            leftToRight = !leftToRight;
        }

        return result;
    }
};

// -------------------- Helper: Build Tree from User Input --------------------
Node* buildTree(const string& str) {
    if (str.empty() || str[0] == 'N') return nullptr;

    vector<string> values;
    istringstream iss(str);
    string val;

    while (iss >> val)
        values.push_back(val);

    Node* root = new Node(stoi(values[0]));
    queue<Node*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < values.size()) {
        Node* curr = q.front();
        q.pop();

        // Left child
        if (i < values.size() && values[i] != "N") {
            curr->left = new Node(stoi(values[i]));
            q.push(curr->left);
        }
        i++;

        // Right child
        if (i < values.size() && values[i] != "N") {
            curr->right = new Node(stoi(values[i]));
            q.push(curr->right);
        }
        i++;
    }

    return root;
}

// -------------------- Main Function --------------------
int main() {
    cout << "Enter tree nodes in level order (use 'N' for nulls):" << endl;
    cout << "Example: 7 9 7 8 8 6 N 10 9" << endl;

    string inputLine;
    getline(cin, inputLine);  // Read full line of input

    Node* root = buildTree(inputLine);

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