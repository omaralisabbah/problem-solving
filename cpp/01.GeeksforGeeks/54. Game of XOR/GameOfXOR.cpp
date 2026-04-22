/*
    Game of XOR

You are given an integer array arr[]. The value of a subarray is defined as the bitwise XOR of all elements in that subarray.
Your task is to compute the bitwise XOR of the values of all possible subarrays of arr[].

Examples:

Input: arr[] = [1, 2, 3] 
Output: 2
Explanation:
xor[1] = 1
xor[1, 2] = 3
xor[2, 3] = 1
xor[1, 2, 3] = 0
xor[2] = 2
xor[3] = 3
Result : 1 ^ 3 ^ 1 ^ 0 ^ 2 ^ 3 = 2

Input: arr[] = [1, 2]
Output: 0
Explanation:
xor[1] = 1
xor[1, 2] = 3
xor[2] = 2
Result : 1 ^ 3 ^ 2 = 0

Constraints:
1 ≤ arr.size() ≤ 105
0 ≤ arr[i] ≤ 109


🔎 Key Insight

We need the XOR of all subarray XORs. Instead of brute-forcing (which would be O(n2)O(n^2)), we can use a mathematical observation:

    Each element arr[i] contributes to many subarrays.

    Specifically, arr[i] appears in (i+1) × (n-i) subarrays:

        (i+1) choices for the starting index (0 to i)

        (n-i) choices for the ending index (i to n-1)

Now, if an element appears in an even number of subarrays, its contribution cancels out (because XORing a number an even number of times = 0). If it appears in an odd number of subarrays, it contributes to the final answer.
⚡ Efficient Approach

    Compute (i+1) * (n-i) for each index i.

    If this count is odd, XOR arr[i] into the result.

    Return the final XOR.

This works in O(n) time and O(1) extra space.
*/