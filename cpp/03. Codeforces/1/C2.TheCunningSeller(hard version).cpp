/*
    This is the hard version of the problem. The easy version differs from the hard one in that it requires determining the minimum cost with the
    least number of deals, while the hard version requires determining the minimum cost with a limited number of deals.

    After the cunning seller sold three watermelons instead of one, he decided to increase his profit — namely, he bought even more
    watermelons. Now he can sell 3x watermelons for 3x+1+x⋅3x−1 coins, where x is a non-negative integer. Such a sale is called a deal.

A calculating buyer came to him, but he has little time, so the buyer can make no more than k
deals and plans to buy exactly n

watermelons.

The buyer is in a hurry and has therefore turned to you to determine the minimum number of coins he must pay the seller for n
watermelons if he makes no more than k deals. If it is impossible to buy exactly n watermelons while making no more than k deals, output −1

.
Input

The first line contains an integer t
(1≤t≤104)

— the number of test cases. The description of each test case follows.

In a single line of each test case, there are two integers n
and k (1≤n,k≤109)

— how many watermelons need to be bought and how many deals can be made.
Output

For each test case, output a single integer — the minimum cost of the watermelons or −1

if it is impossible to buy the watermelons while meeting all the conditions.
Example
Input
Copy

8
1 1
3 3
8 3
2 4
10 10
20 14
3 2
9 1

Output
Copy

3
9
-1
6
30
63
10
33

Note

Note that there is no point in buying more watermelons than needed, so we will not consider deals where there are more watermelons than necessary.

Let's consider the costs of the first two deal options:

Deal A: 1
watermelon — 3

coins.

Deal B: 3
watermelons — 10

coins.

In the first sample, the only way to buy 1
watermelon is to use Deal A, so the answer is 3

.

In the second sample, you can buy 3
watermelons either with Deal B for 10 coins or with three Deal A for 9 coins, so the answer is 9

.

In the third sample, there are the following options for 3 deals:

3
Deals A — 3

watermelons.

2
Deals A and 1 Deal B — 5

watermelons.

1
Deal A and 2 Deals B — 7

watermelons.

3
Deals B — 9

watermelons.

It can be seen that it is impossible to buy exactly 8 watermelons.
*/
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX_X = 40;
ll powers[MAX_X];
ll costs[MAX_X];

void precompute() {
    powers[0] = 1;
    for (int i = 1; i < MAX_X; i++) powers[i] = powers[i - 1] * 3;

    costs[0] = 3;
    for (int i = 1; i < MAX_X; i++) {
        costs[i] = powers[i + 1] + i * powers[i - 1] - powers[i - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    precompute();

    int t; cin >> t;
    while (t--) {
        ll n, k; cin >> n >> k;

        vector<int> digits;
        ll temp = n;
        while (temp > 0) {
            digits.push_back(temp % 3);
            temp /= 3;
        }
        if (digits.empty()) digits.push_back(0);

        ll sum_deals = 0;
        for (int d : digits) sum_deals += d;

        if (sum_deals <= k) {
            ll ans = 0;
            for (int i = 0; i < (int)digits.size(); i++) {
                ans += digits[i] * costs[i];
            }
            cout << ans << "\n";
            continue;
        }

        // Carry to reduce deals
        for (int i = 0; i + 1 < (int)digits.size(); i++) {
            while (digits[i] >= 3) {
                digits[i] -= 3;
                digits[i + 1] += 1;
            }
        }
        // Handle last carry if needed
        while (digits.back() >= 3) {
            int val = digits.back();
            digits.back() = val % 3;
            digits.push_back(val / 3);
        }

        // Recalculate sum_deals
        sum_deals = 0;
        for (int d : digits) sum_deals += d;

        if (sum_deals > k) {
            cout << -1 << "\n";
            continue;
        }

        ll ans = 0;
        for (int i = 0; i < (int)digits.size(); i++) {
            ans += digits[i] * costs[i];
        }

        cout << ans << "\n";
    }

    return 0;
}