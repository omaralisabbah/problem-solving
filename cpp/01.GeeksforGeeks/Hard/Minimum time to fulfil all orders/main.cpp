#include <bits/stdc++.h>
using namespace std;

/**
 * Problem:
 * Geek needs exactly n donuts. There are m chefs, each with a rank r.
 * A chef with rank r takes:
 *   r minutes for the 1st donut,
 *   2r minutes for the 2nd donut,
 *   3r minutes for the 3rd donut,
 *   ...
 *   k*r minutes for the k-th donut.
 *
 * Total time for k donuts = r * (1 + 2 + ... + k) = r * k * (k+1) / 2.
 *
 * All chefs work simultaneously. We want the minimum time required
 * to produce at least n donuts.
 *
 * Approach:
 * 1. Use binary search on time (0 .. maxTime).
 * 2. For each candidate time mid, check if the chefs can produce >= n donuts.
 * 3. Narrow down until we find the minimum feasible time.
 */

class Solution {
public:
    /**
     * Helper function to check if we can make at least n donuts
     * within a given time limit `mid`.
     */
    bool canMake(vector<int>& ranks, int n, long long mid) {
        long long donuts = 0;
        for (int r : ranks) {
            // Solve inequality: r * k * (k+1) / 2 <= mid
            // Rearranged: k^2 + k <= 2*mid / r
            long long val = (2LL * mid) / r;

            // Quadratic formula: k = (-1 + sqrt(1 + 4*val)) / 2
            long long k = (sqrt(1 + 4.0 * val) - 1) / 2;

            donuts += k;
            if (donuts >= n) return true; // early exit if enough donuts
        }
        return donuts >= n;
    }

    /**
     * Main function to compute minimum time.
     * @param ranks: vector of chef ranks
     * @param n: number of donuts required
     * @return minimum time to make n donuts
     */
    int minTime(vector<int>& ranks, int n) {
        int minRank = *min_element(ranks.begin(), ranks.end());

        // Upper bound: if the fastest chef makes all n donuts
        long long high = 1LL * minRank * n * (n + 1) / 2;
        long long low = 0, ans = high;

        while (low <= high) {
            long long mid = (low + high) / 2;

            if (canMake(ranks, n, mid)) {
                ans = mid;       // feasible → try smaller time
                high = mid - 1;
            } else {
                low = mid + 1;   // not feasible → need more time
            }
        }
        return (int)ans;
    }
};

// ------------------ DRIVER CODE ------------------
int main() {
    Solution sol;

    // Example 1
    vector<int> ranks1 = {1, 2, 3, 4};
    int n1 = 10;
    cout << "Minimum time for n=10, ranks=[1,2,3,4]: "
         << sol.minTime(ranks1, n1) << endl; // Expected: 12

    // Example 2
    vector<int> ranks2 = {1, 1, 1, 1, 1, 1, 1, 1};
    int n2 = 8;
    cout << "Minimum time for n=8, ranks=[1,1,1,1,1,1,1,1]: "
         << sol.minTime(ranks2, n2) << endl; // Expected: 1

    return 0;
}
