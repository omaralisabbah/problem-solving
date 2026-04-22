/**

    You are given a string s, and a list of jumps[][] of size n, where each jumps[i] = [s1, s2] denotes that you are allowed to jump from character s1 to s2 in the forward direction.
Additionally, you are allowed to jump forward from a character to any other occurrence of the same character within the string.

You start at index 0 of the string. After every valid jump from index i to index j, where s[i] = s1 and s[j] = s2, you earn a score equal to the sum of ASCII values of all characters between the jump except for the characters equals s2, i.e.

    score(i, j) = sum(ascii(s[k]) for i ≤ k < j and s[k] != s[j]).

Determine the maximum score that can be achieved by performing a sequence of valid jumps starting from index 0.

Examples:

Input: s = "forgfg", jumps[][] = [['f', 'r'], ['r', 'g']]
Output: 429
Explanation: We can jump from 'f' to 'r' at index 2, this will gives a score equals to sum of ASCII value of 'f', 'o' i.e. 213.
Now we can jump from 'r' to 'g' at index 5, this will gives a score equals to sum of ASCII value of 'r', 'f' i.e. 216.
Hence maximum total score obtain will be 429. 

Input: s = "abcda", jumps[][] = [[b, d]]
Output: 297
Explanation: We can jump from 'a' to 'a'(as both are same character) at index 4, this will gives a score equals to sum of ASCII value of 'b', 'c', 'd' i.e. 297.
Hence maximum total score obtain will be 297. 

Constraints:
1 ≤ |s| ≤ 2 * 105
1 ≤ jumps.size() ≤ 676
There are atleast two distinct characters in s.


Got it — this is a dynamic programming + graph traversal problem. Let’s carefully break it down and then I’ll give you a clean C++ solution.
🔎 Key Observations

    Graph Representation

        Each index in the string is a node.

        You can jump from index i to index j if:

            s[i] == s1 and s[j] == s2 for some allowed jump [s1, s2].

            OR s[i] == s[j] (same character jump).

    Score Calculation

        For a jump (i → j), score = sum of ASCII values of characters in substring s[i..j-1] excluding characters equal to s[j].

    Dynamic Programming

        Let dp[j] = maximum score achievable when landing at index j.

        Transition:

dp[j]=max⁡(dp[i]+score(i,j))for all valid jumps i→jdp[j] = \max(dp[i] + score(i, j)) \quad \text{for all valid jumps } i \to j

    Efficiency

        String length can be up to 2 * 10^5, so we need O(n log n) or O(n) transitions.

        Precompute prefix sums of ASCII values for fast substring scoring.

        Also precompute prefix counts of each character to exclude s[j].

⚡ Implementation Plan

    Build a prefix sum array of ASCII values.

    Build a prefix frequency array for each character (to exclude s[j]).

    Store allowed jumps in a unordered_map<char, unordered_set<char>>.

    Traverse string, for each index i, try all valid jumps forward.

    Update dp[j] accordingly.

    Answer = max over all dp.   



*/
class Solution {
public:
    int maxScore(string &s, vector<vector<char>> &jumps) {

        int n = s.size();

        // allowed[c] contains all characters x such that c -> x jump allowed
        vector<vector<int>> allowed(256, vector<int>(256, 0));
        for (auto &v : jumps) {
            allowed[(unsigned char)v[0]][(unsigned char)v[1]] = 1;
        }

        // Same char jump is ALWAYS allowed
        for (int c = 0; c < 256; c++) {
            allowed[c][c] = 1;
        }

        // prefix sum of ASCII values
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + s[i];
        }

        // last occurrence of each char to the right
        vector<int> last(256, -1);

        // dp[i] = max score starting from i
        vector<int> dp(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {

            int best = 0;
            int c = (unsigned char)s[i];

            // try jumping to each possible target char x
            for (int x = 0; x < 256; x++) {
                if (!allowed[c][x]) continue;

                int j = last[x];
                if (j == -1) continue;

                // gain = sum(i+1 .. j), but adjust if same character
                int gain = pref[j] - pref[i];

                if (s[i] == s[j]) {
                    gain -= s[j];   // do not include target if same character
                }

                best = max(best, gain + dp[j]);
            }

            dp[i] = best;

            // update last occurrence of current char
            last[c] = i;
        }

        return dp[0];
    }
};
