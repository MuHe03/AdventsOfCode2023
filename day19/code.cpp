#include <bits/stdc++.h>
using namespace std;

const int MIN = 1;
const int MAX = 4000;

typedef long long ll;

struct rate {
    vector<int> a;
    rate() {
        a = vector<int>(4, 0);
    }
    rate(string s) {
        int pos;
        while ((pos = s.find('=')) != -1) {
            int nxt = s.find(',', pos + 1);
            if (nxt == -1) {
                a.push_back(stoi(s.substr(pos + 1)));
                break;
            }
            else
                a.push_back(stoi(s.substr(pos + 1, nxt - pos - 1)));
            s.erase(0, nxt + 1);
        }
    }

    int operator [](int i) const {
        return a[i];
    }

    void print() {
        for (int i = 0; i < 4; ++i)
            cout << a[i] << ' ';
        cout << endl;
    }
};

struct filter {
    int ty, mn, mx;
    filter() {
        ty = -1;
        mn = MIN, mx = MAX;
    }
    filter(string s) {
        ty = -1;
        mn = MIN, mx = MAX;
        if (s[0] == 'x')
            ty = 0;
        else if (s[0] == 'm')
            ty = 1;
        else if (s[0] == 'a')
            ty = 2;
        else 
            ty = 3;
        if (s[1] == '<')
            mx = stoi(s.substr(2)) - 1;
        else
            mn = stoi(s.substr(2)) + 1;
    }

    bool valid(rate x) {
        if (ty == -1)
            return true;
        else if (ty == -2)
            return false;
        else
            return x[ty] >= mn && x[ty] <= mx;
    }
    void print() {
        cout << ty << ':' << mn << '-' << mx << endl;
    }
    filter operator !() {
        filter c;
        c.ty = ty;
        if (c.ty == -1)
            return (*this);
        if (mn == MIN)
            c.mn = mx + 1, c.mx = MAX;
        else
            c.mn = MIN, c.mx = mn - 1;
        return c;
    }
};

struct rule {
    vector<filter> a;
    rule() {
        a = vector<filter>(4);
        for (int i = 0; i < 4; ++i)
            a[i].ty = i;
    }
    rule(filter x) {
        a = vector<filter>(4);
        if (x.ty != -1)
            a[x.ty] = x;
        for (int i = 0; i < 4; ++i)
            if (a[i].ty == -1)
                a[i].ty = i;
    }

    bool valid(rate x) {
        for (int i = 0; i < 4; ++i)
            if (!a[i].valid(x))
                return false;
        return true;
    }

    bool valid() {
        for (int i = 0; i < 4; ++i)
            if (a[i].ty == -2)
                return false;
        return true;
    }
    
    ll count() {
        ll ans = 1;
        for (int i = 0; i < 4; ++i)
            if (a[i].ty != -2)
                ans *= a[i].mx - a[i].mn + 1;
            else 
                return 0;
        return ans;
    }

    void print() {
        for (int i = 0; i < 4; ++i)
            a[i].print();
        cout << endl;
    }
};

rule operator &(rule a, rule b) {
    rule c;
    for (int i = 0; i < 4; ++i)
        if (a.a[i].ty == -2 || b.a[i].ty == -2)
            c.a[i].ty = -2;
        else {
            c.a[i].mn = max(a.a[i].mn, b.a[i].mn);
            c.a[i].mx = min(a.a[i].mx, b.a[i].mx);
            if (c.a[i].mn > c.a[i].mx)
                c.a[i].ty = -2;
        }
    for (int i = 0; i < 4; ++i)
        if (c.a[i].ty == -1)
            c.a[i].ty = i;
    return c;
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    vector<rate> v;
    vector<vector<pair<string, filter>>> g;
    vector<string> names;
    map<string, int> m;
    int cnt = 0;
    while (getline(cin, s) && s.size()) {
        string name = s.substr(0, s.find('{'));
        m[name] = cnt++;
        names.push_back(name);
        g.emplace_back();
        s.erase(0, s.find('{') + 1);
        while (s.find(',') != -1) {
            string s1 = s.substr(0, s.find(','));
            filter c(s1.substr(0, s1.find(':')));
            g.back().push_back({s1.substr(s1.find(':') + 1), c});
            s.erase(0, s.find(',') + 1);
        }
        g.back().push_back({s.substr(0, s.find('}')), filter()});
    }
    while (getline(cin, s))
        v.push_back(rate(s));
    m["A"] = cnt++;
    names.push_back("A");
    vector<vector<pair<string, rule>>> g2(cnt);
    for (int i = 0; i < cnt; ++i) {
        rule r;
        for (auto [s, f] : g[i]) {
            if (s != "R")
                g2[m[s]].push_back({names[i], r & rule(f)});
            r = r & rule(!f);
        }
    }
    ll ans = 0;
    for (rate x : v) {
        string cur = "in";
        while (m.count(cur) && cur != "A") {
            int id = m[cur];
            for (auto y : g[id])
                if (y.second.valid(x)) {
                    cur = y.first;
                    break;
                }
        }
        if (cur == "A")
            ans += x[0] + x[1] + x[2] + x[3];
    }
    cout << "task1: " << ans << endl;
    
    vector<vector<bool>> vis(4, vector<bool>(4001, true));
    queue<pair<string, rule>> q;
    q.push({"A", rule()});
    ans = 0;
    while (!q.empty()) {
        auto [s, r] = q.front();
        q.pop();
        if (!r.valid())
            continue;
        if (s == "in") {
            ans += r.count();
            continue;
        }
        for (auto [s1, r1] : g2[m[s]]) {
            rule r2 = r & r1;
            q.push({s1, r2});
        }
    }
    cout << "task2: " << ans << endl;
    return 0;
}