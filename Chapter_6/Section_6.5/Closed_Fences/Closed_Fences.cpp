/*
ID: axrdiv1
PROG: fence4
LANG: C++
*/
#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

const int MAXN = 200 + 10;
int N;

struct Point{
    double x, y;
    Point() {}
    Point(double x, double y):x(x), y(y) {};
    Point operator-(Point p) {
        return Point(x-p.x, y-p.y);
    }
    Point operator+(Point p) {
        return Point(x+p.x, y+p.y);
    }
    Point operator*(double p) {
        return Point(x*p, y*p);
    }
    Point operator/(double p) {
        return Point(x/p, y/p);
    }
};

struct Line{
    Point p1;
    Point p2;
    Line() {}
    Line(Point p1, Point p2) : p1(p1), p2(p2) {}
};

vector<Point> vertice;
vector<Line> fence;
bool seeable[MAXN];
int ans;

typedef Point vec;
inline double Cross(vec A, vec B) {
    return A.x * B.y - A.y * B.x;
}

inline double Dot(vec A, vec B) {
    return A.x * B.x + A.y * B.y;
}
const double eps = 1e-8;

int sgn(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

// 点和直线的关系
int Point_line_relation(Point p, Line v) {
    int c = sgn(Cross(p - v.p1, p - v.p2));
    if(c < 0) return 1;             // 点在线左边
    if(c > 0) return 2;             // 点在线右边
    return 0;                       // 点在线上
}

bool Point_on_seg(Point p, Line v) {
    return sgn(Cross(p - v.p1, v.p2 - v.p1)) == 0 && sgn(Dot(p - v.p1, p - v.p2)) <= 0;
}

int Line_relation(Line v1, Line v2) {
    if(sgn(Cross(v1.p2 - v2.p1, v2.p2 - v2.p1)) == 0) {
        if(Point_line_relation(v1.p1, v2) == 0) return 1;
        else return 0;
    }
    return 2;
}

Point Cross_point(Line A, Line B) {
    double s1 = Cross(A.p2 - A.p1, B.p1 - A.p1);
    double s2 = Cross(A.p2 - A.p1, B.p2 - A.p1);
    return Point(B.p1.x * s2 - B.p2.x * s1, B.p1.y * s2 - B.p2.y * s1) / (s2 - s1);
}


bool conflict(Line e) {
    for(int i = 0; i < (int)fence.size(); i++) {
        Line& et = fence[i];
        if(Line_relation(e, et) == 0) continue;
        Point p = Cross_point(e, et);
        double m1 = (p.x - et.p1.x) / (et.p2.x - et.p1.x);
        double m2 = (p.x - e.p1.x) / (e.p2.x - e.p1.x);
        if(m1 < 1 && m1 > 0 && m2 < 1 && m2 > 0) return true;
    }
    return false;
}

Point obv;

bool can_see(Line& line, int index) {
    if(!sgn(line.p1.x - line.p2.x) && !sgn(line.p1.y - line.p2.y))
        return false;

    Line lline(obv, line.p1);
    Line rline(obv, line.p2);

    bool ok = 0;
    for(int i = 0; i < (int)fence.size(); i++) {
        if(i == index) continue;
        Point c1 = Cross_point(lline, fence[i]);
        bool t1 = Point_on_seg(c1, lline) && Point_on_seg(c1, fence[i]);

        Point c2 = Cross_point(rline, fence[i]);
        bool t2 = Point_on_seg(c2, rline) && Point_on_seg(c2, fence[i]);

        if(t1 && t2) return 0;
        ok |= t1 || t2;
    }
    if(!ok) return true;

    Point mid = (line.p1 + line.p2) / 2;
    Line ml(line.p1, mid);
    Line mr(mid, line.p2);
    if(can_see(ml, index)) return true;
    if(can_see(mr, index)) return true;
    return false;
}

int main() {
    freopen("fence4.in", "r", stdin);
    freopen("fence4.out", "w", stdout);
    cin >> N >> obv.x >> obv.y;
    for(int i = 0; i < N; i++) {
        double x, y;
        cin >> x >> y;
        vertice.push_back((Point){x, y});
    }

    for(int i = 0; i < N; i++) {
        Point p1 = vertice[i];
        Point p2 = vertice[(i + 1) % N];
        if(i == N - 1) swap(p1, p2);
        if(conflict((Line){p1, p2})) {
            cout << "NOFENCE" << endl;
            return 0;
        }
        fence.push_back((Line){p1, p2});
    }

    for(int i = 0; i < (int)fence.size(); i++) {
        if(can_see(fence[i], i)) {
            seeable[i] = 1;
            ans++;
        }

    }

    cout << ans << endl;
    for(int i = 0; i < N - 2; i++)
        if(seeable[i])
            cout << fence[i].p1.x << " " << fence[i].p1.y << " "
                << fence[i].p2.x << " " << fence[i].p2.y << endl;

    if(seeable[N - 1]) 
        cout << fence[N - 1].p1.x << " " << fence[N - 1].p1.y << " "
            << fence[N - 1].p2.x << " " << fence[N - 1].p2.y << endl;
    if(seeable[N-2]) 
        cout << fence[N - 2].p1.x << " " << fence[N - 2].p1.y << " "
            << fence[N - 2].p2.x << " " << fence[N - 2].p2.y << endl;

    return 0;
}
