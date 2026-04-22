/*
    Given a sorted array arr[] containing distinct positive integers that has been rotated at some unknown pivot, and a value x. Your task is to count the number of elements in the array that are less than or equal to x.

Examples:

Input: arr[] = [4, 5, 8, 1, 3], x = 6
Output: 4
Explanation: 1, 3, 4 and 5 are less than 6, so the count of all elements less than 6 is 4.

Input: arr[] = [6, 10, 12, 15, 2, 4, 5], x = 14
Output: 6
Explanation: All elements except 15 are less than 14, so the count of all elements less than 14 is 6.

Constraints:
1 ≤ arr.size() ≤ 105
0 ≤ arr[i], x ≤ 109




*/

#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    --------
    Given a sorted array (with distinct positive integers) that has been rotated 
    at some unknown pivot, and a value x. We need to count how many elements 
    in the array are less than or equal to x.

    Example:
    --------
    Input: arr = [6, 10, 12, 15, 2, 4, 5], x = 14
    Output: 6
    Explanation: Elements <= 14 are [6, 10, 12, 2, 4, 5] → count = 6

    Approach:
    ---------
    1. Find the pivot (index of the smallest element) using binary search.
       - This splits the rotated array into two sorted halves.
    2. Perform binary search (upper bound) in both halves to count elements ≤ x.
    3. Add counts from both halves.

    Complexity:
    ------------
    - Pivot search: O(log n)
    - Two binary searches: O(log n)
    - Total: O(log n), efficient for n up to 1e5.
*/

class Solution {
public:
    // Main function to count elements <= x
    int countLessEqual(vector<int>& arr, int x) {
        int n = arr.size();
        
        // Step 1: Find pivot (index of smallest element)
        int pivot = findPivot(arr);
        
        // Step 2: Count elements <= x in both sorted halves
        int count = 0;
        count += upperBound(arr, pivot, n - 1, x);   // right half
        count += upperBound(arr, 0, pivot - 1, x);   // left half
        
        return count;
    }

private:
    // Function to find pivot (smallest element index) in rotated sorted array
    int findPivot(vector<int>& arr) {
        int low = 0, high = arr.size() - 1;
        while (low < high) {
            int mid = (low + high) / 2;
            if (arr[mid] > arr[high]) 
                low = mid + 1;   // pivot lies to the right
            else 
                high = mid;      // pivot lies to the left or at mid
        }
        return low; // pivot index
    }

    // Function to count elements <= x in arr[l..r] (sorted subarray)
    int upperBound(vector<int>& arr, int l, int r, int x) {
        if (l > r) return 0; // empty range
        int low = l, high = r, ans = l - 1;
        while (low <= high) {
            int mid = (low + high) / 2;
            if (arr[mid] <= x) {
                ans = mid;       // valid candidate
                low = mid + 1;   // search right
            } else {
                high = mid - 1;  // search left
            }
        }
        return ans - l + 1; // number of elements <= x
    }
};

// -------------------------
// Driver Code for Testing
// -------------------------
int main() {
    Solution sol;

    // Example 1
    vector<int> arr1 = {4, 5, 8, 1, 3};
    int x1 = 6;
    cout << "Count <= " << x1 << " : " << sol.countLessEqual(arr1, x1) << endl;
    // Expected Output: 4

    // Example 2
    vector<int> arr2 = {6, 10, 12, 15, 2, 4, 5};
    int x2 = 14;
    cout << "Count <= " << x2 << " : " << sol.countLessEqual(arr2, x2) << endl;
    // Expected Output: 6

    // Example 3 (edge case: all elements smaller)
    vector<int> arr3 = {7, 9, 11, 1, 3, 5};
    int x3 = 12;
    cout << "Count <= " << x3 << " : " << sol.countLessEqual(arr3, x3) << endl;
    // Expected Output: 6 (all elements)

    return 0;
}
