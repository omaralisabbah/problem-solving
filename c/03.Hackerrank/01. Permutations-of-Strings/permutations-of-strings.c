/*
 * HackerRank Challenge: Permutations of Strings
 *
 * Author: [omaralisabbah]
 *
 * Description:
 * Given an array of strings sorted in lexicographical order,
 * this program prints all unique permutations of the array
 * in strict lexicographical order.
 *
 * Key points:
 *   - Strings are compared lexicographically (dictionary order).
 *   - If two permutations are identical (due to duplicate strings),
 *     only one is printed.
 *   - Uses the "next permutation" algorithm to generate permutations
 *     in lexicographical order.
 *
 * Input format:
 *   - First line: integer n (number of strings).
 *   - Next n lines: each string s[i].
 *
 * Output format:
 *   - Each line: one permutation of the strings in lexicographical order.
 *
 * Constraints:
 *   - 2 <= n <= 9
 *   - 1 <= length of s[i] <= 10
 *   - Strings contain only lowercase English letters.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Function: compare
 * -----------------
 * Comparator function for qsort.
 * Compares two strings lexicographically.
 *
 * Parameters:
 *   a, b - pointers to strings
 *
 * Returns:
 *   Negative if *a < *b
 *   Zero if *a == *b
 *   Positive if *a > *b
 */
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

/*
 * Function: next_permutation
 * --------------------------
 * Generates the next lexicographical permutation of the array.
 *
 * Parameters:
 *   n - number of strings
 *   s - array of strings
 *
 * Returns:
 *   1 if the next permutation was generated successfully
 *   0 if there are no more permutations (array is in descending order)
 *
 * Algorithm:
 *   - Find the largest index i such that s[i] < s[i+1].
 *   - Find the largest index j > i such that s[i] < s[j].
 *   - Swap s[i] and s[j].
 *   - Reverse the sequence from s[i+1] to the end.
 */
int next_permutation(int n, char **s)
{
    int i = n - 2;
    // Step 1: find rightmost element smaller than its next
    while (i >= 0 && strcmp(s[i], s[i + 1]) >= 0) {
        i--;
    }
    
    if (i < 0) {
        return 0; // no next permutation
    }
    
    // Step 2: find rightmost element greater than s[i]
    int j = n - 1;
    while (strcmp(s[i], s[j]) >= 0) {
        j--;
    }
    
    // Step 3: swap s[i] and s[j]
    char *temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    
    // Step 4: reverse the suffix starting at i+1
    int left = i + 1, right = n - 1;
    while (left < right) {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
    
    return 1;
}

/*
 * Main function:
 * --------------
 * Reads input, generates permutations, and prints them.
 *
 * Steps:
 *   - Read n (number of strings).
 *   - Allocate memory for array of strings.
 *   - Read each string.
 *   - Print permutations using next_permutation until exhausted.
 *   - Free allocated memory.
 */
int main()
{
    char **s;
    int n;
    scanf("%d", &n);

    // Allocate memory for n strings
    s = calloc(n, sizeof(char*));
    for (int i = 0; i < n; i++)
    {
        s[i] = calloc(11, sizeof(char)); // max length 10 + null terminator
        scanf("%s", s[i]);
    }

    // Print permutations starting from initial sorted order
    do
    {
        for (int i = 0; i < n; i++)
            printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
    } while (next_permutation(n, s));

    // Free memory
    for (int i = 0; i < n; i++)
        free(s[i]);
    free(s);

    return 0;
}
