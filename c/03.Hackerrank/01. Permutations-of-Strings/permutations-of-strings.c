/*
    Strings are usually ordered in lexicographical order.
    That means they are ordered by comparing their leftmost different characters.
    For example, abc < abd because c < d . Also z > yyy because z > y. 
    If one string is an exact prefix of the other it is lexicographically smaller, e.g., gh < ghij.

    Given an array of strings sorted in lexicographical order, print all of its permutations in strict lexicographical order.
    If two permutations look the same, only print one of them. See the 'note' below for an example.

    Complete the function next_permutation which generates the permutations in the described order.

    For example, s = [ab, bc, cd]. The six permutations in correct order are:

    ab bc cd
    ab cd bc
    bc ab cd
    bc cd ab
    cd ab bc
    cd bc ab

    Note: There may be two or more of the same string as elements of s.
    For example, s = [ab, bc, cd]. Only one instance of a permutation where all elements match should be printed.
    In other words, if s[0] == s[1], then print either s[0] s[1] or s[1] s[0] but not both.

    A three element array having three distinct elements has six permutations as shown above.
    In this case, there are three matching pairs of permutations where s[0] = ab abd s[1] = ab are switched.
    We only print the three visibly unique permutations:

    ab ab bc
    ab bc ab
    bc ab ab

    Input Format

    The first line of each test file contains a single integer n, the length of the string array s.
    Each of the next n lines contains a string s[i].

    Constraints
    2 <= n <= 9
    1 <= s[i] <= 10
    s[i] contains only lowercases English letters.

    Sample Input
    2
    ab
    cd

    Sample Output
    ab cd
    cd ab
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int next_permutation(int n, char **s)
{
	/**
	* Complete this method
	* Return 0 when there is no next permutation and 1 otherwise
	* Modify array s to its next permutation
	*/
    int i = n - 2;
    while (i >= 0 && strcmp(s[i], s[i + 1]) >= 0) {
        i--;
    }
    
    if (i < 0) {
        return 0;
    }
    
    int j = n - 1;
    while (strcmp(s[i], s[j]) >= 0) {
        j--;
    }
    
    char *temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    
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

int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}