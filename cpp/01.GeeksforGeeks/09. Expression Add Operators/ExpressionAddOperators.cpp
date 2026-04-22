/*
    Given a string s that contains only digits (0-9) and an integer target, return all possible strings by inserting the binary operator ' + ', ' - ', and/or ' * ' between the digits of s such that the resultant expression evaluates to the target value.

Note:

    Operands in the returned expressions should not contain leading zeros. For example, 2 + 03 is not allowed whereas 20 + 3 is fine.
    It is allowed to not insert any of the operators.
    Driver code will print the final list of strings in lexicographically smallest order.

Examples:

Input: s = "124", target = 9
Output: ["1+2*4"]
Explanation: The valid expression that evaluate to 9 is 1 + 2 * 4

Input: s = "125", target = 7
Output: ["1*2+5", "12-5"]
Explanation: The two valid expressions that evaluate to 7 are 1 * 2 + 5 and 12 - 5.

Input: s = "12", target = 12
Output: ["12"] 
Explanation: s itself matches the target. No other expressions are possible.

Input: s = "987612", target = 200
Output: []
Explanation: There are no expressions that can be created from "987612" to evaluate to 200.

Constraints:
1 ≤ s.size() ≤ 9
s consists of only digits (0-9).
-231 ≤ target ≤ 231-1


To solve this problem, we need to generate all possible expressions from the string of digits by inserting the binary operators '+', '-', and '*' between the digits. We will evaluate each expression to see if it equals the given target. The key challenge is to ensure that no operand has leading zeros (i.e., "03" is not allowed).

Plan:

Backtracking:
We will use backtracking to explore all possible expressions by trying every possible position for the operators. We will construct each expression step-by-step and evaluate its value as we go along.

Expression Evaluation:
Since the expression can have multiple operators, we need to evaluate the expression correctly according to operator precedence:

The * operator has a higher precedence than + and -.

We can evaluate the expression as we construct it, which makes handling operator precedence easier.

Handling Leading Zeros:
We must ensure that no number in the expression has leading zeros, unless the number is exactly 0. For example, 03 or 001 are invalid.

Lexicographical Order:
The driver code will print the result in lexicographically sorted order, so we should return the expressions in the required order.

Approach:

Use backtracking to generate all possible expressions by trying all possible places to insert the operators.

For each expression, check if it evaluates to the target.

Ensure that there are no leading zeros in any operand.

Steps:

Define a recursive function that explores the string and tries different ways to insert the operators.

Evaluate the expression at each step and check if it matches the target.
*/


#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> findExpr(string &s, int target) {
        vector<string> result;
        if (s.empty()) return result;
        
        // Helper function to backtrack and generate expressions
        backtrack(s, target, 0, "", 0, 0, result);
        return result;
    }
    
private:
    // Helper function for backtracking
    void backtrack(string &s, int target, int idx, string current, long prev_operand, long current_operand, vector<string>& result) {
        // If we have reached the end of the string, evaluate the expression
        if (idx == s.length()) {
            if (current_operand + prev_operand == target) {
                result.push_back(current);
            }
            return;
        }
        
        // Convert the current digit into an operand
        string num = "";
        for (int i = idx; i < s.length(); i++) {
            num += s[i];
            
            // If the number has leading zeros, skip it
            if (num.length() > 1 && num[0] == '0') {
                break;
            }

            long n = stol(num); // Convert the current number into an integer
            
            // If we are at the first character, we can start the expression with this number
            if (idx == 0) {
                backtrack(s, target, i + 1, current + num, 0, n, result);
            } else {
                // Add the '+' operator
                backtrack(s, target, i + 1, current + "+" + num, prev_operand + current_operand, n, result);
                // Add the '-' operator
                backtrack(s, target, i + 1, current + "-" + num, prev_operand + current_operand, -n, result);
                // Add the '*' operator
                backtrack(s, target, i + 1, current + "*" + num, prev_operand, current_operand * n, result);
            }
        }
    }
};

int main() {
    Solution sol;
    string s = "124";
    int target = 9;
    
    vector<string> result = sol.findExpr(s, target);
    
    cout << "Possible expressions that evaluate to " << target << ":\n";
    for (const string& expr : result) {
        cout << expr << "\n";
    }
    
    return 0;
}
