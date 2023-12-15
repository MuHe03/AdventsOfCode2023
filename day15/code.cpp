#include <bits/stdc++.h>
using namespace std;

unsigned char HASH(string s) {
    unsigned char ret = 0;
    for (char ch : s)
        ret += ch, ret *= 17;
    return ret;
}

void task1(string s) {
    int pos;
    int ans = 0;
    while ((pos = s.find(',')) != -1) {
        ans += HASH(s.substr(0, pos));
        s.erase(0, pos + 1);
    }
    ans += HASH(s);
    cout << "task1: " << ans << endl;
}

tuple<int, string, int> calc(string s) {
    int pos = 0, ty = 0, len = -1;
    if (s.find('-') != -1)
        pos = s.find('-'), ty = 1;
    if (s.find('=') != -1)
        pos = s.find('='), ty = 2;
    string x = s.substr(0, pos);
    if (ty == 2)
        len = stoi(s.substr(pos + 1));
    return {ty, x, len};
}

void task2(string s) {
    int pos;
    vector<map<string, int>> t(256);
    vector<vector<string>> p(256);
    while ((pos = s.find(',')) != -1) {
        string ss = s.substr(0, pos);
        auto [ty, x, len] = calc(ss);
        int v = HASH(x);
        if (ty == 1) {
            if (t[v].count(x))
                t[v].erase(x), p[v].erase(find(p[v].begin(), p[v].end(), x));
        }
        else {
            if (!t[v].count(x))
                p[v].push_back(x);
            t[v][x] = len;
        }
        s.erase(0, pos + 1);
    }
    {
        auto [ty, x, len] = calc(s);
        int v = HASH(x);
        if (ty == 1) {
            if (t[v].count(x))
                t[v].erase(x), p[v].erase(find(p[v].begin(), p[v].end(), x));
        }
        else {
            if (!t[v].count(x))
                p[v].push_back(x);
            t[v][x] = len;
        }
    }

    long long ans = 0;
    for (int i = 0; i < 256; ++i)
        for (int j = 0; j < p[i].size(); ++j) {
            auto x = p[i][j];
            ans += 1ll * (i + 1) * (j + 1) * t[i][x];
        }
    cout << "task2: " << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    cin >> s;
    task1(s);
    task2(s);
    return 0;
}