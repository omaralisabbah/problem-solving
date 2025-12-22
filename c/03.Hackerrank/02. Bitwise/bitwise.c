/*
 * HackerRank Challenge: Bitwise Operators (Calculate the Maximum)
 *
 * Author: [omaralisabbah]
 *
 * Description:
 * This program computes the maximum values of bitwise AND, OR, and XOR
 * for all pairs (i, j) where 1 <= i < j <= n, subject to the constraint
 * that the result must be strictly less than k.
 *
 * Input format:
 *   - Two integers n and k
 * Output format:
 *   - Three integers (each on a new line):
 *       max AND value < k
 *       max OR value < k
 *       max XOR value < k
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*
 * Function: calculate_the_maximum
 * -------------------------------
 * Computes the maximum bitwise AND, OR, and XOR values for pairs (i, j)
 * in the range [1, n], with the condition that the result must be < k.
 *
 * Parameters:
 *   n - upper bound of the range (1 to n)
 *   k - constraint value (results must be less than k)
 *
 * Output:
 *   Prints three integers:
 *     - Maximum AND < k
 *     - Maximum OR < k
 *     - Maximum XOR < k
 */
void calculate_the_maximum(int n, int k) {
    // Initialize maximum values
    int max_and = 0, max_or = 0, max_xor = 0;

    // Iterate over all pairs (i, j) with i < j
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            // Compute bitwise operations
            int temp_and = i & j;
            int temp_or  = i | j;
            int temp_xor = i ^ j;

            // Update maximum AND if valid and greater
            if (temp_and > max_and && temp_and < k) {
                max_and = temp_and;
            }
            // Update maximum OR if valid and greater
            if (temp_or > max_or && temp_or < k) {
                max_or = temp_or;
            }
            // Update maximum XOR if valid and greater
            if (temp_xor > max_xor && temp_xor < k) {
                max_xor = temp_xor;
            }
        }
    }

    // Print results
    printf("%d\n%d\n%d", max_and, max_or, max_xor);
}

/*
 * Main function:
 * --------------
 * Reads input values n and k, then calls calculate_the_maximum.
 */
int main() {
    int n, k;
  
    // Read input values
    scanf("%d %d", &n, &k);

    // Compute and print results
    calculate_the_maximum(n, k);
 
    return 0;
}