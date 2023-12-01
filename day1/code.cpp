#include <bits/stdc++.h>
using namespace std;

void task1() {
    string s;
    int sum = 0;
    while (getline(cin, s)) {
        int x = 0, y = 0;
        for (auto ch : s)
            if (isdigit(ch)) {
                x = ch - '0';
                break;
            }
        reverse(s.begin(), s.end());
        for (auto ch : s)
            if (isdigit(ch)) {
                y = ch - '0';
                break;
            }
        sum += x * 10 + y;
    }
    cout << sum << endl;
}

void task2() {
    map<string, int> m;
    m["1"] = m["one"] = 1;
    m["2"] = m["two"] = 2;
    m["3"] = m["three"] = 3;
    m["4"] = m["four"] = 4;
    m["5"] = m["five"] = 5;
    m["6"] = m["six"] = 6;
    m["7"] = m["seven"] = 7;
    m["8"] = m["eight"] = 8;
    m["9"] = m["nine"] = 9;
    string s;
    int sum = 0;
    while (getline(cin, s)) {
        int x = 0, y = 0;
        for (int i = 0; i < s.length(); ++i) {
            bool f = false;
            for (auto [ss, v] : m)
                if (ss.size() + i - 1 < s.length()) {
                    if (ss == s.substr(i, ss.size())) {
                        x = v, f = true;
                        break;
                    }
                }
            if (f)
                break;
        }
        for (int i = s.length() - 1; i >= 0; --i) {
            bool f = false;
            for (auto [ss, v] : m)
                if (ss.size() + i - 1 < s.length())
                    if (ss == s.substr(i, ss.size())) {
                        y = v, f = true;
                        break;
                    }
            if (f)
                break;
        }
        sum += x * 10 + y;
    }
    cout << sum << endl;
}

int main () {
    freopen("input.txt", "r", stdin);
    // task1();
    task2();
    return 0;
}