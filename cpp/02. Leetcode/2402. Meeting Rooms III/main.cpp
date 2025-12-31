#include <bits/stdc++.h>
using namespace std;

/**
 * Solution to "Most Booked Meeting Room"
 *
 * Approach:
 * - Sort meetings by start time.
 * - Use two priority queues:
 *   1. freeRooms: min-heap of available room indices.
 *   2. ongoing: min-heap of {end_time, room} for currently occupied rooms.
 * - For each meeting:
 *   - Free up rooms whose meetings ended before current start.
 *   - If a free room exists, assign meeting to lowest-numbered free room.
 *   - If no free room, delay meeting until earliest room becomes free.
 * - Track number of meetings per room.
 * - Return room with maximum meetings (lowest index if tie).
 *
 * Complexity:
 * - Sorting: O(m log m), where m = meetings.size().
 * - Each meeting involves heap operations: O(log n).
 * - Total: O(m log m + m log n).
 */

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        // Step 1: Sort meetings by start time
        sort(meetings.begin(), meetings.end());

        // Min-heap of free rooms (lowest index first)
        priority_queue<int, vector<int>, greater<int>> freeRooms;
        for (int i = 0; i < n; i++) freeRooms.push(i);

        // Min-heap of ongoing meetings: {end_time, room}
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> ongoing;

        // Count of meetings per room
        vector<int> count(n, 0);

        // Step 2: Process each meeting
        for (auto &meet : meetings) {
            long long start = meet[0], end = meet[1];
            long long duration = end - start;

            // Free up rooms that have finished before current start
            while (!ongoing.empty() && ongoing.top().first <= start) {
                freeRooms.push(ongoing.top().second);
                ongoing.pop();
            }

            if (!freeRooms.empty()) {
                // Assign to lowest-numbered free room
                int room = freeRooms.top();
                freeRooms.pop();
                count[room]++;
                ongoing.push({end, room});
            } else {
                // Delay meeting until earliest room is free
                auto [freeTime, room] = ongoing.top();
                ongoing.pop();
                count[room]++;
                ongoing.push({freeTime + duration, room});
            }
        }

        // Step 3: Find room with maximum meetings
        int ans = 0;
        for (int i = 1; i < n; i++) {
            if (count[i] > count[ans] || (count[i] == count[ans] && i < ans)) {
                ans = i;
            }
        }
        return ans;
    }
};

// -------------------------
// Example Usage
// -------------------------
int main() {
    Solution sol;

    vector<vector<int>> meetings1 = {{0,10},{1,5},{2,7},{3,4}};
    cout << "Example 1: " << sol.mostBooked(2, meetings1) << endl; // Output: 0

    vector<vector<int>> meetings2 = {{1,20},{2,10},{3,5},{4,9},{6,8}};
    cout << "Example 2: " << sol.mostBooked(3, meetings2) << endl; // Output: 1

    return 0;
}
