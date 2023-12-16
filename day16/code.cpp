#include <bits/stdc++.h>
using namespace std;

const int dirx[] = {0, 0, 1, -1};
const int diry[] = {1, -1, 0, 0};

int main() {
    freopen("input.txt", "r", stdin);
    vector<string> a;
    string s;
    while (getline(cin, s)) 
        a.push_back(s);

    int n = a.size(), m = a[0].size();
    auto solve = [&](int x, int y, int dir) {
        vector<vector<int>> vis(n, vector<int>(m));
        queue<tuple<int, int, int>> q;
        q.push({x, y, dir});
        while (!q.empty()) {
            auto [x, y, d] = q.front();
            q.pop();
            if (vis[x][y] & (1 << d))
                continue;
            vis[x][y] |= (1 << d);
            vector<int> dirs;
            if (a[x][y] == '/')
                dirs = {3 - d};
            else if (a[x][y] == '\\')
                dirs = {(d + 2) % 4};
            else if (a[x][y] == '-' && (d == 2 || d == 3))
                dirs = {0, 1};
            else if (a[x][y] == '|' && (d == 0 || d == 1))
                dirs = {2, 3};
            else 
                dirs = {d};
            
            for (auto dir : dirs) {
                int nx = x + dirx[dir], ny = y + diry[dir];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    continue;
                q.push({nx, ny, dir});
            }
        }
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // cout << (bitset<4>) vis[i][j] << ' ';
                cnt += (vis[i][j] > 0);
            }
            // cout << endl;
        }
        return cnt;
    };
    cout << "task1: " << solve(0, 0, 0) << endl;
    int ans = 0;
    for (int i = 0; i < n; ++i)
        ans = max({ans, solve(i, 0, 0), solve(i, m - 1, 1)});
    for (int i = 0; i < m; ++i)
        ans = max({ans, solve(0, i, 2), solve(n - 1, i, 3)});
    cout << "task2: " << ans << endl;
    return 0;
}