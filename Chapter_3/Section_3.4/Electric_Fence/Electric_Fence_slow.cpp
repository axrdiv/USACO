/*
ID: axrdiv1
PROG: fence9
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;

const double EPS = 1e-5;

ofstream fout("fence9.out");
ifstream fin("fence9.in");

int n, m, p;

struct vector2 {
    double x, y;
    vector2(double x, double y): x(x), y(y) {};
    vector2 operator- (const vector2& b) const {
        return vector2(x-b.x, y-b.y);
    }
    double xdot(const vector2& b) {
        return x*b.y-y*b.x;
    }
    double norm() {
        return sqrt(x*x+y*y);
    }
};

typedef vector2 point;

bool point_online(point& A, point& B, point& P) {
    return abs((P-A).xdot(B-A)) / (B-A).norm() < EPS;

}
bool is_sameside(point& A, point& B, point& C, point& D) {
    double a = (B-A).xdot(C-A);
    double b = (B-A).xdot(D-A);
    return a*b > 0;
}
int main() {
    fin >> n >> m >> p;
    point A(0, 0), B(n, m), C(p, 0);

    int lout = 0;
    for(int y = 0; y <= m; y++) {
        int x;
        for(x = 0; x <= n; x++) {
            point P(x, y);
            // cout << P.x << P.y << endl;
            if(point_online(A, B, P)) {
                lout++; break;
            }
            if(!is_sameside(A, B, C, P)) { lout++; }
            else break;
        }
    }
    int rout = 0;
    for(int y = 0; y <= m; y++) {
        int x;
        for(x = max(p, n); x >= min(p, n); x--) {
            point P(x, y);
            // cout << P.x << P.y << endl;
            if(point_online(B, C, P)) {
                rout++; break;
            }
            if(!is_sameside(B, C, A, P)) { rout++; }
            else break;
        }
    }
    fout << (max(p, n)+1) * m - lout - rout + 3 + (max(p, n) - p) << endl;
    cout << lout << " " << rout << endl;
    return 0;
}
