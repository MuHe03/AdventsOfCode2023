#include <bits/stdc++.h>
#define sz(x) ((int) x.size())
using namespace std;


int dirx[] = {0, 1, 0, -1};
int diry[] = {1, 0, -1, 0};

typedef long long ll;

const ll eps = 1e-13;
struct Point {
    ll x, y;
    Point(ll x=0, ll y=0) : x(x), y(y) {}
};
typedef Point Vector;
Vector operator + (Vector a, Vector b) { return Vector(a.x + b.x, a.y + b.y); }
Vector operator - (Vector a, Vector b) { return Vector(a.x - b.x, a.y - b.y); }
Vector operator * (Vector a, ll p) { return Vector(a.x*p, a.y*p); }
Vector operator / (Vector a, ll p) { return Vector(a.x/p, a.y/p); }
bool operator < (const Point& a, const Point& b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}
int dcmp(ll x) {
    if (fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}
bool operator == (const Point& a, const Point& b) {
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}
ll Dot(Vector a, Vector b) { return a.x*b.x + a.y*b.y; }
ll Length(Vector a) { return sqrt(Dot(a, a)); }
ll Angle(Vector a, Vector b) { return acos(Dot(a,b) / Length(a) / Length(b)); }
ll Cross(Vector a, Vector b) { return a.x*b.y - a.y*b.x; }
ll Area2(Point a, Point b, Point c) { return Cross(b-a, c-a); }
Vector Rotate(Vector a, ll rad) { return Vector(a.x*cos(rad) - a.y*sin(rad), a.x*sin(rad)+a.y*cos(rad)); }
Vector Normal(Vector a) { ll L = Length(a); return Vector(-a.y/L, a.x/L); }


Point GetLineIntersection(Point p, Vector v, Point q, Vector w) {
    return p + v*(Cross(w, p-q) / Cross(v, w));
}

ll DistanceToLine(Point p, Point a, Point b) {
    Vector v1 = b-a, v2 = p-a;
    return fabs(Cross(v1, v2)) / Length(v1); // 不取绝对值是有向距离
}

ll DistanceToSegment(Point p, Point a, Point b) {
    if (a == b) return Length(p-a);
    Vector v1 = b-a, v2 = p-a, v3 = p-b;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1,v2)) / Length(v1);
}

Point GetLineProjection(Point p, Point a, Point b) {
    Vector v = b-a;
    return a+v*(Dot(v, p-a) / Dot(v, v));
}

bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2) { // 不包括端点,重合
    ll c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
           c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2) < 0 && dcmp(c3)*dcmp(c4) < 0;
}

bool OnSegment(Point p, Point a1, Point a2) { // 不包括端点
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

 
ll PolygonArea(vector<Point> &P) { // following untest
    ll area = 0;
    for (int i = 1;i < sz(P); ++i) {
        area += Cross(P[i]-P[0], P[(i+1)%sz(P)]-P[0]);
    }
    return abs(area/2); // directed without abs
}
 
int isPointInPolygon(Point p, vector<Point> &P) {
    int wn = 0;
    int n = sz(P);
    for (int i = 0;i < n; ++i) {
        if (OnSegment(p, P[i], P[(i+1)%n])) return -1; // on border
        int k = dcmp(Cross(P[(i+1)%n]-P[i], p-P[i]));
        int d1 = dcmp(P[i].y-p.y);
        int d2 = dcmp(P[(i+1)%n].y-p.y);
        if (k > 0 && d1 <= 0 && d2 > 0) wn++;
        if (k < 0 && d2 <= 0 && d1 > 0) wn--;
    }
    if (wn != 0) return 1; // inside
    return 0; // outside
}
 
// ball
ll torad(ll deg) {
    return deg/180 * acos(-1); 
}
 
// change latitude,langtitude(degree) to (x,y,z) 
void get_coord(ll R, ll lat, ll lng, ll &x, ll &y, ll &z) {
    lat = torad(lat);
    lng = torad(lng);
    x = R*cos(lat)*cos(lng);
    y = R*cos(lat)*sin(lng);
    z = R*sin(lat);
}

void task2(vector<tuple<int, int, string>> a) {
    vector<Point> p;
    ll cc = 0;
    Point cur = {0, 0};
    p.push_back(cur);
    for (auto [_, __, col]: a) {
        int dir = col[5] - '0';
        int len = stoi(col.substr(0, 5), 0, 16);
        cur = {cur.x + len * dirx[dir], cur.y + len * diry[dir]};
        cc += len;
        p.push_back(cur);
    }
    cout << "task2: " << PolygonArea(p) + cc / 2 + 1<< endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    string s;
    vector<tuple<int, int, string>> a;
    vector<Point> p;
    p.push_back({0, 0});
    ll mmmin = INT_MAX, mmmax = INT_MIN;
    ll cc = 0;
    while (getline(cin, s)) {
        int dir = -1, len = 0;
        if (s[0] == 'R')
            dir = 0;
        else if (s[0] == 'D')
            dir = 1;
        else if (s[0] == 'L')
            dir = 2;
        else 
            dir = 3;
        s = s.substr(2);
        len = stoi(s.substr(0, s.find(' ')));
        a.push_back({dir, len, s.substr(s.find('#') + 1, 6)});
        p.push_back({p.back().x + len * dirx[dir], p.back().y + len * diry[dir]});
        mmmin = min(mmmin, p.back().x), mmmax = max(mmmax, p.back().x);
        mmmin = min(mmmin, p.back().y), mmmax = max(mmmax, p.back().y);
        cc += len;
    }
    int n = mmmax - mmmin + 1;
    vector<vector<int>> b(n << 1, vector<int>(n << 1));
    for (int i = 1; i < p.size(); ++i) {
        auto [x, y] = p[i - 1];
        x -= mmmin, y -= mmmin;
        auto [dir, len, col] = a[i - 1];
        for (int k = 1; k <= len * 2; ++k)
            b[1 + x * 2 + k * dirx[dir]][1 + y * 2 + k * diry[dir]] = 1;
    }
    queue<pair<int, int>> q;
    q.push({n * 2 - 1, n * 2 - 1});
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (b[x][y])
            continue;
        b[x][y] = 2;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirx[i], ny = y + diry[i];
            if (nx < 0 || ny < 0 || nx >= 2 * n || ny >= 2 * n || b[nx][ny])
                continue;
            q.push({nx, ny});
        }
    }
    int cnt = 0;
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = 0; j < 2 * n; ++j)
            if (b[i][j] < 2 && i % 2 && j % 2)
                ++cnt;
    }
    p.pop_back();
    cout << "task1: " << cnt << endl;
    cout << "task1: " << PolygonArea(p) + cc / 2 + 1 << endl;

    task2(a);
    return 0;
}