/*
    Given an integer k and an array of points points[][], where each point is represented as points[i] = [xi, yi] on the X-Y plane. Return the k closest points to the origin (0, 0).

The distance between two points on the X-Y plane is the Euclidean distance, defined as:
distance = sqrt( (x2 - x1)2 + (y2 - y1)2 )

Note: You can return the k closest points in any order, the driver code will print them in sorted order.
Test Cases are generated such that there will be a unique ans.

Examples:

Input: k = 2, points[] = [[1, 3], [-2, 2], [5, 8], [0, 1]]
Output: [[-2, 2], [0, 1]]
Explanation: The Euclidean distances from the origin are:
Point (1, 3) = sqrt(10)
Point (-2, 2) = sqrt(8)
Point (5, 8) = sqrt(89)
Point (0, 1) = sqrt(1)
The two closest points to the origin are [-2, 2] and [0, 1].

Input: k = 1, points = [[2, 4], [-1, -1], [0, 0]]
Output: [[0, 0]]
Explanation: The Euclidean distances from the origin are:
Point (2, 4) = sqrt(20)
Point (-1, -1) = sqrt(2)
Point (0, 0) = sqrt(0)
The closest point to origin is (0, 0).

Constraints:
1 ≤ k ≤ points.size() ≤ 105
-3*104 ≤ xi, yi ≤ 3*104
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

/*
    Problem:
    Given an integer k and an array of points points[][], where each point is represented as points[i] = [xi, yi] on the X-Y plane,
    return the k closest points to the origin (0, 0).

    The distance between two points on the X-Y plane is the Euclidean distance:
    distance = sqrt( (x2 - x1)² + (y2 - y1)² ).

    Approach:
    - We calculate the squared distance (no need for sqrt as it preserves the order of distances).
    - Use a max heap (priority_queue) to maintain the k closest points.
    - Ensure the heap never exceeds size k by popping the farthest point if necessary.
    
    Time Complexity:
    - Distance calculation: O(n)
    - Insertion and removal in max heap: O(log k) each
    - Total Complexity: O(n log k)
    
    Space Complexity:
    - O(k), for storing the k closest points in the heap.
*/

class Solution {
public:
    // Function to get the k closest points to the origin
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        // Max heap: stores {distance^2, index of point}
        priority_queue<pair<int, int>> maxHeap;

        // Loop through all points
        for (int i = 0; i < points.size(); ++i) {
            int x = points[i][0];
            int y = points[i][1];

            // Calculate squared distance from the origin (0, 0)
            int distSq = x * x + y * y;

            // Push the distance and index to the heap
            maxHeap.push({distSq, i});

            // If heap exceeds size k, remove the farthest point
            if (maxHeap.size() > k) {
                maxHeap.pop();
            }
        }

        // Prepare the result by extracting the closest k points from the heap
        vector<vector<int>> result;
        while (!maxHeap.empty()) {
            result.push_back(points[maxHeap.top().second]);
            maxHeap.pop();
        }

        return result;
    }
};

// Driver code for testing
int main() {
    Solution sol;
    
    // Test Case 1
    int k1 = 2;
    vector<vector<int>> points1 = {{1, 3}, {-2, 2}, {5, 8}, {0, 1}};
    vector<vector<int>> result1 = sol.kClosest(points1, k1);

    // Output the result
    cout << "Test Case 1 Result: \n";
    for (const auto& point : result1) {
        cout << "[" << point[0] << ", " << point[1] << "]\n";
    }

    // Test Case 2
    int k2 = 1;
    vector<vector<int>> points2 = {{2, 4}, {-1, -1}, {0, 0}};
    vector<vector<int>> result2 = sol.kClosest(points2, k2);

    // Output the result
    cout << "\nTest Case 2 Result: \n";
    for (const auto& point : result2) {
        cout << "[" << point[0] << ", " << point[1] << "]\n";
    }

    return 0;
}
