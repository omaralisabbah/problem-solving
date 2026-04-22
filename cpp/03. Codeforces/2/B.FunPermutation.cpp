#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>  // <-- Needed for std::iota
using namespace std;

// Function to check if a given q is valid
bool is_valid(const vector<int>& p, const vector<int>& q) {
    int n = static_cast<int>(p.size());
    for (int i = 0; i < n - 1; ++i) {
        if (__gcd(p[i] + q[i], p[i + 1] + q[i + 1]) < 3)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        vector<int> p(n), q(n);
        for (int i = 0; i < n; ++i)
            cin >> p[i];

        // Try q as a cyclic shift of p
        for (int i = 0; i < n; ++i)
            q[i] = p[(i + 1) % n];

        if (!is_valid(p, q)) {
            // Try q = [1, 2, ..., n]
            iota(q.begin(), q.end(), 1);
        }

        if (!is_valid(p, q)) {
            // Try q = [n, ..., 1]
            for (int i = 0; i < n; ++i)
                q[i] = n - i;
        }

        // Output result
        for (int i = 0; i < n; ++i)
            cout << q[i] << " ";
        cout << '\n';
    }

    return 0;
}