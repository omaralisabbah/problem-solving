/*

Palindromic Partitioning


    Given a string s, a partitioning of the string is a palindrome partitioning if every sub-string of the partition is a palindrome.
    Determine the fewest cuts needed for palindrome partitioning of the given string.

    Examples:

    Input: s = "geek" 
    Output: 2 
    Explanation: We need to make minimum 2 cuts, i.e., "g | ee | k".

    Input: s = "aaaa" 
    Output: 0
    Explanation: The string is already a palindrome.

    Input: s = "ababbbabbababa" 
    Output: 3
    Explanation: We need to make minimum 3 cuts, i.e., "aba | bb | babbab | aba".

    Constraints:
    1 ≤ |s| ≤ 103
    s contain lowercase letters only



*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int palPartition(string &s) {
        int n = s.size();
        if (n == 0) return 0;

        // Step 1: Precompute palindrome table
        vector<vector<bool>> isPal(n, vector<bool>(n, false));
        
        for (int i = 0; i < n; i++) {
            isPal[i][i] = true; // single char is palindrome
        }
        
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    if (len == 2) isPal[i][j] = true;
                    else isPal[i][j] = isPal[i+1][j-1];
                }
            }
        }

        // Step 2: DP for minimum cuts
        vector<int> dp(n, INT_MAX);
        
        for (int i = 0; i < n; i++) {
            if (isPal[0][i]) {
                dp[i] = 0; // no cut needed if whole substring is palindrome
            } else {
                for (int j = 0; j < i; j++) {
                    if (isPal[j+1][i]) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }

        return dp[n-1];
    }
};

// -------------------------
// Driver Code for Testing
// -------------------------
int main() {
    Solution sol;

    string s1 = "geek";
    cout << "Minimum cuts for \"" << s1 << "\" = " << sol.palPartition(s1) << endl;
    // Expected: 2

    string s2 = "aaaa";
    cout << "Minimum cuts for \"" << s2 << "\" = " << sol.palPartition(s2) << endl;
    // Expected: 0

    string s3 = "ababbbabbababa";
    cout << "Minimum cuts for \"" << s3 << "\" = " << sol.palPartition(s3) << endl;
    // Expected: 3

    return 0;
}
