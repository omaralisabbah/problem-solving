/*
Given an array arr[], where the ith element of arr[] represents the price of a stock on the ith day (all prices are non-negative integers). Find the maximum profit you can make by buying and selling stocks such that after selling a stock, you cannot buy again on the next day (i.e., there is a one-day cooldown).

Examples:

Input: arr[] = [0, 2, 1, 2, 3]
Output: 3
Explanation: You first buy on day 1, sell on day 2 then cool down, then buy on day 4, and sell on day 5. The total profit earned is (2-0) + (3-2) = 3, which is the maximum achievable profit.

Input:  arr[] = [3, 1, 6, 1, 2, 4]
Output: 7
Explanation: You first buy on day 2 and sell on day 3 then cool down, then again you buy on day 5 and then sell on day 6. Clearly, the total profit earned is (6-1) + (4-2) = 7, which is the maximum achievable profit.

Constraint:
1 ≤ arr.size() ≤ 105
1 ≤ arr[i] ≤ 104


To solve this problem efficiently, we use Dynamic Programming with three states to model the cooldown constraint:
State Definitions:

    hold: Maximum profit when holding a stock.

    sold: Maximum profit after selling a stock (triggers cooldown).

    rest: Maximum profit when in cooldown or doing nothing.

Transition Logic:

    hold = max(hold, rest - price) → Buy or continue holding.

    sold = hold + price → Sell today.

    rest = max(rest, prev_sold) → Stay in cooldown or do nothing.

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& arr) {
        if (arr.empty()) return 0;

        int n = arr.size();
        int hold = -arr[0]; // Buying on day 0
        int sold = 0;
        int rest = 0;

        for (int i = 1; i < n; ++i) {
            int prev_sold = sold;
            sold = hold + arr[i]; // Sell today
            hold = max(hold, rest - arr[i]); // Buy today or keep holding
            rest = max(rest, prev_sold); // Cooldown or stay idle
        }

        return max(sold, rest); // Final profit can't be in hold state
    }
};

int main() {
    Solution sol;

    vector<int> arr1 = {0, 2, 1, 2, 3};
    vector<int> arr2 = {3, 1, 6, 1, 2, 4};

    cout << "Output 1: " << sol.maxProfit(arr1) << endl; // Expected: 3
    cout << "Output 2: " << sol.maxProfit(arr2) << endl; // Expected: 7

    return 0;
}
