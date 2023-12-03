#include <bits/stdc++.h>
using namespace std;

void task1(vector<pair<int, tuple<int, int, int>>> nums, vector<vector<char>> sym) {
    int sum = 0;
    for (auto [val, pos] : nums) {
        auto [x, y, len] = pos;
        bool f = false;
        for (int i = max(0, x - 1); i < min((int)sym.size(), x + 2); ++i)
            for (int j = max(0, y - len); j < min((int)sym[0].size(), y + 2); ++j) 
                f |= sym[i][j];
        if (f)
            sum += val;
    }
    cout << "task1: " << sum << endl;
}

void task2(vector<pair<int, tuple<int, int, int>>> nums, vector<vector<char>> sym) {
    vector<vector<vector<int>>> b(sym.size(), vector<vector<int>>(sym[0].size()));
    for (auto [val, pos] : nums) {
        auto [x, y, len] = pos;
        bool f = false;
        for (int i = max(0, x - 1); i < min((int)sym.size(), x + 2); ++i)
            for (int j = max(0, y - len); j < min((int)sym[0].size(), y + 2); ++j) 
                if (sym[i][j] == '*')
                    b[i][j].push_back(val);
    }
    long long sum = 0;
    for (int i = 0; i < sym.size(); ++i)
        for (int j = 0; j < sym[0].size(); ++j)
            if (b[i][j].size() == 2)
                sum += 1ll * b[i][j][0] * b[i][j][1];
    cout << "task2: " << sum << endl;
}


int main() {
    freopen("input.txt", "r", stdin);
    vector<string> a;
    a.emplace_back();
    while (getline(cin, a.back()))
        a.emplace_back();
    a.pop_back();
    vector<pair<int, tuple<int, int, int>>> nums;
    vector<vector<char>> sym(a.size(), vector<char>(a[0].size(), 0));
    for (int j = 0; j < a.size(); ++j) {
        string num;
        for (int i = 0; i < a[j].length(); ++i) {
            if (isdigit(a[j][i])) {
                num += a[j][i];
                if (i + 1 == a[j].length() || !isdigit(a[j][i + 1])) {
                    nums.push_back({stoi(num), {j, i, num.size()}});
                    num = "";
                }
            }
            else if (a[j][i] != '.')
                sym[j][i] = a[j][i];
        }
    }

    task1(nums, sym);
    task2(nums, sym);
    return 0;
}