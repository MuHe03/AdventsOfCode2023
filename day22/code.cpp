#include <bits/stdc++.h>
using namespace std;

int cnt = 0;
struct cube {
    int id, x1, x2, y1, y2, z1, z2;
    int bot;

    cube(tuple<int, int, int> a, tuple<int, int, int> b) {
        id = cnt++;
        tie(x1, y1, z1) = a;
        tie(x2, y2, z2) = b;
        bot = 0;
    }

    bool operator!=(cube &c) {
        return x1 != c.x1 || x2 != c.x2 || y1 != c.y1 || y2 != c.y2 || z1 != c.z1 || z2 != c.z2;
    }

    bool intersect(cube &c) {
        if (x2 < c.x1 || x1 > c.x2 || y2 < c.y1 || y1 > c.y2) return false;
        return true;
    }

    bool topof(cube &c) {
        if (x2 < c.x1 || x1 > c.x2 || y2 < c.y1 || y1 > c.y2) return false;
        return z1 > c.z2;
    }

    bool operator<(cube &c) {
        return z1 < c.z1;
    }
};

tuple<int, int, int> parse(string s) {
    int x, y, z;
    sscanf(s.c_str(), "%d,%d,%d", &x, &y, &z);
    return make_tuple(x, y, z);
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    vector<cube> v;
    while (getline(cin, s)) {
        string s1 = s.substr(0, s.find('~'));
        string s2 = s.substr(s.find('~') + 1);
        v.push_back(cube(parse(s1), parse(s2)));
    }

    sort(v.begin(), v.end());
    vector<vector<cube*>> vh1(1000), vh2(1000);
    auto checkh = [&](int h, cube &c) {
        if (h == 0) return false;
        for (auto cc : vh2[h]) {
            if ((*cc).intersect(c)) return false;
        }
        return true;
    };
    for (int i = 0; i < v.size(); ++i) {
        cube &c = v[i];
        while (c.z1 > 1 && checkh(c.z1 - 1, c)) --c.z1, --c.z2;
        vh1[c.z1].push_back(&c);
        vh2[c.z2].push_back(&c);
    }
    for (int i = 0; i < v.size(); ++i) {
        cube &c = v[i];
        int h = c.z1;
        for (auto cc : vh2[h - 1])
            if ((*cc).intersect(c))
                ++c.bot;
    }
    int ans1 = 0, ans2 = 0;

    for (int h = 1; h < 1000; ++h) {
        for (auto c : vh2[h]) {
            bool f = true;
            for (auto cc : vh1[h + 1])
                if ((*cc).intersect(*c) && (*cc).bot == 1) {
                    f = false;
                    break;
                }
            if (f) ++ans1;
            else {
                auto vv = v;
                queue<cube*> q;
                q.push(c);
                while (!q.empty()) {
                    cube cc = *q.front();
                    q.pop();
                    int h = cc.z2;
                    ++ans2;
                    for (auto ccc : vh1[h + 1]) {
                        if ((*ccc).intersect(cc)) {
                            (*ccc).bot--;
                            if ((*ccc).bot == 0) {
                                q.push(ccc);
                            }
                        }
                    }
                }
                --ans2;
                v = vv;
            }
        }
    }
    
    cout << "task1: " << ans1 << endl;
    cout << "task2: " << ans2 << endl;
    return 0;
}