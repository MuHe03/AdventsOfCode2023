#include <bits/stdc++.h>
using namespace std;

const int dirx[] = {0, 0, 1, -1};
const int diry[] = {1, -1, 0, 0};

void task(vector<string> a) {
    queue<tuple<int, int, int>> q;
    vector<vector<int>> dirs(128);
    dirs['S'] = {0, 2};
    dirs['|'] = {3, 2};
    dirs['-'] = {0, 1};
    dirs['F'] = {0, 2};
    dirs['J'] = {1, 3};
    dirs['7'] = {1, 2};
    dirs['L'] = {0, 3};
    int n = a.size(), m = a[0].size();
    pair<int, int> s, e;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] == 'S')
                s = {i, j}, a[i][j] = 'F';
    int ans = 0;
    vector<vector<int>> vis(n, vector<int>(m, -1));
    vector<vector<pair<int, int>>> la(n, vector<pair<int, int>>(m));
    function<void(int, int, int)> dfs = [&](int x, int y, int t) {
        vis[x][y] = t;
        if (a[x][y] == '.')
            return;
        if (t > ans)
            ans = t, e = {x, y};
        for (auto dir : dirs[a[x][y]]) {
            int nx = x + dirx[dir], ny = y + diry[dir];
            if (nx < 0 || ny < 0 || nx >= n || ny >= m || ~vis[nx][ny])
                continue;
            la[nx][ny] = {x, y};
            dfs(nx, ny, t + 1);
        }
    };
    dfs(s.first, s.second, 0);
    vis = vector<vector<int>>(n, vector<int>(m, 0));
    vis[e.first][e.second] = 1;
    while (e != s)
        e = la[e.first][e.second], vis[e.first][e.second] = 1;
    cout << "task1: " << (ans + 1) / 2 << endl;
    vector<vector<char>> nmp(2 * n + 2, vector<char>(2 * m + 2, '.'));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (vis[i][j])
                nmp[i << 1 | 1][j << 1 | 1] = a[i][j];
    for (int i = 2; i < n * 2; i += 2)
        for (int j = 1; j < m * 2; j += 2)
            if (nmp[i - 1][j] == '|' || nmp[i - 1][j] == 'F' || nmp[i - 1][j] == '7')
                if (nmp[i + 1][j] == '|' || nmp[i + 1][j] == 'L' || nmp[i + 1][j] == 'J')
                    nmp[i][j] = '|';
    for (int i = 1; i < n * 2; i += 2)
        for (int j = 2; j < m * 2; j += 2)
            if (nmp[i][j - 1] == '-' || nmp[i][j - 1] == 'L' || nmp[i][j - 1] == 'F')
                if (nmp[i][j + 1] == '-' || nmp[i][j + 1] == '7' || nmp[i][j + 1] == 'J')
                    nmp[i][j] = '-';
    vector<vector<bool>> b(2 * n + 2, vector<bool>(2 * m + 2));
    q.push({0, 0, 0});
    while (!q.empty()) {
        auto [x, y, z] = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirx[i], ny = y + diry[i];
            if (nx < 0 || ny < 0 || nx > n * 2 || ny > m * 2 || b[nx][ny])
                continue;
            b[nx][ny] = true;
            if (nmp[nx][ny] == '.')
                q.push({nx, ny, 0});
        }
    }
    ans = 0;
    for (int i = 0; i <= n * 2; ++i)
        for (int j = 0; j <= m * 2; ++j)
            if (nmp[i][j] == '.' && !b[i][j]) {
                ans += (vis[i >> 1][j >> 1] == 0), vis[i >> 1][j >> 1] = 1;
            }
    cout << "task2: " << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<string> a;
    string s;
    while (getline(cin, s))
        a.push_back(s);
    
    task(a);
    return 0;
}