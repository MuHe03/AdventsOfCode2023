#include <bits/stdc++.h>
using namespace std;

const int dirx[] = {-1, 0, 1, 0};
const int diry[] = {0, -1, 0, 1};

typedef long long ll;
int n, m;

bool ok(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

void go(vector<string> &a) {
    for (int k = 0; k < 2; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                if (a[i][j] == 'O') {
                    int x = i, y = j, nx = x + dirx[k], ny = y + diry[k];
                    while (ok(nx, ny) && a[nx][ny] == '.') {
                        x = nx, y = ny, nx += dirx[k], ny += diry[k];
                    }
                    a[i][j] = '.';
                    a[x][y] = 'O';
                }
    for (int k = 2; k < 4; ++k)
        for (int i = n - 1; i >= 0; --i)
            for (int j = m - 1; j >= 0; --j)
                if (a[i][j] == 'O') {
                    int x = i, y = j, nx = x + dirx[k], ny = y + diry[k];
                    while (ok(nx, ny) && a[nx][ny] == '.') {
                        x = nx, y = ny, nx += dirx[k], ny += diry[k];
                    }
                    a[i][j] = '.';
                    a[x][y] = 'O';
                }
}
ll calc(vector<string> &a) {
    ll ans = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] == 'O')
                ans += n - i;
    return ans;
}
int main() {
    freopen("input.txt", "r", stdin);
    string s;
    vector<string> a;
    while (getline(cin, s))
        a.push_back(s);
    n = a.size(), m = a[0].size();


    ll ans = 0;
    for (int i = 0; i < m; ++i) {
        int cur = 0, st = 0;
        for (int j = 0; j < n; ++j) {
            if (a[j][i] == 'O')
                cur++;
            else if (a[j][i] == '#') {
                for (int k = st; k < st + cur; ++k)
                    ans += n - k;
                st = j + 1, cur = 0;
            }
        }
        if (st < n)
            for (int k = st; k < st + cur; ++k)
                ans += n - k;
    }
    cout << "task1: " << ans << endl;
    set<vector<string>> ss;

    int cnt = 0;
    do {
        ss.insert(a);
        go(a), ++cnt;
    } while (ss.find(a) == ss.end());
    auto la = a;
    int len = 0;
    do {
        go(a), ++len;
    } while(la != a);
    cnt -= len;
    int res = (1000000000 - cnt) % len;
    while (res--) {
        go(a);
    }
    cout << "task2: " << calc(a) << endl;
    return 0;
}