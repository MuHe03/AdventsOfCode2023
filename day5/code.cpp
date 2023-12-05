#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int len = 7;

vector<ll> getnum(string s) {
    stringstream ss(s);
    ll x;
    vector<ll> ret;
    while (ss >> x)
        ret.push_back(x);
    return ret;
}

vector<tuple<ll, ll, ll>> getrel() {
    vector<tuple<ll, ll, ll>> ret;
    string s;
    while (getline(cin, s) && (!s.length() || s.back() == ':'));
    do {
        vector<ll> val = getnum(s);
        ret.push_back({val[1], val[1] + val[2] - 1, val[0] - val[1]});
    } while(getline(cin, s) && s.length());
    return ret;
}

void task1(vector<ll> seeds, vector<vector<tuple<ll, ll, ll>>> rels) {
    auto loc = seeds;
    for (auto rel : rels) {
        vector<ll> nxt = loc;
        for (auto [l, r, v] : rel) {
            for (ll i = 0; i < seeds.size(); ++i)
                if (loc[i] >= l && loc[i] <= r)
                    nxt[i] = loc[i] + v;
        }
        loc = nxt;
    }
    assert(min_element(loc.begin(), loc.end()) != loc.end());
    cout << "task1: " << (*min_element(loc.begin(), loc.end())) << endl;
}

void task2(vector<ll> seeds, vector<vector<tuple<ll, ll, ll>>> rels) {
    set<pair<ll, ll>> s;
    for (int i = 0; i < seeds.size(); i += 2)
        s.insert({seeds[i], seeds[i] + seeds[i + 1] - 1});
    
    for (auto rel : rels) {
        map<pair<ll, int>, ll> m;
        for (auto [l, r, v] : rel)
            m[{l - 1, 1}] = v, m[{r, -1}] = v;
        m[{LONG_LONG_MAX - 1, 1}] = 0;
        auto nxt = s;
        for (auto [l, r] : s) {
            nxt.erase({l, r});
            while (l <= r) {

                auto [pp, v] = *m.lower_bound({l, -2});
                auto [pos, sign] = pp;
                pos = min(pos, r);
                if (sign == 1)
                    nxt.insert({l, pos});
                else 
                    nxt.insert({l + v, pos + v});
                l = pos + 1;
            }
        }
        s = nxt;
    }
    cout << "task2: " << (*s.begin()).first << endl;
} 

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    getline(cin, s);
    s.erase(0, s.find(':') + 2);
    auto seeds = getnum(s);
    vector<vector<tuple<ll, ll, ll>>> rels;
    for (int i = 0; i < len; ++i)
        rels.push_back(getrel());
    for (auto &rel : rels)
        sort(rel.begin(), rel.end());

    task1(seeds, rels);
    task2(seeds, rels);
    return 0;
}