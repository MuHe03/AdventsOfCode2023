#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> getnum(string s) {
    stringstream ss(s);
    ll x;
    vector<ll> ret;
    while (ss >> x)
        ret.push_back(x);
    return ret;
}

bool check(vector<ll> cur) {
    for (auto x : cur)
        if (x)
            return true;
    return false;
}

void task1(vector<vector<ll>> a) {
    ll ans = 0;
    for (auto d : a) {
        ll cur = 0;
        while (check(d)) {
            auto c = d;
            cur += d.back();
            d = vector<ll>(d.size() - 1);
            for (int i = 1; i < c.size(); ++i)
                d[i - 1] = c[i] - c[i - 1];
        }
        ans += cur;
    }
    cout << "task1: " << ans << endl;
}

void task2(vector<vector<ll>> a) {
    ll ans = 0;
    for (auto d : a) {
        auto c = d;
        vector<int> bb;
        while (check(d)) {
            bb.push_back(d[0]);
            c = d;
            d = vector<ll>(d.size() - 1);
            for (int i = 1; i < c.size(); ++i)
                d[i - 1] = c[i] - c[i - 1];
        }
        ll x = 0;
        reverse(bb.begin(), bb.end());
        for (auto y : bb) 
            x = y - x;
        ans += x;
    }
    cout << "task2: " << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    vector<vector<ll>> a;
    while (getline(cin, s)) {
        a.push_back(getnum(s));
    }

    task1(a);
    task2(a);
    return 0;
}