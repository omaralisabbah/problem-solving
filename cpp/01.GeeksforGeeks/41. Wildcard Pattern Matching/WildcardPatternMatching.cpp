/*
    Given two strings pat and txt which may be of different sizes, You have to return true if the wildcard pattern i.e. pat, matches with txt else return false.

The wildcard pattern pat can include the characters '?' and '*'.

    '?' – matches any single character.
    '*' – matches any sequence of characters (including the empty sequence).

Note: The matching should cover the entire txt (not partial txt).

Examples:

Input: txt = "abcde", pat = "a?c*"
Output: true
Explanation: '?' matches with 'b' and '*' matches with "de".

Input: txt = "baaabab", pat = "a*ab"
Output: false
Explanation: The pattern starts with a, but the text starts with b, so the pattern does not match the text.

Input: txt = "abc", pat = "*"
Output: true
Explanation: '*' matches with whole text "abc".

Constraints:
1 ≤ txt.size(), pat.size() ≤ 100


🧠 Key idea:

If pat[i-1] == txt[j-1] or pat[i-1] == '?',
→ dp[i][j] = dp[i-1][j-1]

If pat[i-1] == '*',
→ dp[i][j] = dp[i-1][j] || dp[i][j-1]

dp[i-1][j] means * represents an empty sequence.

dp[i][j-1] means * represents one or more characters.

Base cases handle empty string/pattern.


*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool wildCard(string &txt, string &pat) {
        int n = pat.size(), m = txt.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = true; // empty pattern matches empty text

        // Handle patterns with only '*' at the start
        for (int i = 1; i <= n; i++) {
            if (pat[i - 1] == '*')
                dp[i][0] = dp[i - 1][0];
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (pat[i - 1] == txt[j - 1] || pat[i - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (pat[i - 1] == '*') {
                    dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
                } else {
                    dp[i][j] = false;
                }
            }
        }

        return dp[n][m];
    }
};

int main() {
    Solution sol;
    
    // Test cases
    string txt1 = "abcde", pat1 = "a?c*";
    cout << (sol.wildCard(txt1, pat1) ? "true" : "false") << endl; 
    // Output: true

    string txt2 = "baaabab", pat2 = "a*ab";
    cout << (sol.wildCard(txt2, pat2) ? "true" : "false") << endl; 
    // Output: false

    string txt3 = "abc", pat3 = "*";
    cout << (sol.wildCard(txt3, pat3) ? "true" : "false") << endl; 
    // Output: true

    return 0;
}
