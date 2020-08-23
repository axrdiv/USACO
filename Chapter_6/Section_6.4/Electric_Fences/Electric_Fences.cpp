/*
ID: axrdiv1
PROG: fence3
LANG: C++
*/

#include<iostream>
#include<cstdio>
#include<vector>
#include<cmath>
using namespace std;
int N;
int fence[155][4];
double ansx, ansy, ansd;

double PointToSegDist(double x, double y, double x1, double y1, double x2, double y2)
{
    double cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
    if (cross <= 0) return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));

    double d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
    if (cross >= d2) return sqrt((x - x2) * (x - x2) + (y - y2) * (y - y2));
    double r = cross / d2;
    double px = x1 + (x2 - x1) * r;
    double py = y1 + (y2 - y1) * r;
    return sqrt((x - px) * (x - px) + (py - y) * (py - y));
}

double calc(double x, double y) {
    double ans = 0;
    for(int i = 0; i < N; i++) {
        int *p = fence[i];
        ans += PointToSegDist(x, y, p[0], p[1], p[2], p[3]);
    }
    return ans;
}

double thy(double x)
{
    double l = 0, r = 100;
    while (r - l >= 0.01)
    {
        double mid = l + (r - l) / 3;
        double midmid = l + (r - l) / 3 * 2;
        double tmp1 = calc(x, mid), tmp2 = calc(x, midmid);
        if (tmp1 < tmp2) r = midmid;
        else l = mid;
    }
    double tmpd = calc(x, l);
    if (ansd > tmpd)
    {
        ansd = tmpd;
        ansx = x;
        ansy = l;
    }
    return tmpd;
}

void thx(double l, double r)
{

    while (r - l >= 0.01)
    {
        double mid = l + (r - l) / 3;
        double midmid = l + (r - l) / 3 * 2;
        double tmp1 = thy(mid), tmp2 = thy(midmid);
        if (tmp1 < tmp2) r = midmid;
        else l = mid;
    }
}

int main() {
    freopen("fence3.in", "r", stdin);
    freopen("fence3.out", "w", stdout);
    cin >> N;
    for(int i = 0; i < N; i++) {
        int *p = fence[i];
        cin >> p[0] >> p[1] >> p[2] >> p[3];
    }

    ansd = 0x7fffffff;
    thx(0, 100);
    printf("%.1f %.1f %.1f\n", ansx, ansy, ansd);
    return 0;
}
