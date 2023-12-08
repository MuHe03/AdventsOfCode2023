#include <bits/stdc++.h>
using namespace std;

void task1(vector<pair<pair<vector<int>, vector<int>>, int>> a) {
    vector<pair<pair<int, vector<int>>, int>> id(a.size());
    for (int i = 0; i < a.size(); ++i) {
        auto [bb, cnt] = a[i];
        auto [b, kk] = bb;
        int pri = 0;
        if (b.size() == 1) 
            pri = -1;
        else if (b.size() == 2 && b[0] == 4) 
            pri = -2;
        else if (b.size() == 2) 
            pri = -3;
        else if (b.size() == 3 && b[0] == 3) 
            pri = -4;
        else if (b.size() == 3 && b[0] == 2) 
            pri = -5;
        else if (b.size() == 4) 
            pri = -6;
        else 
            pri = -7;
        id[i] = {{pri, kk}, i};
    }
    sort(id.begin(), id.end());
    int ans = 0;
    for (int i = 0; i < id.size(); ++i)
        ans += a[id[i].second].second * (i + 1);
    cout << "task1: " << ans << endl;
}

void task2(vector<pair<pair<vector<int>, vector<int>>, pair<int, int>>> a) {
    vector<pair<pair<int, vector<int>>, int>> id(a.size());
    for (int i = 0; i < a.size(); ++i) {
        auto [bb, cntt] = a[i];
        auto [b, kk] = bb;
        auto [cntj, cnt] = cntt;
        int pri = 0;
        if (b.size() == 1 || b.size() == 0) 
            pri = -1;
        else if (b.size() == 2 && b[0] + cntj == 4) 
            pri = -2;
        else if (b.size() == 2)
            pri = -3;
        else if (b.size() == 3 && b[0] + cntj == 3)
            pri = -4;
        else if (b.size() == 3 && b[0] + cntj == 2) 
            pri = -5;
        else if (b.size() == 4) 
            pri = -6;
        else 
            pri = -7;
        id[i] = {{pri, kk}, i};
    }
    sort(id.begin(), id.end());
    int ans = 0;
    for (int i = 0; i < id.size(); ++i)
        ans += a[id[i].second].second.second * (i + 1);
    cout << "task2: " << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string ss = "AKQT98765432J";
    string s;
    vector<pair<pair<vector<int>, vector<int>>, pair<int, int>>> a;
    while (getline(cin, s)) {
        vector<int> b(128);
        int cntj = 0;
        for (auto ch : s)
            if (ch == ' ')
                break;
            else  {
                if (ch == 'J')
                    ++cntj;
                else 
                    ++b[ch];
            }
        vector<int> kk;
        for (int i = 0; i < 5; ++i)
            kk.push_back(ss.size() - ss.find(s[i]));
        int cnt = stoi(s.erase(0, s.find(' ') + 1));
        auto c = b;
        sort(b.begin(), b.end());
        reverse(b.begin(), b.end());
        int pos = 0;
        while(b[pos])
            ++pos;
        b.erase(b.begin() + pos, b.end());
        vector<bool> book(ss.size());
        a.push_back({{b, kk}, {cntj, cnt}});
    }

    // task1(a);
    task2(a);
}