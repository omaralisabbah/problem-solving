/*
You are given the head of a singly linked list of positive integers. You have to check if the given linked list is palindrome or not.

Examples:

Input:
   
Output: true
Explanation: The given linked list is 1 -> 2 -> 1 -> 1 -> 2 -> 1, which is a palindrome.
Input:
   
Output: false
Explanation: The given linked list is 10 -> 20 -> 30 -> 40 -> 50, which is not a palindrome.
Constraints:
1 ≤ number of nodes ≤ 105
0 ≤ node->data ≤ 103



*/

#include <iostream>
using namespace std;

/**
 * Definition for singly-linked list node.
 */
class Node {
public:
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = nullptr;
    }
};

class Solution {
public:
    /**
     * Function to check if a linked list is a palindrome.
     * Time Complexity: O(N)
     * Space Complexity: O(1)
     */
    bool isPalindrome(Node* head) {
        if (head == nullptr || head->next == nullptr)
            return true;

        // 1. Find the middle using slow and fast pointers
        Node *slow = head, *fast = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
        }

        // 2. Reverse the second half of the list
        Node* secondHalfHead = reverseList(slow->next);
        
        // 3. Compare the first half and reversed second half
        Node* firstHalf = head;
        Node* secondHalf = secondHalfHead;
        bool isPalin = true;
        
        while (secondHalf != nullptr) {
            if (firstHalf->data != secondHalf->data) {
                isPalin = false;
                break;
            }
            firstHalf = firstHalf->next;
            secondHalf = secondHalf->next;
        }

        // (Optional) 4. Restore the list to its original state
        slow->next = reverseList(secondHalfHead);

        return isPalin;
    }

private:
    /**
     * Helper function to reverse a linked list in-place.
     */
    Node* reverseList(Node* head) {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* nextNode = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextNode;
        }
        return prev;
    }
};

/**
 * Helper function to create a linked list and test the logic.
 */
int main() {
    // Example: 1 -> 2 -> 1
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(1);

    Solution sol;
    if (sol.isPalindrome(head))
        cout << "The linked list is a palindrome." << endl;
    else
        cout << "The linked list is NOT a palindrome." << endl;

    return 0;
}
