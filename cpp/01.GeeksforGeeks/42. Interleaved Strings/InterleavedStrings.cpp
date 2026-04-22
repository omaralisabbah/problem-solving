/*
    Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
Interleaving of two strings s1 and s2 is a way to mix their characters to form a new string s3, while maintaining the relative order of characters from s1 and s2. Conditions for interleaving:

    Characters from s1 must appear in the same order in s3 as they are in s1.
    Characters from s2 must appear in the same order in s3 as they are in s2.
    The length of s3 must be equal to the combined length of s1 and s2.

Examples :

Input: s1 = "AAB", s2 = "AAC", s3 = "AAAABC", 
Output: true
Explanation: The string "AAAABC" has all characters of the other two strings and in the same order.

Input: s1 = "AB", s2 = "C", s3 = "ACB", 
Output: true
Explanation: s3 has all characters of s1 and s2 and retains order of characters of s1.

Input: s1 = "YX", s2 = "X", s3 = "XXY"
Output: false
Explanation: "XXY " is not interleaved of "YX" and "X". The strings that can be formed are YXX and XYX

Constraints:
1 ≤ s1.length, s2.length ≤ 300
1 ≤ s3.length ≤ 600


*/

/*
    Problem: Interleaving Strings
    ---------------------------------
    Given three strings s1, s2, and s3, determine whether s3 is formed 
    by an interleaving of s1 and s2.

    Definition of Interleaving:
        - Characters from s1 and s2 must appear in the same relative order
          as in their original strings.
        - The combined length of s1 and s2 must equal the length of s3.

    Example:
        Input:
            s1 = "AAB"
            s2 = "AAC"
            s3 = "AAAABC"
        Output:
            true
        Explanation:
            "AAAABC" is a valid interleaving of "AAB" and "AAC".

    Constraints:
        1 ≤ s1.length, s2.length ≤ 300
        1 ≤ s3.length ≤ 600

    Approach:
    ----------
    Dynamic Programming (DP):
        - dp[i][j] = true if the first i characters of s1 and
                     the first j characters of s2 can form the first (i + j)
                     characters of s3 by interleaving.
        - Base case: dp[0][0] = true (empty strings form empty s3)
        - Transition:
            dp[i][j] = (dp[i-1][j] && s1[i-1] == s3[i+j-1]) ||
                       (dp[i][j-1] && s2[j-1] == s3[i+j-1])
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isInterleave(string &s1, string &s2, string &s3) {
        int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();

        // Quick length check
        if (n1 + n2 != n3)
            return false;

        // dp[i][j] = true if s3[0...(i+j-1)] can be formed 
        // by interleaving s1[0...(i-1)] and s2[0...(j-1)]
        vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1, false));

        dp[0][0] = true; // Empty strings interleave to form empty string

        // Fill first row (only using s2)
        for (int j = 1; j <= n2; j++) {
            dp[0][j] = dp[0][j - 1] && (s2[j - 1] == s3[j - 1]);
        }

        // Fill first column (only using s1)
        for (int i = 1; i <= n1; i++) {
            dp[i][0] = dp[i - 1][0] && (s1[i - 1] == s3[i - 1]);
        }

        // Fill rest of DP table
        for (int i = 1; i <= n1; i++) {
            for (int j = 1; j <= n2; j++) {
                bool fromS1 = dp[i - 1][j] && (s1[i - 1] == s3[i + j - 1]);
                bool fromS2 = dp[i][j - 1] && (s2[j - 1] == s3[i + j - 1]);
                dp[i][j] = fromS1 || fromS2;
            }
        }

        // Final result
        return dp[n1][n2];
    }
};

// -------------------- Driver Code --------------------
int main() {
    Solution solution;

    string s1, s2, s3;
    cout << "Enter string s1: ";
    cin >> s1;
    cout << "Enter string s2: ";
    cin >> s2;
    cout << "Enter string s3: ";
    cin >> s3;

    bool result = solution.isInterleave(s1, s2, s3);

    cout << "\nIs \"" << s3 << "\" an interleaving of \"" << s1
         << "\" and \"" << s2 << "\"? -> "
         << (result ? "true" : "false") << endl;

    return 0;
}
