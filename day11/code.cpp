#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("input.txt", "r", stdin);
    vector<string> a;
    string s;
    while (getline(cin, s))
        a.push_back(s);

    int n = a.size(), m = a[0].size();
    vector<int> cntx(n + 1, 1), cnty(m + 1, 1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cntx[i + 1] &= (a[i][j] == '.'), cnty[j + 1] &= (a[i][j] == '.');
    vector<int> prex(n + 1, 0), prey(m + 1, 0);
    for (int i = 1; i <= n; ++i)
        prex[i] = prex[i - 1] + cntx[i];
    for (int i = 1; i <= m; ++i)
        prey[i] = prey[i - 1] + cnty[i];

    vector<pair<int, int>> g(1);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (a[i][j] == '#')
                g.push_back({i + 1, j + 1});
    int cnt = g.size() - 1;
    long long ans1 = 0, ans2 = 0;
    for (int i = 1; i <= cnt; ++i)
        for (int j = i; j <= cnt; ++j) {
            auto [x1, y1] = g[i];
            auto [x2, y2] = g[j];
            if (x1 > x2)
                swap(x1, x2);
            if (y1 > y2)
                swap(y1, y2);
            ans1 += x2 - x1 + y2 - y1 + prex[x2] - prex[x1 - 1] + prey[y2] - prey[y1 - 1];
            ans2 += x2 - x1 + y2 - y1 + 1ll * (prex[x2] - prex[x1 - 1] + prey[y2] - prey[y1 - 1]) * (1000000 - 1);
        }
    cout << "task1: " << ans1 << endl;
    cout << "task2: " << ans2 << endl;
    
    return 0;
}