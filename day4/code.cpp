#include <bits/stdc++.h>
using namespace std;

typedef vector<pair<vector<int>, vector<int>>> C;

vector<int> getnum(string s) {
    stringstream ss(s);
    int x;
    vector<int> ret;
    while (ss >> x)
        ret.push_back(x);
    return ret;
}

void task1(vector<int> cnt) {
    long long ans = 0;
    for (auto x : cnt)
        if (x)
            ans += 1ll << (x - 1);
    cout << "task1: " << ans << endl;
}

void task2(vector<int> cnt) {
    vector<long long> tot(cnt.size(), 1);
    long long ans = 0;
    for (int i = 0; i < cnt.size(); ++i) {
        ans += tot[i];
        if (cnt[i]) {
            for (int j = i + 1; j <= i + cnt[i] && j < cnt.size(); ++j)
                tot[j] += tot[i];
        }
    }
    cout << "task2: " << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    C cards;
    while (getline(cin, s)) {
        s.erase(0, s.find(':') + 2);    
        string s1 = s.substr(0, s.find('|') - 1), s2 = s.substr(s.find('|') + 2);
        cards.push_back({getnum(s1), getnum(s2)});
    }
    vector<int> cnt(cards.size());
    for (int i = 0; i < cards.size(); ++i) {
        set<int> w;
        auto [wc, mc] = cards[i];
        for (int x : wc)
            w.insert(x);
        for (int x : mc)
            if (w.count(x))
                ++cnt[i];
    }

    task1(cnt);
    task2(cnt);
    return 0;
}