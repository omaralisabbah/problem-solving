/*
    Given an array arr[] and an integer k, we need to count the number of pairs from the given array such that the Bitwise XOR of each pair is less than k.

Examples:

Input: arr = [1, 2, 3, 5], k = 5 
Output: 4
Explanation: Bitwise XOR of all possible pairs that satisfy the given conditions are:
arr[0] ^ arr[1] = 1 ^ 2 = 3 
arr[0] ^ arr[2] = 1 ^ 3 = 2 
arr[0] ^ arr[3] = 1 ^ 5 = 4 
arr[1] ^ arr[2] = 2 ^ 3 = 1 
Therefore, the required output is 4.

Input: arr[] = [3, 5, 6, 8], k = 7 
Output: 3
Explnation: Bitwise XOR of all possible pairs that satisfy the given conditions are:
arr[0] ^ arr[1] = 6
arr[0] ^ arr[2] = 5
arr[1] ^ arr[2] = 3
Therefore, the required output is 3. 

Constraints:
1 ≤ arr.size(), k ≤ 5*104
1 ≤ arr[i] ≤ 5*104

🔹 Naive Approach

    Iterate over all pairs (i, j) with i < j.

    Compute arr[i] ^ arr[j].

    Count if result < k.

This works fine for small arrays but is O(n²), which may be too slow if n is large (up to 50,000).
🔹 Optimized Approach

We can use a Trie (prefix tree) for binary representation of numbers:

    Insert numbers into a binary trie.

    For each number, query how many previously inserted numbers give XOR < k.

    This reduces complexity to about O(n · log(max(arr[i]))), which is feasible.
*/

/*
    Problem:
    --------
    Given an array arr[] and an integer k, count the number of pairs (i, j)
    such that arr[i] ^ arr[j] < k.

    Constraints:
    1 ≤ arr.size(), k ≤ 5*10^4
    1 ≤ arr[i] ≤ 5*10^4

    Approach:
    ---------
    - Brute force O(n^2) will time out for n up to 50,000.
    - Optimized solution uses a Binary Trie (bitwise trie).
    - For each number:
        * Query how many previously inserted numbers produce XOR < k.
        * Insert the number into the trie.
    - Complexity: O(n * log(maxValue)), where maxValue ≤ 50000 < 2^16.
      So about O(n * 16), which is efficient.

    Example:
    --------
    Input: arr = [1, 2, 3, 5], k = 5
    Output: 4
    Explanation: Valid pairs are (1^2=3), (1^3=2), (1^5=4), (2^3=1).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
    // Trie node structure
    struct TrieNode {
        TrieNode* child[2]; // child[0] for bit 0, child[1] for bit 1
        int count;          // number of elements passing through this node
        TrieNode() {
            child[0] = child[1] = nullptr;
            count = 0;
        }
    };

    // Insert a number into the trie
    void insert(TrieNode* root, int num) {
        for (int i = 15; i >= 0; i--) { // 16 bits are enough (since 50000 < 2^16)
            int bit = (num >> i) & 1;
            if (!root->child[bit]) root->child[bit] = new TrieNode();
            root = root->child[bit];
            root->count++;
        }
    }

    // Count how many numbers already in trie give XOR < k with num
    int countLessThanK(TrieNode* root, int num, int k) {
        int res = 0;
        for (int i = 15; i >= 0; i--) {
            if (!root) break;
            int bitNum = (num >> i) & 1;
            int bitK   = (k >> i) & 1;

            if (bitK == 1) {
                // If k has 1 at this bit, we can take numbers with same bitNum
                if (root->child[bitNum]) res += root->child[bitNum]->count;
                root = root->child[1 - bitNum];
            } else {
                root = root->child[bitNum];
            }
        }
        return res;
    }

public:
    int cntPairs(vector<int>& arr, int k) {
        TrieNode* root = new TrieNode();
        int ans = 0;
        for (int num : arr) {
            ans += countLessThanK(root, num, k);
            insert(root, num);
        }
        return ans;
    }
};

// Driver code for testing
int main() {
    Solution sol;

    vector<int> arr1 = {1, 2, 3, 5};
    int k1 = 5;
    cout << "Input: [1,2,3,5], k=5\nOutput: " << sol.cntPairs(arr1, k1) << "\n\n";

    vector<int> arr2 = {3, 5, 6, 8};
    int k2 = 7;
    cout << "Input: [3,5,6,8], k=7\nOutput: " << sol.cntPairs(arr2, k2) << "\n";

    return 0;
}
