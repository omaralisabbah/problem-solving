/*
    Given a floor of dimensions 2 x n and tiles of dimensions 2 x 1, the task is to find the number of ways
    the floor can be tiled. A tile can either be placed horizontally i.e as a 1 x 2 tile or vertically i.e as 2 x 1 tile. 

    Note: Two tiling arrangements are considered different if the placement of at least one tile differs.

    Examples :

    Input: n = 3
    Output: 3
    Explanation: We need 3 tiles to tile the board of size 2 x 3.
    We can tile in following ways:
    1) Place all 3 tiles vertically.
    2) Place first tile vertically and remaining 2 tiles horizontally.
    3) Place first 2 tiles horizontally and remaining tiles vertically.

    Input: n = 4
    Output: 5
    Explanation: We need 4 tiles to tile the board of size 2 x 4.
    We can tile in following ways:
    1) All 4 vertical
    2) All 4 horizontal
    3) First 2 vertical, remaining 2 horizontal.
    4) First 2 horizontal, remaining 2 vertical.
    5) Corner 2 vertical, middle 2 horizontal.

    Constraints:
    1 ≤ n ≤ 45



    Problem:
    --------
    Given a floor of dimensions 2 x n and tiles of dimensions 2 x 1,
    the task is to find the number of ways the floor can be tiled.

    You can place a tile either:
      - Vertically (occupies 2 x 1)
      - Horizontally (occupies 1 x 2, hence you need two tiles to cover 2 x 2)

    Two arrangements are considered different if the placement of at least one tile differs.

    Example:
    --------
    Input: n = 3
    Output: 3

    Explanation:
        Ways to tile a 2 x 3 board:
        1) All tiles vertical
        2) One vertical + two horizontal
        3) Two horizontal + one vertical

    Input: n = 4
    Output: 5

    Constraints:
    ------------
    1 ≤ n ≤ 45

    Approach:
    ---------
    Let f(n) = number of ways to tile a 2 x n board.

    Recurrence:
        - If we place one tile vertically, the remaining board is 2 x (n-1).
          → f(n-1) ways

        - If we place two tiles horizontally, the remaining board is 2 x (n-2).
          → f(n-2) ways

        Therefore:
            f(n) = f(n-1) + f(n-2)

    Base cases:
        f(1) = 1   // One vertical tile
        f(2) = 2   // Two vertical tiles OR two horizontal tiles

    The relation is identical to the Fibonacci sequence.
*/

#include <iostream>
using namespace std;

class Solution {
  public:
    // Function to compute the number of tiling ways for a 2 x n board
    int numberOfWays(int n) {
        // Base cases
        if (n == 1) return 1;
        if (n == 2) return 2;

        // Variables to store previous two results
        int a = 1; // f(1)
        int b = 2; // f(2)
        int c;     // To store current result f(n)

        // Iteratively compute values up to f(n)
        for (int i = 3; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }

        // 'b' now contains f(n)
        return b;
    }
};

// Driver code for testing
int main() {
    Solution sol;

    int n1 = 3;
    cout << "Input: n = " << n1 << "\nOutput: " << sol.numberOfWays(n1) << "\n\n";

    int n2 = 4;
    cout << "Input: n = " << n2 << "\nOutput: " << sol.numberOfWays(n2) << "\n\n";

    int n3 = 5;
    cout << "Input: n = " << n3 << "\nOutput: " << sol.numberOfWays(n3) << "\n";

    return 0;
}
