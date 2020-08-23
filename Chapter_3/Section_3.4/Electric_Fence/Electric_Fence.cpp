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
    int last = 0;
    for(int y = 0; y <= m; y++) {
        int x;
        lout += last;
        for(x = last; x <= n; x++) {
            point P(x, y);
            // cout << P.x << P.y << endl;
            if(point_online(A, B, P)) {
                lout++;
                last = x;
                break;
            }
            if(!is_sameside(A, B, C, P)) { lout++; }
            else {
                last = x-1;
                break;
            }
        }
    }
    int rout = 0;
    if(B.x > C.x) {
        last = max(p, n);
        for(int y = m; y >= 0; y--) {
            int x;
            rout += max(p, n) - last;
            for(x = last; x >= min(p, n); x--) {
                point P(x, y);
                if(point_online(B, C, P)) {
                    rout++;
                    last = x;
                    break;
                }
                if(!is_sameside(B, C, A, P)) { rout++; }
                else {
                    last = x+1;
                    break;
                }
            }
        }
    }
    else {
        last = max(p, n);
        for(int y = 0; y <= m; y++) {
            int x;
            rout += max(p, n) - last;
            for(x = last; x >= min(p, n); x--) {
                point P(x, y);
                // cout << P.x << P.y << endl;
                if(point_online(B, C, P)) {
                    rout++;
                    last = x;
                    break;
                }
                if(!is_sameside(B, C, A, P)) { rout++; }
                else {
                    last = x+1;
                    break;
                }
            }
        }
    }
    fout << (max(p, n)+1) * m - lout - rout + 3 + (max(p, n) - p) << endl;
    // cout << lout << " " << rout << " " << (max(p, n)+1) * m << endl;
    return 0;
}
