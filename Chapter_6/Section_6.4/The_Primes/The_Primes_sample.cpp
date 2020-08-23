/*
TASK:prime3
LANG:C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>
#define REP(i,st,ed) for ((i) = (st); (i) < (ed); ++(i))

using namespace std;

struct Ans
{
    int matrix[5][5];
    
    Ans operator = (Ans &rhs)
    {
        memcpy(matrix, rhs.matrix, sizeof(rhs.matrix));
        return *this;
    }
    
    bool operator < (const Ans &rhs) const
    {
        for (int i = 0; i < 5; ++i)
            for (int j = 0; j < 5; ++j)
                if (matrix[i][j] < rhs.matrix[i][j]) return true;
                else if (matrix[i][j] > rhs.matrix[i][j]) return false;
        return false;
    }
    
}ans[1000], tmp;
int anslen;

const int MAXP = 100000;
int p[10000], np, sumallr[5], sumallc[5], sumalld, sum;
bool v[MAXP * 10];

bool check(int x)
{
    int s = 0;
    while (x) s += x % 10, x /= 10;
    return s == sum;
}

void filtrate()
{
    memset(v, true, sizeof(v));
    for (int i = 2; i < MAXP; ++i)
        for (int j = 2; i * j < MAXP; ++j)
            v[i * j] = false;
    np = 0;
    for (int i = 10000; i < MAXP; ++i)
        if (v[i] && check(i)) p[np++] = i;
}

bool judge(int x, int y)
{
    if (sumallr[x] + tmp.matrix[x][y] > sum) return false;
    if (sumallc[y] + tmp.matrix[x][y] > sum) return false;
    if (4 - x == y && sumalld + tmp.matrix[x][y] > sum) return false;
    return true;
}

void adds(int x, int y, int d)
{
    sumallr[x] += tmp.matrix[x][y] * d;
    sumallc[y] += tmp.matrix[x][y] * d;
    if (4 - x == y) sumalld += tmp.matrix[x][y] * d;
}

int trans(int d, int m)
{
    if (m == 1) return tmp.matrix[d][0] * 10000 
                        + tmp.matrix[d][1] * 1000
                        + tmp.matrix[d][2] * 100
                        + tmp.matrix[d][3] * 10
                        + tmp.matrix[d][4];
    else if (m == 2) return tmp.matrix[0][d] * 10000
                            + tmp.matrix[1][d] * 1000
                            + tmp.matrix[2][d] * 100
                            + tmp.matrix[3][d] * 10
                            + tmp.matrix[4][d];
    else if (m == 3) return tmp.matrix[4][0] * 10000
                            + tmp.matrix[3][1] * 1000
                            + tmp.matrix[2][2] * 100
                            + tmp.matrix[1][3] * 10
                            + tmp.matrix[0][4];
}

bool condit(int x)
{
    return x >= 0 && x <= 9;
}

int main()
{
    freopen("prime3.in", "r", stdin);
    freopen("prime3.out", "w", stdout);
    scanf("%d%d", &sum, &tmp.matrix[0][0]);
    filtrate();
    memset(sumallr, 0, sizeof(sumallr));
    memset(sumallc, 0, sizeof(sumallc));
    sumalld = 0;
    anslen = 0;
    for (int i = 0; i < np; ++i)
    {
        if (p[i] * 10 / MAXP != tmp.matrix[0][0]) continue;
        int k = p[i];
        for (int j = 4; j >= 0; --j)
        {
            tmp.matrix[j][j] = k % 10;
            sumallr[j] = sumallc[j] = k % 10;
            k /= 10;
        }
        sumalld = p[i] % 1000 / 100;
        REP(tmp.matrix[0][4], 1, 10)
        {
            if (tmp.matrix[0][4] % 2 == 0 || tmp.matrix[0][4] == 5) continue;
            if (!judge(0, 4)) break;
            adds(0, 4, 1);
            REP(tmp.matrix[1][3], 0, 10)
            {
                if (!judge(1, 3)) break;
                adds(1, 3, 1);
                REP(tmp.matrix[4][0], 1, 10)
                {
                    if (tmp.matrix[4][0] % 2 == 0 || tmp.matrix[4][0] == 5) continue;
                    if (!judge(4, 0)) break;
                    tmp.matrix[3][1] = sum - sumalld - tmp.matrix[4][0];
                    if (!condit(tmp.matrix[3][1]) || !judge(3, 1)) continue;
                    if (!v[trans(0, 3)]) continue;
                    adds(3, 1, 1);
                    adds(4, 0, 1);
                    REP(tmp.matrix[1][4], 1, 10)
                    {
                        if (tmp.matrix[1][4] % 2 == 0 || tmp.matrix[1][4] == 5) continue;
                        if (!judge(1, 4)) break;
                        adds(1, 4, 1);
                        REP(tmp.matrix[2][4], 1, 10)
                        {
                            if (tmp.matrix[2][4] % 2 == 0 || tmp.matrix[2][4] == 5) continue;
                            if (!judge(2, 4)) break;
                            tmp.matrix[3][4] = sum - sumallc[4] - tmp.matrix[2][4];
                            if (!condit(tmp.matrix[3][4]) || !judge(3, 4)) continue;
                            if (!v[trans(4, 2)]) continue;
                            adds(3, 4, 1);
                            adds(2, 4, 1);
                            REP(tmp.matrix[4][3], 1, 10)
                            {
                                if (tmp.matrix[4][3] % 2 == 0 || tmp.matrix[4][3] == 5) continue;
                                if (!judge(4, 3)) break;
                                adds(4, 3, 1);
                                REP(tmp.matrix[0][3], 1, 10)
                                {
                                    if (!judge(0, 3)) break;
                                    tmp.matrix[2][3] = sum - sumallc[3] - tmp.matrix[0][3];
                                    if (!condit(tmp.matrix[2][3]) || !judge(2, 3)) continue;
                                    if (!v[trans(3, 2)]) continue;
                                    adds(0, 3, 1);
                                    adds(2, 3, 1);
                                    REP(tmp.matrix[4][2], 1, 10)
                                    {
                                        if (tmp.matrix[4][2] % 2 == 0 || tmp.matrix[4][2] == 5) continue;
                                        if (!judge(4, 2)) break;
                                        adds(4, 2, 1);
                                        REP(tmp.matrix[3][2], 0, 10)
                                        {
                                            if (!judge(3, 2)) break;
                                            adds(3, 2, 1);
                                            REP(tmp.matrix[0][2], 1, 10)
                                            {
                                                if (!judge(0, 2)) break;
                                                tmp.matrix[1][2] = sum - sumallc[2] - tmp.matrix[0][2];
                                                if (!condit(tmp.matrix[1][2]) || !judge(1, 2) || !v[trans(2, 2)]) continue;
                                                tmp.matrix[0][1] = sum - sumallr[0] - tmp.matrix[0][2];
                                                if (tmp.matrix[0][1] == 0) continue;
                                                if (!condit(tmp.matrix[0][1]) || !judge(0, 1) || !v[trans(0, 1)]) continue;
                                                tmp.matrix[4][1] = sum - sumallr[4];
                                                if (!condit(tmp.matrix[4][1]) || !judge(4, 1) || !v[trans(4, 1)]) continue;
                                                tmp.matrix[2][1] = sum - sumallc[1] - tmp.matrix[0][1] - tmp.matrix[4][1];
                                                if (!condit(tmp.matrix[2][1]) || !judge(2, 1) || !v[trans(1, 2)]) continue;
                                                tmp.matrix[1][0] = sum - sumallr[1] - tmp.matrix[1][2];
                                                if (tmp.matrix[1][0] == 0) continue;
                                                if (!condit(tmp.matrix[1][0]) || !judge(1, 0) || !v[trans(1, 1)]) continue;
                                                tmp.matrix[2][0] = sum - sumallr[2] - tmp.matrix[2][1];
                                                if (tmp.matrix[2][0] == 0) continue;
                                                if (!condit(tmp.matrix[2][0]) || !judge(2, 0) || !v[trans(2, 1)]) continue;
                                                if (sumallc[0] + tmp.matrix[1][0] + tmp.matrix[2][0] != sumallr[3]) continue;
                                                tmp.matrix[3][0] = sum - sumallr[3];
                                                if (tmp.matrix[3][0] == 0) continue;
                                                if (!condit(tmp.matrix[3][0]) || !v[trans(0, 2)] || !v[trans(3, 1)]) continue;
                                                ans[anslen++] = tmp;
                                            }
                                            adds(3, 2, -1);
                                        }
                                        adds(4, 2, -1);
                                    }
                                    adds(0, 3, -1);
                                    adds(2, 3, -1);
                                }
                                adds(4, 3, -1);
                            }
                            adds(3, 4, -1);
                            adds(2, 4, -1);
                        }
                        adds(1, 4, -1);
                    }
                    adds(4, 0, -1);
                    adds(3, 1, -1);
                }
                adds(1, 3, -1);
            }
            adds(0, 4, -1);
        }
    }
    sort(ans, ans + anslen);
    for (int k = 0; k < anslen; ++k)
    {
        if (k != 0) printf("\n");
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
                printf("%d", ans[k].matrix[i][j]);
            printf("\n");
        }
    }
    return 0;
}