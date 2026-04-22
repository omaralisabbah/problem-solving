/*
    Given the root of a Binary Search Tree and two integers l and r, the task is to find the sum of all nodes that lie between l and r, including both l and r.

    Examples

Input: root = [22, 12, 30, 8, 20], l = 10, r = 22

Output: 54
Explanation: The nodes in the given Tree that lies in the range [10, 22] are {12, 20, 22}. Therefore, the sum of nodes is 12 + 20 + 22 = 54.

Input: root = [8, 5, 11, 3, 6, N, 20], l = 11, r = 15  
Output: 11
Explanation: The nodes in the given Tree that lies in the range [11, 15] is {11}. Therefore, the sum of node is 11.

Constraints:
0 ≤ number of nodes ≤ 104
0 ≤ node->data ≤ 104
0 ≤ l ≤ r ≤ 104


To solve this problem efficiently, we can take advantage of the Binary Search Tree (BST) properties:

In a BST, the left child of a node contains values less than the node, and the right child contains values greater than the node.

So, if the current node’s value is:

less than l, we can safely skip the left subtree.

greater than r, we can safely skip the right subtree.

within [l, r], we include its value in the sum and recurse both sides.

Here is the completed nodeSum function:


Given BST:
        22
       /  \
     12    30
    /  \
   8   20
   
Range: [10, 22]

Nodes in this range: 12, 20, 22

Sum: 12 + 20 + 22 = 54

The function will correctly return 54.

*/

#include <iostream>
using namespace std;

/*
    Definition of a Node in a Binary Search Tree
*/
class Node {
  public:
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a new node with given value
    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

/*
    Class Solution containing method to calculate sum of nodes
    within a given range in a BST
*/
class Solution {
  public:
    // Function to compute the sum of all node values between l and r (inclusive)
    int nodeSum(Node* root, int l, int r) {
        if (root == NULL) return 0;

        // If current node is within range, include its value and explore both subtrees
        if (root->data >= l && root->data <= r) {
            return root->data 
                   + nodeSum(root->left, l, r) 
                   + nodeSum(root->right, l, r);
        }

        // If current node's value is less than l, explore right subtree only
        if (root->data < l) {
            return nodeSum(root->right, l, r);
        }

        // If current node's value is greater than r, explore left subtree only
        return nodeSum(root->left, l, r);
    }
};

/*
    Helper function to insert a value into the BST
*/
Node* insert(Node* root, int val) {
    if (root == NULL) return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

/*
    Main function to demonstrate the functionality
*/
int main() {
    // Manually constructing the BST:
    //         22
    //        /  \
    //      12    30
    //     /  \
    //    8   20

    Node* root = NULL;
    root = insert(root, 22);
    insert(root, 12);
    insert(root, 30);
    insert(root, 8);
    insert(root, 20);

    int l = 10, r = 22;

    Solution sol;
    int result = sol.nodeSum(root, l, r);

    cout << "Sum of nodes in range [" << l << ", " << r << "] is: " << result << endl;

    return 0;
}
