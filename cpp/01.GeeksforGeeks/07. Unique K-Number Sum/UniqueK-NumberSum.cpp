/*
    Given two integers n and k, the task is to find all valid combinations of k numbers that adds up to n based on the following conditions:

    Only numbers from the range [1, 9] used.
    Each number can only be used at most once.

    Note: You can return the combinations in any order, the driver code will print them in sorted order.

    Examples:

    Input: n = 9, k = 3
    Output: [[1, 2, 6], [1, 3, 5], [2, 3, 4]]
    Explanation: There are three valid combinations of 3 numbers that sum to 9: [1 ,2, 6], [1, 3, 5] and [2, 3, 4].

    Input: n = 3, k = 3
    Output: []
    Explanation: It is not possible to pick 3 distinct numbers from 1 to 9 that sum to 3, so no valid combinations exist.

    Constraints:
    1 ≤ n ≤ 50
    1 ≤ k ≤ 9

    -------------------------

    To solve this problem, we can use backtracking to explore all possible combinations of numbers from the range [1, 9] that sum up to n with exactly k numbers. Here's the step-by-step approach:

Approach:

Backtracking:

We'll start with an empty combination and try to add numbers one by one, starting from 1 to 9.

If we have selected k numbers and their sum is equal to n, then we have found a valid combination.

If at any point, the sum exceeds n or if we have selected more than k numbers, we can prune that branch of the search (backtrack).

Constraints:

We only use numbers in the range [1, 9].

Each number can be used only once.

We need exactly k numbers.

Termination:

If we have selected exactly k numbers and their sum is equal to n, it's a valid combination.

If we have exhausted all possibilities and cannot form such a combination, we return an empty list.

Plan:

Backtracking Function: This function will try to pick a number from 1 to 9 and either include it in the current combination or skip it.

Recursion Depth: We maintain the current depth (i.e., how many numbers we've picked) and backtrack when necessary.



Explanation:

combinationSum function:

This is the main function that initializes the result vector and starts the backtracking process by calling the backtrack function.

backtrack function:

This function is responsible for exploring all possible combinations of k numbers that sum up to n.

Base Case 1: If the combination has exactly k elements and their sum equals n, it adds the combination to the result.

Base Case 2: If the combination exceeds k elements or the sum is greater than n, it stops further exploration (prunes the search).

Recursive Case: It tries every number starting from start to 9 and recursively attempts to add numbers to the current combination. It also ensures that each number is used at most once by using i + 1 as the start for the next recursion.

Main Function:

The main function tests the combinationSum method with two test cases:

The first case uses n = 9 and k = 3 to find combinations of 3 numbers that sum up to 9.

The second case uses n = 3 and k = 3 to demonstrate the case where no valid combinations exist.

*/

#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    // Main function to find all combinations that sum to n using exactly k numbers
    vector<vector<int>> combinationSum(int n, int k) {
        vector<vector<int>> result;
        vector<int> currentCombination;
        backtrack(n, k, 1, currentCombination, result);
        return result;
    }

private:
    // Helper function for backtracking
    void backtrack(int n, int k, int start, vector<int>& currentCombination, vector<vector<int>>& result) {
        // If we have selected k numbers and their sum is n, we found a valid combination
        if (currentCombination.size() == k && n == 0) {
            result.push_back(currentCombination);
            return;
        }
        
        // If the combination is invalid (either too many numbers or the sum is too large), backtrack
        if (currentCombination.size() > k || n < 0) {
            return;
        }

        // Try every number from 'start' to '9'
        for (int i = start; i <= 9; ++i) {
            currentCombination.push_back(i);  // Pick the number
            backtrack(n - i, k, i + 1, currentCombination, result);  // Recurse with reduced n
            currentCombination.pop_back();  // Backtrack, remove the last number
        }
    }
};

int main() {
    Solution sol;
    
    // Test Case 1
    int n = 9, k = 3;
    vector<vector<int>> result = sol.combinationSum(n, k);
    
    cout << "Valid combinations for n = " << n << " and k = " << k << ":\n";
    for (const auto& combination : result) {
        cout << "[ ";
        for (int num : combination) {
            cout << num << " ";
        }
        cout << "]\n";
    }
    
    // Test Case 2
    n = 3, k = 3;
    result = sol.combinationSum(n, k);
    
    cout << "Valid combinations for n = " << n << " and k = " << k << ":\n";
    if (result.empty()) {
        cout << "No valid combinations\n";
    } else {
        for (const auto& combination : result) {
            cout << "[ ";
            for (int num : combination) {
                cout << num << " ";
            }
            cout << "]\n";
        }
    }

    return 0;
}
