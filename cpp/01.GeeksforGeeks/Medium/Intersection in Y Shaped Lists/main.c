#include <bits/stdc++.h>
using namespace std;

/*
 * Definition for singly-linked list node.
 */
class Node {
public:
    int data;      // Value stored in the node
    Node* next;    // Pointer to the next node

    // Constructor
    Node(int x) {
        data = x;
        next = NULL;
    }
};

/*
 * Solution class containing the intersectPoint function.
 */
class Solution {
public:
    /*
     * Function to find the intersection point of two linked lists.
     * 
     * Parameters:
     *   head1 - pointer to the head of the first linked list
     *   head2 - pointer to the head of the second linked list
     * 
     * Returns:
     *   Node* - pointer to the intersection node
     * 
     * Approach:
     *   - Use two pointers (p1 and p2).
     *   - Traverse both lists simultaneously.
     *   - When a pointer reaches the end of its list, redirect it to the head of the other list.
     *   - Eventually, both pointers will meet at the intersection node.
     * 
     * Time Complexity: O(n + m), where n and m are lengths of the two lists.
     * Space Complexity: O(1), since no extra data structures are used.
     */
    Node* intersectPoint(Node* head1, Node* head2) {
        if (!head1 || !head2) return NULL;  // Edge case: empty list

        Node* p1 = head1;
        Node* p2 = head2;

        // Traverse until both pointers meet
        while (p1 != p2) {
            // Move to next node, or switch to other list's head
            p1 = (p1 == NULL) ? head2 : p1->next;
            p2 = (p2 == NULL) ? head1 : p2->next;
        }

        // Both pointers meet at intersection node
        return p1;
    }
};

/*
 * Helper function to print a linked list.
 */
void printList(Node* head) {
    while (head != NULL) {
        cout << head->data;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

/*
 * Example usage:
 */
int main() {
    // Create common part: 15 -> 30
    Node* common = new Node(15);
    common->next = new Node(30);

    // First list: 10 -> 15 -> 30
    Node* head1 = new Node(10);
    head1->next = common;

    // Second list: 3 -> 6 -> 9 -> 15 -> 30
    Node* head2 = new Node(3);
    head2->next = new Node(6);
    head2->next->next = new Node(9);
    head2->next->next->next = common;

    Solution sol;
    Node* intersection = sol.intersectPoint(head1, head2);

    cout << "List 1: ";
    printList(head1);
    cout << "List 2: ";
    printList(head2);

    cout << "Intersection Node: " << intersection->data << endl;

    return 0;
}
