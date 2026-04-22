/*

    Vlad and Dima have been assigned a task in school for their English class. They were given two strings a and b and asked to append all
    characters from b to string a in any order. The guys decided to divide the work between themselves and, after lengthy negotiations,
    determined who would add each character from string b to a.

    Due to his peculiarities, Vlad can only add characters to the beginning of the word, while Dima can only add them to the end. They add
    characters in the order they appear in string b. Your task is to determine what string Vlad and Dima will end up with.

    Input
    Each test consists of several test cases. The first line contains a single integer t(1≤t≤1000) — the number of test cases. The
    description of the test cases follows.

    The first line contains an integer n(1≤n≤10) — the length of the string a.

    The second line contains the string a, consisting of lowercase letters of the English alphabet.

    The third line contains an integer m(1≤m≤10) — the length of the strings b and c.

    The fourth line contains the string b, consisting of lowercase letters of the English alphabet.

    The fifth line contains the string c, consisting of the characters 'V' and 'D' — the distribution of the characters of string b between Dima
    and Vlad. If ci = 'V', then the i-th letter is added by Vlad; otherwise, it is added by Dima.

    Output
    For each test case, output the string that will result from Dima and Vlad's work.

    Example
    Input

        4
        2
        ot
        2
        ad
        DV
        3
        efo
        7
        rdcoecs
        DVDVDVD
        3
        aca
        4
        bbaa
        DVDV
        3
        biz
        4
        abon
        VVDD

    Output

        dota
        codeforces
        abacaba
        babizon


    Note
    In the first test case, there is initially a string ot. Then Dima appends the character a to the end of the string, resulting in ota, and Vlad
    appends the last character, resulting in dota.

    In the second test case, the string will change as follows:
    efo→efor→defor→deforc→odeforc→odeforce→codeforce→codeforces

    In the third test case: aca→acab→bacab→bacaba→abacaba

    In the fourth test case: biz→abiz→babiz→babizo→babizon

*/

#include <iostream>
#include <string>
#include <deque>
using namespace std;

int main() {
    int t; // number of test cases
    cin >> t;

    while (t--) {
        int n, m;
        string a, b, c;

        cin >> n >> a;
        cin >> m >> b;
        cin >> c;

        deque<char> result(a.begin(), a.end());

        for (int i = 0; i < m; ++i) {
            if (c[i] == 'V') {
                result.push_front(b[i]);
            } else {
                result.push_back(b[i]);
            }
        }

        for (char ch : result) {
            cout << ch;
        }
        cout << '\n';
    }

    return 0;
}