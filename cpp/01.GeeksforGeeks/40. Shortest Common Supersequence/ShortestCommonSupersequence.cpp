/*
    Given two strings s1 and s2, find the length of the smallest string which has both s1 and s2 as its sub-sequences.
Note: s1 and s2 can have both uppercase and lowercase English letters.

Examples:

Input: s1 = "geek", s2 = "eke"
Output: 5
Explanation: String "geeke" has both string "geek" and "eke" as subsequences.

Input: s1 = "AGGTAB", s2 = "GXTXAYB"
Output: 9
Explanation: String "AGXGTXAYB" has both string "AGGTAB" and "GXTXAYB" as subsequences.

Input: s1 = "geek", s2 = "ek"
Output: 4
Explanation: String "geek" has both string "geek" and "ek" as subsequences.

Constraints:
1 ≤ s1.size(), s2.size() ≤ 500


This is a Shortest Common Supersequence (SCS) problem. The key idea is:
🔑 Insight

The length of the shortest common supersequence (SCS) can be derived from the Longest Common Subsequence (LCS):
SCS length=∣s1∣+∣s2∣−LCS(s1,s2)\text{SCS length} = |s1| + |s2| - \text{LCS}(s1, s2)

    The LCS represents the overlapping part of both strings.

    By subtracting the LCS length, we avoid double-counting the common subsequence.

🛠️ Steps

    Compute the LCS of s1 and s2 using dynamic programming.

    Use the formula above to get the SCS length.

*/

#include <bits/stdc++.h>
using namespace std;

/*
    Problem:
    --------
    Given two strings s1 and s2, find the length of the shortest string
    which has both s1 and s2 as subsequences.

    Key Idea:
    ---------
    - The shortest common supersequence (SCS) length can be derived from
      the longest common subsequence (LCS).
    - Formula:
          SCS_length = |s1| + |s2| - LCS(s1, s2)

    Why?
    ----
    - LCS represents the overlapping part of both strings.
    - By subtracting the LCS length, we avoid double-counting the common subsequence.
*/

class Solution {
  public:
    // Function to compute the length of the shortest common supersequence
    int minSuperSeq(string &s1, string &s2) {
        int n = s1.size();
        int m = s2.size();

        // Step 1: Build DP table for LCS
        // dp[i][j] = length of LCS of s1[0..i-1] and s2[0..j-1]
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i-1] == s2[j-1]) {
                    // Characters match → extend LCS
                    dp[i][j] = 1 + dp[i-1][j-1];
                } else {
                    // Characters differ → take max of excluding one char
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        // Step 2: Extract LCS length
        int lcs = dp[n][m];

        // Step 3: Apply formula
        return n + m - lcs;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    /*
        Input format:
        -------------
        Two strings separated by space or newline.

        Example:
        --------
        Input:
        geek eke

        Output:
        5
    */

    string s1, s2;
    cin >> s1 >> s2;

    Solution sol;
    cout << sol.minSuperSeq(s1, s2) << "\n";

    return 0;
}
