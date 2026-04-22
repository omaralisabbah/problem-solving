#include <iostream>
using namespace std;

int find_initial_value(int k, int x) {
    for (int i = 0; i < k; ++i) {
        if ((x - 1) % 3 == 0 && ((x - 1) / 3) % 2 == 1) {
            x = (x - 1) / 3;
        } else {
            x *= 2;
        }
    }
    return x;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int k, x;
        cin >> k >> x;
        cout << find_initial_value(k, x) << endl;
    }
    return 0;
}