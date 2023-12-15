#include <bits/stdc++.h>
using namespace std;

void task1(vector<vector<string>> a) {
    int cntx = 0, cnty = 0;
    for (auto b : a) {
        int n = b.size(), m = b[0].size();
        bool found = false;
        for (int i = 0; i < n - 1 && !found; ++i) {
            bool f = true;
            for (int l = 1; l <= min(i + 1, n - i - 1) && f; ++l) {
                for (int j = 0; j < m && f; ++j)
                    f &= (b[i - l + 1][j] == b[i + l][j]);
            }
            if (f)
                cntx += i + 1, found = true;
        }
        for (int i = 0; i < m - 1 && !found; ++i) {
            bool f = true;
            for (int l = 1; l <= min(i + 1, m - i - 1) && f; ++l) {
                for (int j = 0; j < n && f; ++j)
                    f &= (b[j][i - l + 1] == b[j][i + l]);
            }
            if (f)
                cnty += i + 1, found = true;
        }
    }
    cout << "task1: " << cntx * 100 + cnty << endl;
}

void task2(vector<vector<string>> a) {
    int cntx = 0, cnty = 0;
    for (auto b : a) {
        int n = b.size(), m = b[0].size();
        bool found = false;
        for (int i = 0; i < n - 1 && !found; ++i) {
            bool f = true, ff = false;
            for (int l = 1; l <= min(i + 1, n - i - 1) && f; ++l) {
                for (int j = 0; j < m && f; ++j) {
                    if (b[i - l + 1][j] != b[i + l][j]) {
                        if (!ff)
                            ff = true;
                        else 
                            f = false;
                    }

                }
            }
            if (f && ff)
                cntx += i + 1, found = true;
        }
        for (int i = 0; i < m - 1 && !found; ++i) {
            bool f = true, ff = false;
            for (int l = 1; l <= min(i + 1, m - i - 1) && f; ++l) {
                for (int j = 0; j < n && f; ++j)
                    if (b[j][i - l + 1] != b[j][i + l]) {
                        if (!ff)
                            ff = true;
                        else 
                            f = false;
                    }
            }
            if (f && ff)
                cnty += i + 1, found = true;
        }
    }
    cout << "task2: " << cntx * 100 + cnty << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<vector<string>> a;
    string s;
    while (getline(cin, s)) {
        a.emplace_back();
        do {
            a.back().push_back(s);
        } while (getline(cin, s) && s != "");
    }
    task1(a);
    task2(a);
    return 0;
}