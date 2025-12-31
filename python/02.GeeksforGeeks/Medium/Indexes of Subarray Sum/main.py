"""
Given an array arr[] containing only non-negative integers, your task is to find a continuous subarray (a contiguous sequence of elements) whose sum equals a specified value target. You need to return the 1-based indices of the leftmost and rightmost elements of this subarray. You need to find the first subarray whose sum is equal to the target.

Note: If no such array is possible then, return [-1].

Examples:

Input: arr[] = [1, 2, 3, 7, 5], target = 12
Output: [2, 4]
Explanation: The sum of elements from 2nd to 4th position is 12.

Input: arr[] = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], target = 15
Output: [1, 5]
Explanation: The sum of elements from 1st to 5th position is 15.

Input: arr[] = [5, 3, 4], target = 2
Output: [-1]
Explanation: There is no subarray with sum 2.

Constraints:
1 <= arr.size()<= 106
0 <= arr[i] <= 103
0 <= target <= 109
"""


class Solution:
    """
    Finds a continuous subarray with a sum equal to a specified target.
    """
    def subarraySum(self, arr, target):
        """
        Finds the first continuous subarray with a sum equal to target.

        Args:
            arr (list): A list of non-negative integers.
            target (int): The target sum.

        Returns:
            list: A list containing the 1-based indices [left, right]
                  of the subarray, or [-1] if no such subarray exists.
        """
        n = len(arr)
        current_sum = 0
        left = 0

        for right in range(n):
            current_sum += arr[right]

            # Shrink the window from the left if the current sum exceeds the target
            while current_sum > target and left <= right:
                current_sum -= arr[left]
                left += 1
            
            # If the current sum equals the target, return the 1-based indices
            if current_sum == target:
                return [left + 1, right + 1]

        # Return [-1] if no such subarray is found
        return [-1]

if __name__ == "__main__":
    # Example 1
    arr1 = [1, 2, 3, 7, 5]
    target1 = 12
    result1 = Solution().subarraySum(arr1, target1)
    print(f"Input: arr[] = {arr1}, target = {target1}")
    print(f"Output: {result1}")
    print("Expected: [2, 4]\n")

    # Example 2
    arr2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
    target2 = 15
    result2 = Solution().subarraySum(arr2, target2)
    print(f"Input: arr[] = {arr2}, target = {target2}")
    print(f"Output: {result2}")
    print("Expected: [1, 5]\n")

    # Example 3
    arr3 = [5, 3, 4]
    target3 = 2
    result3 = Solution().subarraySum(arr3, target3)
    print(f"Input: arr[] = {arr3}, target = {target3}")
    print(f"Output: {result3}")
    print("Expected: [-1]\n")

    # Example 4 (No solution in middle)
    arr4 = [1, 2, 3, 4, 5]
    target4 = 100
    result4 = Solution().subarraySum(arr4, target4)
    print(f"Input: arr[] = {arr4}, target = {target4}")
    print(f"Output: {result4}")
    print("Expected: [-1]\n")
    
    # Example 5 (Target at the end)
    arr5 = [1, 2, 3, 4, 5]
    target5 = 9
    result5 = Solution().subarraySum(arr5, target5)
    print(f"Input: arr[] = {arr5}, target = {target5}")
    print(f"Output: {result5}")
    print("Expected: [4, 5]\n")
