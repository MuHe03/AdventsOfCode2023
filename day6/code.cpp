#include <bits/stdc++.h>
using namespace std;

void task1(vector<int> t, vector<int> d) {
    long long ans = 1;
    for (int i = 0; i < t.size(); ++i) {
        int cnt = 0;
        for (int k = 0; k <= t[i]; ++k)
            cnt += ((t[i] - k) * k > d[i]);
        ans *= cnt;
    }
    cout << "task1: " << ans << endl;
}

void task2(vector<int> tt, vector<int> dd) {
    string ts, ds;
    for (auto x : tt)
        ts += to_string(x);
    for (auto x : dd)
        ds += to_string(x);
    long long t = stoll(ts), d = stoll(ds);
    long long cnt = 0;
    for (long long k = 0; k <= t; ++k)
        cnt += ((t - k) * k > d);
    cout << "task2: " << cnt << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string ts, ds;
    getline(cin, ts);
    getline(cin, ds);
    ts = ts.substr(ts.find_first_of("01234565789"));
    ds = ds.substr(ds.find_first_of("01234565789"));
    stringstream st(ts), sd(ds);
    vector<int> t, d;
    while (st.good())
        t.emplace_back(), st >> t.back();
    while (sd.good())
        d.emplace_back(), sd >> d.back();
    
    task1(t, d);
    task2(t, d);
}