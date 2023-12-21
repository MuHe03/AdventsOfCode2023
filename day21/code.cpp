#include <bits/stdc++.h>
using namespace std;

int dirx[] = {0, 0, 1, -1};
int diry[] = {1, -1, 0, 0};

int main() {
    freopen("input.txt", "r", stdin);
    string ss;
    vector<string> a;
    while (getline(cin, ss))
        a.push_back(ss);
    pair<int, int> s;
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) 
            if (a[i][j] == 'S')
                s = {i, j}, a[i][j] = '.';
    {
        int tot = 64;
        vector<vector<bool>> b(n, vector<bool>(m));
        queue<tuple<int, int, int>> q;
        q.push({s.first, s.second, 0});
        while (!q.empty()) {
            auto [x, y, d] = q.front();
            q.pop();
            if (d == tot + 1)
                continue;
            if (b[x][y])
                continue;
            b[x][y] = true;
            for (int i = 0; i < 4; ++i) {
                int nx = x + dirx[i], ny = y + diry[i];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m || a[nx][ny] == '#')
                    continue;
                q.push({nx, ny, d + 1});
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) 
                if (b[i][j] && (((i - s.first) + (j - s.second)) % 2 + 2) % 2 == tot % 2)
                    ans += b[i][j];
        cout << "task1: " << ans << endl;
    }

    {
        int tot = 26501365;
        vector<vector<vector<int>>> dis(9, vector<vector<int>>(n, vector<int>(m, -1)));
        assert(n / 2 == s.first);
        assert(m / 2 == s.second);
        vector<pair<int, int>> stp = {{n / 2, 0}, {0, m / 2}, {n / 2, m - 1}, {n - 1, m / 2}, {0, 0}, {0, m - 1}, {n - 1, m - 1}, {n - 1, 0}, s};
        long long ans = 0;
        for (int k = 0; k < 9; ++k) {
            queue<tuple<int, int, int>> q;
            vector<vector<bool>> b(n, vector<bool>(m));
            q.push({stp[k].first, stp[k].second, 0});
            while (!q.empty()) {
                auto [x, y, d] = q.front();
                q.pop();
                if (b[x][y])
                    continue;
                b[x][y] = true;
                dis[k][x][y] = d;
                for (int i = 0; i < 4; ++i) {
                    int nx = x + dirx[i], ny = y + diry[i];
                    if (nx < 0 || ny < 0 || nx >= n || ny >= m || a[nx][ny] == '#')
                        continue;
                    q.push({nx, ny, d + 1});
                }
            }
            // cout << stp[k].first << ' ' << stp[k].second << ':' << endl;
            // for (int i = 0; i < n; ++i) {
            //     for (int j = 0; j < m; ++j) 
            //         cout << dis[k][i][j] << ' ';
            //     cout << endl;
            // }
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < m; ++j) 
                    if (dis[k][i][j] != -1) {
                        if (k < 4) {
                            int cnt = (tot - dis[k][i][j] - s.first - 1) / n + 1;
                            if ((((i - s.first) + (j - s.second) + s.first) % 2 + 2) % 2 == tot % 2)
                                ans += (cnt + 1) / 2;
                            else 
                                ans += cnt / 2;
                        }
                        else if (k < 8) {
                            int cnt = (tot - dis[k][i][j] - s.first - s.second - 2) / n + 1;
                            if ((((i - s.first) + (j - s.second)) % 2 + 2) % 2 == tot % 2) {
                                int cc = (cnt + 1) / 2, e = 1 + (cc - 1) * 2;
                                ans += 1ll * (e + 1) * cc / 2;
                            }
                            else {
                                int cc = cnt / 2, e = cc * 2;
                                ans += 1ll * (e + 2) * cc / 2;
                            }
                        }
                        else if ((((i - s.first) + (j - s.second)) % 2 + 2) % 2 == tot % 2)
                            ++ans;
                    }
        }
        cout << "task2: " << ans << endl;
    }
    return 0;
}