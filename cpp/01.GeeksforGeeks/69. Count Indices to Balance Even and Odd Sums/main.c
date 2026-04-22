/*
    Given an array arr[], count the number of indices such that deleting the element at that index and shifting all elements after it one position left results in an array where the sum of elements at even indices equals the sum at odd indices.

Examples:

Input: arr[] = [2, 1, 6, 4]
Output: 1
Explaination: After removing arr[1], the resulting array will be [2, 6, 4] the sums of elements at odd index is arr[1] = 6 and the sum of elements at even index is arr[0] + arr[2] = 6.
Input: arr[] = [1, 1, 1]
Output: 3
Explaination: Removing any element makes the sum of odd and even indexed elements equal.
Constraints:
1 ≤ arr.size() ≤ 105
0 ≤ arr[i] ≤ 104


*/
/*
    Problem:
    --------
    Given an array arr[], count the number of indices such that deleting the element
    at that index and shifting all elements after it one position left results in an array
    where the sum of elements at even indices equals the sum at odd indices.

    Example 1:
    ----------
    Input: arr[] = [2, 1, 6, 4]
    Output: 1
    Explanation:
        - Removing arr[1] → new array = [2, 6, 4]
        - Even indices sum = arr[0] + arr[2] = 2 + 4 = 6
        - Odd indices sum = arr[1] = 6
        - Equal → valid index.

    Example 2:
    ----------
    Input: arr[] = [1, 1, 1]
    Output: 3
    Explanation:
        - Removing any element results in equal sums.

    Constraints:
    ------------
    1 ≤ arr.size() ≤ 10^5
    0 ≤ arr[i] ≤ 10^4

    Approach:
    ---------
    1. Compute total sums of elements at even indices and odd indices.
    2. Iterate through each index i:
       - Temporarily remove arr[i] from totals.
       - After removal, all elements after i shift left → parity flips.
       - New even sum = prefixEven + remainingOdd
       - New odd sum  = prefixOdd + remainingEven
       - If equal, increment count.
    3. Return count.

    Time Complexity: O(n)
    Space Complexity: O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int cntWays(vector<int>& arr) {
        int n = arr.size();
        
        // Step 1: Compute total sums of even and odd indices
        long long totalEven = 0, totalOdd = 0;
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) totalEven += arr[i];
            else totalOdd += arr[i];
        }
        
        // Step 2: Iterate through each index
        long long prefixEven = 0, prefixOdd = 0;
        int count = 0;
        
        for (int i = 0; i < n; i++) {
            // Remove arr[i] from totals
            if (i % 2 == 0) totalEven -= arr[i];
            else totalOdd -= arr[i];
            
            // New sums after removal
            long long newEven = prefixEven + totalOdd;
            long long newOdd  = prefixOdd + totalEven;
            
            if (newEven == newOdd) count++;
            
            // Update prefix sums
            if (i % 2 == 0) prefixEven += arr[i];
            else prefixOdd += arr[i];
        }
        
        return count;
    }
};

// Driver code for testing
int main() {
    Solution sol;
    
    vector<int> arr1 = {2, 1, 6, 4};
    cout << "Output for [2,1,6,4]: " << sol.cntWays(arr1) << endl; // Expected 1
    
    vector<int> arr2 = {1, 1, 1};
    cout << "Output for [1,1,1]: " << sol.cntWays(arr2) << endl; // Expected 3
    
    vector<int> arr3 = {5, 5, 2, 5, 8};
    cout << "Output for [5,5,2,5,8]: " << sol.cntWays(arr3) << endl;
    
    return 0;
}
