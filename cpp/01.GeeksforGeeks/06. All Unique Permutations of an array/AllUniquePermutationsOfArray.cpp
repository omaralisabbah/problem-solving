/*
    Given an array arr[] that may contain duplicates. Find all possible distinct permutations of the array in sorted order.
    Note: A sequence A is greater than sequence B if there is an index i for which Aj = Bj for all j<i and Ai > Bi.

    Examples:
    Input: arr[] = [1, 3, 3]
    Output: [[1, 3, 3], [3, 1, 3], [3, 3, 1]]
    Explanation: These are the only possible distinct permutations for the given array.

    Input: arr[] = [2, 3]
    Output: [[2, 3], [3, 2]]
    Explanation: These are the only possible distinct permutations for the given array.


    Explanation:
    
    1. Sorting the Array: First, we sort the array to make sure identical elements are adjacent. This is crucial for handling duplicates effectively.
    
    2. Backtracking Function:
        - We maintain a used array to track which elements have been used in the current permutation.
        - We iterate over the array, and if an element has not been used, we add it to the current
            permutation and recursively attempt to build the rest of the permutation.
        - If we encounter a duplicate element (i.e., an element that is the same as the previous element but has not been used in the current recursion),
            we skip it to avoid generating duplicate permutations.

    3. Base Case: Once the current permutation has the same length as the input array, we add it to the result.
    4. Backtracking: After generating a valid permutation, we backtrack by unmarking the current element
                    as used and removing it from the current permutation.


    Time Complexity:
        Sorting the array takes 
        O(Nlog⁡N)
        O(NlogN), where 
        N
        N is the length of the array.

    Generating permutations with backtracking takes 
    O(N!⋅N)
    O(N!⋅N) because there are 
    N!
    N! possible permutations, and each permutation requires 
    O(N)
    O(N) operations to construct.

    Example Walkthrough:

    For the input arr = [1, 3, 3], the algorithm will:

    Sort the array: arr = [1, 3, 3]

    Start the backtracking process:

    First, it will pick 1 and try to generate permutations for [3, 3].

    Then it will add the first 3, and finally, the second 3.

    It will backtrack and explore the other possible combinations (e.g., swapping 3 and 3).
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> uniquePerms(vector<int>& arr) {
        // Sort the array to handle duplicates easily
        sort(arr.begin(), arr.end());
        
        vector<vector<int>> result;
        vector<int> currentPermutation;
        vector<bool> used(arr.size(), false); // To mark used elements during permutation

        // Backtracking function to generate permutations
        generatePermutations(arr, used, currentPermutation, result);
        
        return result;
    }

private:
    void generatePermutations(vector<int>& arr, vector<bool>& used, vector<int>& currentPermutation, vector<vector<int>>& result) {
        if (currentPermutation.size() == arr.size()) {
            result.push_back(currentPermutation);
            return;
        }
        
        for (int i = 0; i < arr.size(); ++i) {
            // Skip the element if it's already used or if it's a duplicate and the previous instance wasn't used
            if (used[i] || (i > 0 && arr[i] == arr[i - 1] && !used[i - 1])) {
                continue;
            }
            
            // Mark the element as used and add it to the current permutation
            used[i] = true;
            currentPermutation.push_back(arr[i]);
            
            // Recursively generate the rest of the permutation
            generatePermutations(arr, used, currentPermutation, result);
            
            // Backtrack: unmark the element and remove it from the current permutation
            used[i] = false;
            currentPermutation.pop_back();
        }
    }
};

int main() {
    // Test case input
    vector<int> arr = {1, 3, 3};
    
    // Create an instance of the Solution class
    Solution sol;
    
    // Get the unique permutations
    vector<vector<int>> result = sol.uniquePerms(arr);
    
    // Output the result
    cout << "Distinct permutations in sorted order:\n";
    for (const auto& perm : result) {
        cout << "[ ";
        for (int num : perm) {
            cout << num << " ";
        }
        cout << "]\n";
    }

    return 0;
}
