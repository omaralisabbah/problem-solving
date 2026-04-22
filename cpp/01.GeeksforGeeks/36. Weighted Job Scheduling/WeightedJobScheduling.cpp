/*
    Given a 2D array jobs[][] of size n × 3, where each row represents a single job with the following details:

    jobs[i][0] : Start time of the job
    jobs[i][1] : End time of the job
    jobs[i][2] : Profit earned by completing the job

Find the maximum profit you can earn by scheduling non-overlapping jobs.

Note: Two jobs are said to be non-overlapping if the end time of one job is less than or equal to the start time of the next job. If a job ends at time X, another job can start exactly at time X.

Examples:

Input: jobs[][] =  [[1, 2, 50], 
                 [3, 5, 20],
                 [6, 19, 100],
                 [2, 100, 200]] 
Output: 250
Explanation: The first and fourth jobs with the time range [1, 2] and [2, 100] can be chosen to give maximum profit of 50 + 200 = 250.

Input: jobs[][] =  [[1, 3, 60], 
                 [2, 5, 50],
                 [4, 6, 70],
                 [5, 7, 30]] 
Output: 130
Explanation: The first and third jobs with the time range [1, 3] and [4, 6] can be chosen to give maximum profit of 60 + 70 = 130.

Constraints:
1 ≤ jobs.size() ≤ 105
1 ≤ jobs[i][0] < jobs[i][1] ≤ 109
1 ≤ jobs[i][2] ≤ 104
*/

/***************************************************************
 * Weighted Job Scheduling Problem
 * 
 * Given a list of jobs with start time, end time, and profit,
 * find the maximum profit by scheduling non-overlapping jobs.
 * 
 * Approach:
 *  - Sort jobs by their end times.
 *  - For each job, choose whether to:
 *      1. Include it → profit = job.profit + best profit from 
 *         the last non-conflicting job.
 *      2. Exclude it → profit = best profit so far.
 *  - Use binary search to efficiently find the last non-overlapping job.
 * 
 * Time Complexity:  O(n log n)
 * Space Complexity: O(n)
 * 
 * Example:
 * Input:
 *     jobs = [[1,2,50],[3,5,20],[6,19,100],[2,100,200]]
 * Output:
 *     250
 ***************************************************************/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<vector<int>> &jobs) {
        // Step 1: Sort jobs by end time
        sort(jobs.begin(), jobs.end(), [](const vector<int> &a, const vector<int> &b) {
            return a[1] < b[1];
        });

        int n = jobs.size();
        vector<int> dp(n);          // dp[i] = max profit up to job i
        vector<int> endTimes(n);    // Store end times for binary search

        for (int i = 0; i < n; i++)
            endTimes[i] = jobs[i][1];

        // Base case: profit of the first job
        dp[0] = jobs[0][2];

        // Step 2: Build DP array
        for (int i = 1; i < n; i++) {
            int inclProfit = jobs[i][2];  // Profit if including current job

            // Step 3: Find last job that doesn't conflict using binary search
            int idx = upper_bound(endTimes.begin(), endTimes.end(), jobs[i][0]) - endTimes.begin() - 1;
            if (idx >= 0)
                inclProfit += dp[idx];  // Add profit from the last non-overlapping job

            // Step 4: Choose the better of including or excluding this job
            dp[i] = max(dp[i - 1], inclProfit);
        }

        // Step 5: The last element has the answer
        return dp[n - 1];
    }
};

// -------------------- DRIVER CODE --------------------
int main() {
    Solution sol;

    vector<vector<int>> jobs1 = {{1, 2, 50}, {3, 5, 20}, {6, 19, 100}, {2, 100, 200}};
    cout << "Maximum Profit (Example 1): " << sol.maxProfit(jobs1) << endl;
    // Expected Output: 250

    vector<vector<int>> jobs2 = {{1, 3, 60}, {2, 5, 50}, {4, 6, 70}, {5, 7, 30}};
    cout << "Maximum Profit (Example 2): " << sol.maxProfit(jobs2) << endl;
    // Expected Output: 130

    return 0;
}
