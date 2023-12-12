#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<int> getnum(string s) {
    for (auto &ch : s)
        if (ch == ',')
            ch = ' ';
    stringstream ss(s);
    int x;
    vector<int> ret;
    while (ss >> x)
        ret.push_back(x);
    return ret;
}

vector<vector<ll>> ff;
ll dfs(int posx, int posy, string &x, vector<int> &y) {
    if (ff[posx][posy] != -1)
        return ff[posx][posy];
    if (posy == y.size()) {
        bool f = false;
        for (int i = posx; i < x.size(); ++i)
            f |= x[i] == '#';
        if (f)
            return ff[posx][posy] = 0ll;
        return ff[posx][posy] = 1ll;
    }
    else if (posx + y[posy] > x.size()) {
        return ff[posx][posy] = 0ll;
    }
    else {
        bool f = true;
        for (int i = posx; i < posx + y[posy]; ++i)
            f &= (x[i] == '?' || x[i] == '#');
        f &= (posx + y[posy] == x.size() || x[posx + y[posy]] != '#');
        ll ret = 0;
        if (f)
            ret += dfs(posx + y[posy] + 1, posy + 1, x, y);
        if (x[posx] != '#')
            ret += dfs(posx + 1, posy, x, y);
        return ff[posx][posy] = ret;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    vector<pair<string, vector<int>>> a;
    string s;
    while (getline(cin, s)) {
        int pos = s.find(' ');
        string s1 = s.substr(0, pos);
        auto v = getnum(s.substr(pos + 1));
        a.push_back({s1, v});
    }


    ll ans = 0;
    for (auto [x, y] : a) {
        ff = vector<vector<ll>>(50, vector<ll>(50, -1));
        ans += dfs(0, 0, x, y);
    }
    cout << "task1: " << ans << endl;

    ans = 0;
    for (auto &[x, y] : a) {
        ff = vector<vector<ll>>(500, vector<ll>(500, -1));
        x = x + "?" + x + "?" + x + "?" + x + "?" + x;
        auto yy = y;
        for (int i = 0; i < 4; ++i)
            for (auto v : y)
                yy.push_back(v);
        y = yy;
        ans += dfs(0, 0, x, y);
    }
    cout << "task2: " << ans << endl;

    return 0;
}
