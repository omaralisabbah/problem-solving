/*
    Given the root of a Binary Tree, your task is to return its Postorder Traversal.

    Note: A postorder traversal first visits the left child (including its entire subtree), then visits the right child (including its entire subtree),
    and finally visits the node itself.

    Input: root = [19, 10, 8, 11, 13]
    Output: [11, 13, 10, 8, 19]
    Explanation: The postorder traversal of the given binary tree is [11, 13, 10, 8, 19].

    Input: root = [11, 15, N, 7]
    Output: [7, 15, 11]
    Explanation: The postorder traversal of the given binary tree is [7, 15, 11].

*/

/*
    struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};
*/

#define MAX_SIZE 100000

int* postOrder(struct Node* root, int* size) {
    int* result = (int*) malloc(MAX_SIZE * sizeof(int));
    *size = 0; 
    
    if (root == NULL) {
        return result;
    }

    struct Node* stack[MAX_SIZE];
    int top = -1;

    stack[++top] = root;

    while (top >= 0) {
        struct Node* node = stack[top--];
        result[(*size)++] = node->data;
        
        if (node->left) {
            stack[++top] = node->left;
        }
        
        if (node->right) {
            stack[++top] = node->right;
        }
    }
    
    int start = 0;
    int end = *size - 1;
    while (start < end) {
        int temp = result[start];
        result[start] = result[end];
        result[end] = temp;
        start++;
        end--;
    }

    return result;
}