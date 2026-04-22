/*
    Given a sorted integer array arr[] and an integer k, determine if it is possible to split the array into one or more consecutive subsequences such that:

    Each subsequence consists of consecutive integers (each number is exactly one greater than the previous).
    Every subsequence has a length of at least k.

Return true if such a split is possible, otherwise return false.

Examples :

Input: arr[] = [2, 2, 3, 3, 4, 5], k = 2
Output: true
Explanation: arr can be split into three subsequence of length k - [2, 3], [2, 3], [4, 5].

Input: arr[] = [1, 1, 1, 1, 1], k = 4
Output: false
Explanation: It is impossible to split arr into consecutive increasing subsequences of length 4 or more.

Constraints:
1 ≤ arr.size()  ≤ 105
1 ≤ arr[i] ≤ 105
1 ≤  k ≤  arr.size() 


*/


#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool isPossible(vector<int>& arr, int k) {
        // Sort the array to ensure consecutive order
        sort(arr.begin(), arr.end());

        unordered_map<int, int> freq, end;

        // Count frequency of each number
        for (int num : arr) {
            freq[num]++;
        }

        for (int num : arr) {
            if (freq[num] == 0) continue;

            // Try to extend a previous subsequence ending at num - 1
            if (end[num - 1] > 0) {
                end[num - 1]--;
                end[num]++;
                freq[num]--;
            }
            // Try to start a new subsequence of length k
            else {
                bool canStart = true;
                for (int i = 0; i < k; ++i) {
                    if (freq[num + i] <= 0) {
                        canStart = false;
                        break;
                    }
                }
                if (!canStart) return false;

                for (int i = 0; i < k; ++i) {
                    freq[num + i]--;
                }
                end[num + k - 1]++;
            }
        }

        return true;
    }
};


int main() {
    vector<int> arr = {8, 9, 10, 11, 11, 12, 13, 2};
    int k = 2;

    Solution sol;
    bool result = sol.isPossible(arr, k);

    cout << (result ? "true" : "false") << endl;
    return 0;
}