#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int dirx[] = {0, 0, 1, -1};
const int diry[] = {1, -1, 0, 0};


struct Dijkstra {
    int n; 
    vector<vector<pair<int, ll>>> G;
    vector<ll> d;
    Dijkstra(int n) : n(n+1), G(n+1) {}
    void addedge(int x, int y, ll val) { G[x].push_back({y, val}); }

    void calc(int s) {
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> Q;
        vector<bool> done(n+1);
        d.assign(n+1, 1e18); d[s] = 0;
        Q.push({d[s], s});
        while(!Q.empty()) {
            int x = Q.top().second; Q.pop();
            if (done[x]) continue; else done[x] = true;
            for (auto [v, len] : G[x]) if (d[v] > d[x] + len) {
                d[v] = d[x] + len;
                Q.push({d[v], v});
            }
        }
    }
};

int n, m;

void task1(vector<vector<int>> a) {
    vector<vector<vector<vector<int>>>> id(n, vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(4))));
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < 4; ++k)
                for (int g = 0; g < 4; ++g)
                    id[i][j][k][g] = ++cnt;
    Dijkstra g(cnt);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < 4; ++k) {
                int nx = i + dirx[k], ny = j + diry[k];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    continue;
                for (int p = 0; p < 4; ++p) {
                    if (p < 3) {
                        // cout << "1!" << endl;
                        // cout << i << ' ' << j << ' ' << k << ' ' << p << endl;
                        g.addedge(id[i][j][k][p], id[nx][ny][k][p + 1], a[i][j]);
                        // cout << nx << ' ' << ny << ' ' << k << ' ' << p + 1 << endl;
                    }
                    for (int q = 0; q < 4; ++q) 
                        if (k != q) {
                            if (k + q == 1 || k + q == 5)
                                continue;
                            // cout << "!" << endl;
                            // cout << i << ' ' << j << ' ' << k << ' ' << p << endl;
                            g.addedge(id[i][j][q][p], id[nx][ny][k][1], a[i][j]);
                            // cout << nx << ' ' << ny << ' ' << q << ' ' << 1 << endl;
                        }
                }
            }   
    ll ans = INT_MAX;
    g.calc(id[0][0][0][0]);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ans = min(ans, g.d[id[n - 1][m - 1][i][j]]);
    g.calc(id[0][0][2][0]);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            ans = min(ans, g.d[id[n - 1][m - 1][i][j]]);
    cout << "task1: " << ans + a[n - 1][m - 1] - a[0][0] << endl;
}

void task2(vector<vector<int>> a) {
    vector<vector<vector<vector<int>>>> id(n, vector<vector<vector<int>>>(m, vector<vector<int>>(4, vector<int>(11))));
    int cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < 4; ++k)
                for (int g = 4; g <= 10; ++g)
                    id[i][j][k][g] = ++cnt;
    Dijkstra g(cnt);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 0; k < 4; ++k) {
                int nx = i + dirx[k], ny = j + diry[k];
                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    continue;
                for (int p = 4; p < 10; ++p) {
                    int lax = i - dirx[k] * p, lay = j - diry[k] * p;
                    if (lax < 0 || lay < 0 || lax >= n || lay >= m)
                        continue;
                    g.addedge(id[i][j][k][p], id[nx][ny][k][p + 1], a[i][j]);
                }
                nx = i + dirx[k] * 4, ny = j + diry[k] * 4;
                if (nx < 0 || ny < 0 || nx >= n || ny >= m)
                    continue;
                int sum = 0;
                for (int x = 0; x < 4; ++x)
                    sum += a[i + dirx[k] * x][j + diry[k] * x];
                for (int p = 4; p <= 10; ++p) {
                    for (int q = 0; q < 4; ++q) 
                        if (k != q) {
                            if (k + q == 1 || k + q == 5)
                                continue;
                            int lax = i - dirx[q] * p, lay = j - diry[q] * p;
                            if (lax < 0 || lay < 0 || lax >= n || lay >= m)
                                continue;
                            g.addedge(id[i][j][q][p], id[nx][ny][k][4], sum);
                        }
                }
            }   
    ll ans = INT_MAX;
    int sum = 0;
    for (int i = 0; i < 4; ++i) 
        sum += a[i][0];
    g.addedge(id[0][0][2][0], id[4][0][2][4], sum);
    sum = 0;
    for (int i = 0; i < 4; ++i) 
        sum += a[0][i];
    g.addedge(id[0][0][0][0], id[0][4][0][4], sum);
    g.calc(id[0][0][0][0]);
    for (int i = 0; i < 4; ++i)
        for (int j = 4; j <= 10; ++j)
            ans = min(ans, g.d[id[n - 1][m - 1][i][j]]);
    g.calc(id[0][0][2][0]);
    for (int i = 0; i < 4; ++i)
        for (int j = 4; j <= 10; ++j)
            ans = min(ans, g.d[id[n - 1][m - 1][i][j]]);
    cout << "task2: " << ans + a[n - 1][m - 1] - a[0][0] << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<vector<int>> a;
    string s;
    while (getline(cin, s)) {
        a.push_back(vector<int>(s.size()));
        for (int i = 0; i < s.size(); ++i)
            a.back()[i] = s[i] - '0';
    }
    
    n = a.size(), m = a[0].size();
    task1(a);
    task2(a);
    return 0;
}