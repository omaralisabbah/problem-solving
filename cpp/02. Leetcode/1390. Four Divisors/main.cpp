/**
 * @file sum_four_divisors.cpp
 * @brief Program to compute the sum of divisors of integers in an array
 *        that have exactly four divisors.
 *
 * Problem:
 * Given an integer array nums, return the sum of divisors of the integers
 * in that array that have exactly four divisors. If there is no such integer
 * in the array, return 0.
 *
 * Example:
 * Input: nums = [21,4,7]
 * Output: 32
 *
 * Explanation:
 * 21 has 4 divisors: 1, 3, 7, 21 → sum = 32
 * 4 has 3 divisors: 1, 2, 4 → ignored
 * 7 has 2 divisors: 1, 7 → ignored
 *
 * Constraints:
 * 1 <= nums.length <= 10^4
 * 1 <= nums[i] <= 10^5
 */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution {
public:
    // Helper function to check primality
    bool isPrime(int n) {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }

    int sumFourDivisors(vector<int>& nums) {
        int total = 0;

        for (int n : nums) {
            int sum = 0;

            // Case 1: Check if n is cube of a prime
            int root = round(pow(n, 1.0 / 3));
            if (root * root * root == n && isPrime(root)) {
                sum = 1 + root + root * root + n;
            } else {
                // Case 2: Check if n = p * q (distinct primes)
                for (int i = 2; i * i <= n; i++) {
                    if (n % i == 0) {
                        int j = n / i;
                        if (i != j && isPrime(i) && isPrime(j)) {
                            sum = 1 + i + j + n;
                        }
                        break; // only need first factor
                    }
                }
            }

            total += sum;
        }

        return total;
    }
};

// Example usage
int main() {
    Solution sol;

    vector<int> nums1 = {21, 4, 7};
    cout << "Output for [21,4,7]: " << sol.sumFourDivisors(nums1) << endl;

    vector<int> nums2 = {21, 21};
    cout << "Output for [21,21]: " << sol.sumFourDivisors(nums2) << endl;

    vector<int> nums3 = {1, 2, 3, 4, 5};
    cout << "Output for [1,2,3,4,5]: " << sol.sumFourDivisors(nums3) << endl;

    return 0;
}