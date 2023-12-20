#include <bits/stdc++.h>
using namespace std;

int cnt[2];
map<string, int> m;
queue<tuple<bool, int, int>> q;

struct Module {
    string name;
    vector<Module*> nxt;
    Module(string name) : name(name) {}

    virtual void trigger(bool sig, Module *from) {
        ++cnt[sig];
    }

    virtual void print() {
        cout << "Module: " << name << endl;
        for (auto &i : nxt)
            cout << i->name << " ";
        cout << endl;
    }
};
vector<Module *> a;

struct Flipflop : Module {
    bool status;

    Flipflop(string name) : Module(name) {
        status = false;
    }

    void init() {
        status = false;
    }

    void trigger(bool sig, Module *from) {
        // cout << "trigger: " << name << " " << sig << endl;
        ++cnt[sig];
        if (!sig) {
            status = !status;
            for (auto &i : nxt)
                q.push({status, m[i->name], m[name]});
        }
    }

    void print() {
        cout << "Flipflop: " << name << " " << status << endl;
        for (auto &i : nxt)
            cout << i->name << " ";
        cout << endl;
    }

};

struct Broadcaster : Module {
    Broadcaster(string name) : Module(name) {
    }

    void init() {
    }

    void trigger(bool sig, Module *from) {
        // cout << "trigger: " << name << " " << sig << endl;
        ++cnt[sig];
        for (auto &i : nxt)
            q.push({sig, m[i->name], m[name]});
    }

    void print() {
        cout << "Broadcaster: " << name << endl;
        for (auto &i : nxt)
            cout << i->name << " ";
        cout << endl;
    }
};

struct Conjunction : Module {
    vector<bool> la;
    vector<int> pos;
    bool status;

    Conjunction(string name) : Module(name) {
        status = false;
    }

    void init(int n) {
        la.resize(n, 1);
    }

    void init() {
        la.assign(la.size(), 1);
        for (auto &i : pos)
            la[i] = false;
        status = false;
    }

    void trigger(bool sig, Module *from) {
        // cout << "trigger: " << name << " " << sig << endl;
        ++cnt[sig];
        la[m[from->name]] = sig;
        status = true;
        for (auto i : la)
            status &= i;
            
        for (auto &i : nxt)
            q.push({!status, m[i->name], m[name]});
    }

    void print() {
        cout << "Conjunction: " << name << " " << status << endl;
        for (auto &i : nxt)
            cout << i->name << " ";
        cout << endl;
        for (int i = 0; i < la.size(); ++i)
            if (!la[i])
                cout << i << " ";
        cout << endl;
    }
};


void init() {
    for (auto &i : a) {
        if (Flipflop* v = dynamic_cast<Flipflop*>(i))
            v->init();
        else if (Conjunction* v = dynamic_cast<Conjunction*>(i))
            v->init();
        else if (Broadcaster* v = dynamic_cast<Broadcaster*>(i))
            v->init();
    }
    cnt[0] = cnt[1] = 0;
}

void go(int n, int bpos) {
    init();
    while (n--) {
        q.push({false, bpos, bpos});
        while (!q.empty()) {
            auto [sig, pos, from] = q.front();
            q.pop();
            a[pos]->trigger(sig, a[from]);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    vector<string> tos;
    int n = 0, bpos = -1;
    while (getline(cin, s)) {
        string name = s.substr(0, s.find(' '));
        if (name[0] != 'b')
            name = name.substr(1);
        else
            bpos = n;
        
        m[name] = n++;
        if (s[0] == 'b') 
            a.push_back(new Broadcaster(name));
        else if (s[0] == '%')
            a.push_back(new Flipflop(name));
        else
            a.push_back(new Conjunction(name));

        s = s.substr(s.find('>') + 2);
        tos.push_back(s);
    }
    // cout << n << endl;
    for (Module* i : a) {
        if (Conjunction* v = dynamic_cast<Conjunction*>(i))
            v->init(n);
    }
    for (int i = 0; i < n; ++i) {
        string x = tos[i];
        int pos, cur = m[a[i]->name];
        while ((pos = x.find(',')) != string::npos) {
            string y = x.substr(0, pos);
            if (!m.count(y))
                m[y] = n++, a.push_back(new Module(y));
            a[i]->nxt.push_back(a[m[y]]);
            if (Conjunction* v = dynamic_cast<Conjunction*>(a[m[y]]))
                v->la[cur] = false, v->pos.push_back(cur);//, cout << cur << "->" << m[y] << endl;
            x = x.substr(pos + 2);
        }
        if (!m.count(x))
            m[x] = n++, a.push_back(new Module(x));
        a[i]->nxt.push_back(a[m[x]]);
        if (Conjunction* v = dynamic_cast<Conjunction*>(a[m[x]]))
            v->la[cur] = false, v->pos.push_back(cur);//, cout << cur << "->" << m[x] << endl;
    }
    // for (Module* i : a) {
    //     if (Conjunction* v = dynamic_cast<Conjunction*>(i))
    //         v->print();
    //     else if (Flipflop* v = dynamic_cast<Flipflop*>(i))
    //         v->print();
    //     else if (Broadcaster* v = dynamic_cast<Broadcaster*>(i))
    //         v->print();
    //     else 
    //         i->print();
    // }

    go(1000, bpos);
    cout << "task1: " << 1ll * cnt[0] * cnt[1] << endl;

    Conjunction* lst = dynamic_cast<Conjunction*>(a[m["zg"]]);
    vector<Conjunction*> b;
    for (int k : lst->pos) {
        Conjunction* v = dynamic_cast<Conjunction*>(a[k]);
        b.push_back(v);
    }

    int tot = 1000;
    vector<int> len(b.size(), 0);
    bool f = false;
    vector<int> t(n), cc(n);
    init();
    for (int i = 1; ; ++i) {
        q.push({false, bpos, bpos});
        while (!q.empty()) {
            auto [sig, pos, from] = q.front();
            if (!sig) {
                if (find(b.begin(), b.end(), a[pos]) != b.end() && cc[pos])
                    len[find(b.begin(), b.end(), a[pos]) - b.begin()] = i - t[pos];
                t[pos] = i;
                cc[pos]++;
            }
            q.pop();
            a[pos]->trigger(sig, a[from]);
        }
        f = true;
        for (int j = 0; j < b.size(); ++j)
            f &= len[j];
        if (f)
            break;
    }
    long long ans = 1;
    for (int i = 0; i < b.size(); ++i)
        ans = lcm(ans, len[i]);
    cout << "task2: " << ans << endl;

    for (auto &i : a)
        delete i;
    return 0;
}