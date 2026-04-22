#include <iostream>
#include <cmath>
using namespace std;

using ll = long long;

ll compute_max_even_sum(ll a, ll b) {
    ll max_sum = -1;
    for (ll d = 1; d * d <= b; ++d) {
        if (b % d == 0) {
            // Try k = d
            ll k1 = d;
            ll a1 = a * k1;
            ll b1 = b / k1;
            ll sum1 = a1 + b1;
            if (sum1 % 2 == 0)
                max_sum = max(max_sum, sum1);

            // Try k = b / d (only if different)
            if (k1 != b / d) {
                ll k2 = b / d;
                ll a2 = a * k2;
                ll b2 = b / k2;
                ll sum2 = a2 + b2;
                if (sum2 % 2 == 0)
                    max_sum = max(max_sum, sum2);
            }
        }
    }
    return max_sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        cout << compute_max_even_sum(a, b) << '\n';
    }
    return 0;
}