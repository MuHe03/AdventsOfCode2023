#include <bits/stdc++.h>
using namespace std;

tuple<int, int, int> parse2(string s) {
    int p = s.find(' '), cnt = stoi(s.substr(0, p));
    s.erase(0, p + 1);
    if (s == "red")
        return {cnt, 0, 0};
    if (s == "green")
        return {0, cnt, 0};
    if (s == "blue")
        return {0, 0, cnt};
    return {0, 0, 0};
}

tuple<int, int, int> parse(string s) {
    int p = -1;
    int r = 0, g = 0, b = 0;
    while ((p = s.find(',')) != -1) {
        auto [rr, gg, bb] = parse2(s.substr(0, p));
        r += rr, g += gg, b += bb;
        s.erase(0, p + 2);
    }
    auto [rr, gg, bb] = parse2(s.substr(0, p));
    r += rr, g += gg, b += bb;
    return {r, g, b};
}

void task1(vector<vector<tuple<int, int, int>>> games) {
    tuple<int, int, int> target{12, 13, 14};
    int ans = 0;
    for (int i = 0; i < games.size(); ++i) {
        bool f = true;
        for (int j = 0; j < games[i].size(); ++j) {
            auto [r1, g1, b1] = target;
            auto [r2, g2, b2] = games[i][j];
            f &= r1 <= r2 && g1 <= g2 && b1 <= b2;
        }
        if (f)
            ans += i + 1;
    }
    cout << "task1: " << ans << endl;
}

void task2(vector<vector<tuple<int, int, int>>> games) {
    long long ans = 0;
    for (auto game : games) {
        int r = 0, g = 0, b = 0;
        for (auto [rr, gg, bb] : game)
            r = max(r, rr), g = max(g, gg), b = max(b, bb);
        ans += 1ll * r * g * b;
    }
    cout << "task2: " << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    vector<vector<tuple<int, int, int>>> games;
    while (getline(cin, line)) {
        games.emplace_back();
        line.erase(0, line.find(':') + 2);
        int p = -1;
        while ((p = line.find(';')) != -1) {
            games.back().push_back(parse(line.substr(0, p)));
            line.erase(0, p + 2);
        }
        games.back().push_back(parse(line));
    }

    task1(games);
    task2(games);

    return 0;
}