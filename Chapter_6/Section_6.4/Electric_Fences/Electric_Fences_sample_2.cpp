/*
TASK:fence3
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <iostream>
using namespace std;

int n;
int line[155][4];
double ansx, ansy, ansd;

double sqr(double x)
{
    return x * x;
}

double calc(double x, double y)
{
    double sum = 0;
    for (int i = 0; i < n; ++i)
    {
        double tmp = min(sqrt(sqr(line[i][0] - x) + sqr(line[i][1] - y)), sqrt(sqr(line[i][2] - x) + sqr(line[i][3] - y)));
        if (line[i][1] == line[i][3] && line[i][0] <= x && x <= line[i][2]) tmp = min(tmp, fabs(line[i][1] - y));
        if (line[i][0] == line[i][2] && line[i][1] <= y && y <= line[i][3]) tmp = min(tmp, fabs(line[i][0] - x));
        sum += tmp;
    }
    return sum;
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

int main()
{
    freopen("fence3.in", "r", stdin);
    freopen("fence3.out", "w", stdout);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d%d%d%d", &line[i][0], &line[i][1], &line[i][2], &line[i][3]);
    ansd = 0x7fffffff;
    thx(0, 100);
    printf("%.1lf %.1lf %.1lf\n", ansx, ansy, ansd);
    return 0;
}
