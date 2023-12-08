#include <bits/stdc++.h>
using namespace std;

const int n = 26 * 26 * 26;
int id(string s) {
    return 26 * 26 * (s[0] - 'A') + 26 * (s[1] - 'A') + s[2] - 'A';
}


void task1(vector<int> dir, vector<tuple<int, int, int>> a) {
    vector<vector<int>> g(n);
    int cnt = 0, cur = 0, ans = 0;
    for (auto [x, y, z] : a)
        g[x] = {y, z};
    while (cur != n - 1) {
        cur = g[cur][dir[cnt]], ++cnt, cnt %= dir.size(), ++ans;
    }
    cout << "task1: " << ans << endl;
}


void task2(vector<int> dir, vector<tuple<int, int, int>> a) {
    vector<vector<int>> g(n);
    vector<int> pos;
    for (auto [x, y, z] : a) {
        g[x] = {y, z};
        if (x % 26 == 0)
            pos.push_back(x);
    }
    int cnt = 0, tot = pos.size();
    vector<int> len(pos.size());
    while (tot) {
        for (int i = 0; i < pos.size(); ++i)
            if (pos[i] % 26 == 25 && !len[i]) {
                int cntt = cnt, cur = pos[i];
                while (cur != pos[i] || !len[i]) {
                    ++len[i];
                    cur = g[cur][dir[cntt]];
                    cntt = (cntt + 1) % dir.size();
                }
                --tot;
            }
        for (auto &x : pos)
            x = g[x][dir[cnt]];
        ++cnt, cnt %= dir.size();
    }
    long long ans = 1;
    for (int x : len)
        if (x)
            ans = lcm(ans, x);
    cout << "task2: " << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    getline(cin, s);
    vector<int> dir;
    for (char ch : s) 
        dir.push_back(ch == 'R');
    getline(cin, s);
    vector<tuple<int, int, int>> a;

    while (getline(cin, s)) {
        string s1 = s.substr(0, 3), s2 = s.substr(7, 3), s3 = s.substr(12, 3);
        int x = id(s1), y = id(s2), z = id(s3);
        a.push_back({x, y, z});
    }
    
    // task1(dir, a);
    task2(dir, a);
    
    return 0;
}