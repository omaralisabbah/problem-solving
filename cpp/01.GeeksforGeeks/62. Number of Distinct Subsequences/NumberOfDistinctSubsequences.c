/*

Given a string str consisting of lowercase english alphabets, the task is to find the number of distinct subsequences of the string
Note: Answer can be very large, so, ouput will be answer modulo 109+7.

Examples:

Input: str = "gfg"
Output: 7
Explanation: 
The seven distinct subsequences are "", "g", "f", "gf", "fg", "gg" and "gfg" .

Input: str = "ggg"
Output: 4
Explanation: 
The four distinct subsequences are "", "g", "gg", "ggg".

Constraints:
1 ≤ |str| ≤ 105
str contains lower case English alphabets


Got it 👍 — this is a classic dynamic programming problem. We want to count the number of distinct subsequences of a string, modulo 109+710^9+7.
🔑 Key Idea

    Every character can either be included or excluded → subsequences double at each step.

    But if a character has appeared before, we must avoid double-counting subsequences that were already formed with its previous occurrence.

    To handle this, we track the last occurrence of each character.

📝 Algorithm

    Let dp[i] = number of distinct subsequences using the first i characters.

    Transition:

dp[i]=2⋅dp[i−1]−dp[lastOccur]dp[i] = 2 \cdot dp[i-1] - dp[lastOccur]

    2 * dp[i-1]: include or exclude current character.

    Subtract subsequences counted before the last occurrence of this character.

    Use a map/array last to store the last index of each character.

    Base case: dp[0] = 1 (the empty subsequence).

    Answer = dp[n].

*/
/*
  Problem:
  --------
  Given a string consisting of lowercase English alphabets, 
  find the number of distinct subsequences of the string.

  Note:
  - The answer can be very large, so output should be modulo 1e9+7.
  - A subsequence is formed by deleting zero or more characters 
    without changing the order of the remaining characters.

  Approach:
  ---------
  1. Use Dynamic Programming (DP).
     Let dp[i] = number of distinct subsequences using first i characters.
     
  2. Transition:
     - At each step, we can either include or exclude the current character.
       So normally: dp[i] = 2 * dp[i-1].
     - But if the current character has appeared before, 
       we must subtract subsequences that were already counted 
       before its last occurrence to avoid duplicates.
       Formula:
         dp[i] = 2 * dp[i-1] - dp[lastOccur[ch] - 1]

  3. Base case:
     dp[0] = 1 (the empty subsequence).

  4. Use an array `last` to store the last index of each character.

  5. Answer = dp[n].

  Complexity:
  -----------
  - Time: O(n), where n = length of string.
  - Space: O(n) for dp array, can be optimized to O(1) if needed.

  Example:
  --------
  Input: "gfg"
  Distinct subsequences: "", "g", "f", "gf", "fg", "gg", "gfg"
  Output: 7
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int distinctSubseq(string &str) {
        const int MOD = 1e9 + 7;
        int n = str.size();
        
        // dp[i] = number of distinct subsequences using first i characters
        vector<long long> dp(n + 1, 0);
        dp[0] = 1;  // empty subsequence
        
        // last occurrence of each character (26 lowercase letters)
        vector<int> last(26, -1);
        
        for (int i = 1; i <= n; i++) {
            // double the subsequences by including/excluding current char
            dp[i] = (2 * dp[i - 1]) % MOD;
            
            int ch = str[i - 1] - 'a';
            
            // if character appeared before, subtract duplicates
            if (last[ch] != -1) {
                dp[i] = (dp[i] - dp[last[ch] - 1] + MOD) % MOD;
            }
            
            // update last occurrence
            last[ch] = i;
        }
        
        return dp[n];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    string str;
    cout << "Enter string: ";
    cin >> str;
    
    Solution sol;
    cout << "Number of distinct subsequences = " 
         << sol.distinctSubseq(str) << "\n";
    
    return 0;
}
