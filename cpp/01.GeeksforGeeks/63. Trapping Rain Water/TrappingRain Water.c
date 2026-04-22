/*
Given an array arr[] with non-negative integers representing the height of blocks. If the width of each block is 1, compute how much water can be trapped between the blocks during the rainy season. 

Examples:

Input: arr[] = [3, 0, 1, 0, 4, 0 2]
Output: 10
Explanation: Total water trapped = 0 + 3 + 2 + 3 + 0 + 2 + 0 = 10 units.

Input: arr[] = [3, 0, 2, 0, 4]
Output: 7
Explanation: Total water trapped = 0 + 3 + 1 + 3 + 0 = 7 units.

Input: arr[] = [1, 2, 3, 4]
Output: 0
Explanation: We cannot trap water as there is no height bound on both sides.

Input: arr[] = [2, 1, 5, 3, 1, 0, 4]
Output: 9
Explanation: Total water trapped = 0 + 1 + 0 + 1 + 3 + 4 + 0 = 9 units.

Constraints:
1 < arr.size() < 105
0 < arr[i] < 103


Perfect, this is the Trapping Rain Water problem. We need to compute how much water can be trapped between blocks of varying heights.
🔑 Key Idea

    Water trapped at index i depends on:

water[i]=min⁡(maxLeft[i],maxRight[i])−height[i]\text{water}[i] = \min(\text{maxLeft}[i], \text{maxRight}[i]) - \text{height}[i]

    maxLeft[i]: tallest block to the left of i.

    maxRight[i]: tallest block to the right of i.

    If this value is positive, it contributes to trapped water.

📝 Algorithm

    Precompute leftMax[i] for each index.

    Precompute rightMax[i] for each index.

    For each index, add:

ans+=max⁡(0,min⁡(leftMax[i],rightMax[i])−arr[i])\text{ans} += \max(0, \min(leftMax[i], rightMax[i]) - arr[i])

    Return total.

    
*/

/*
  Problem:
  --------
  Given an array arr[] representing block heights, compute how much water
  can be trapped between the blocks during the rainy season.

  Approach:
  ---------
  - For each index, water trapped depends on the tallest block to its left
    and the tallest block to its right.
  - Formula:
      water[i] = min(leftMax[i], rightMax[i]) - arr[i]
    (only if positive).
  - Precompute leftMax and rightMax arrays in O(n).
  - Sum up trapped water.

  Complexity:
  -----------
  - Time: O(n)
  - Space: O(n) (can be optimized to O(1) using two pointers)

  Example:
  --------
  Input: [3, 0, 2, 0, 4]
  Output: 7
  
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxWater(vector<int> &arr) {
        int n = arr.size();
        if (n <= 2) return 0; // no water can be trapped
        
        vector<int> leftMax(n), rightMax(n);
        
        // Compute leftMax
        leftMax[0] = arr[0];
        for (int i = 1; i < n; i++) {
            leftMax[i] = max(leftMax[i - 1], arr[i]);
        }
        
        // Compute rightMax
        rightMax[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            rightMax[i] = max(rightMax[i + 1], arr[i]);
        }
        
        // Calculate trapped water
        int water = 0;
        for (int i = 0; i < n; i++) {
            water += min(leftMax[i], rightMax[i]) - arr[i];
        }
        
        return water;
    }
};

int main() {
    Solution sol;
    vector<int> arr = {3, 0, 2, 0, 4};
    cout << "Water trapped = " << sol.maxWater(arr) << "\n"; // Output: 7
    return 0;
}
