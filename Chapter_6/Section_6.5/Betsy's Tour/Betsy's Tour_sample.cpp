/*
TASK:betsy
LANG:C++
*/
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int d[2][4] = {{-1, 0, 1, 0},
                     {0, -1, 0, 1}};

int n, f[10][10];
bool vis[10][10];

bool check(int x, int y)
{
    if (!vis[x-1][y] && !vis[x+1][y] && vis[x][y-1] && vis[x][y+1]) return true;
    if (!vis[x][y-1] && !vis[x][y+1] && vis[x-1][y] && vis[x+1][y]) return true;
    return false;
}

long long dfs(int x, int y, int dep)
{
    if (x == n && y == 1)
    {
        if (dep == n * n) return 1;
        return 0;
    }
    if (check(x, y)) return 0;
    int msc = 0, k;
    for (int i = 0; i < 4; ++i)
    {
        int tx = x + d[0][i], ty = y + d[1][i];
        if (vis[tx][ty])
        {
            f[tx][ty]--;
            if (f[tx][ty] == 1) msc++, k = i;
        }
    }
    vis[x][y] = false;
    long long res = 0;
    if (msc <= 1)
    {
        if (msc == 0)
            for (int i = 0; i < 4; ++i)
            {
                int tx = x + d[0][i], ty = y + d[1][i];
                if (vis[tx][ty]) res += dfs(tx, ty, dep + 1);
            }
        else res = dfs(x+d[0][k], y+d[1][k], dep+1);
    }
    for (int i = 0; i < 4; ++i)
    {
        int tx = x + d[0][i], ty = y + d[1][i];
        if (vis[tx][ty]) f[tx][ty]++;
    }
    vis[x][y] = true;
    return res;
}

int main()
{
    scanf("%d", &n);
    memset(vis, true, sizeof(vis));
    for (int i = 0; i <= n; ++i)
        vis[0][i] = vis[i][0] = vis[n+1][i] = vis[i][n+1] = false;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            f[i][j] = 4;
    for (int i = 1; i <= n; ++i) f[i][1] = f[1][i] = f[i][n] = f[n][i] = 3;
    f[n][1] = 10;
    f[1][1] = f[1][n] = f[n][n] = 2;
    cout << dfs(1, 1, 1) << endl;
    return 0;
}
