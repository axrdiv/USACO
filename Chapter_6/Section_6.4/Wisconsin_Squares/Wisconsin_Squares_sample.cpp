/*
TASK:wissqu
LANG:C++
*/
#include <cstdio>
#include <cstring>

using namespace std;

char matrix[4][5], path[16][10];
bool v[4][4], flag;
int ans, num[5] = {3, 3, 3, 4, 3};

bool judge(int x0, int y0, int x1, int y1, int k)
{
    for (int i = x0; i <= x1; ++i)
        for (int j = y0; j <= y1; ++j)
            if (i >= 0 && i < 4 && j >= 0 && j < 4 && matrix[i][j] == k + 'A') return false;
    return true;
}

void dfs(int dep)
{
    if (dep == 16)
    {
        if (flag)
        {
            for (int i = 0; i < 16; ++i) printf("%s\n", path[i]);
            flag = false;
        }
        ans++;
        return;
    }
    for (int u = 0; u < 5; ++u)
        if (num[u])
        {
            num[u]--;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    if (v[i][j] && judge(i-1, j-1, i+1, j+1, u))
                    {
                        v[i][j] = false;
                        if (flag)
                            sprintf(path[dep], "%c %d %d", u+'A', i+1, j+1);
                        char tmp = matrix[i][j];
                        matrix[i][j] = u + 'A';
                        dfs(dep + 1);
                        matrix[i][j] = tmp;
                        v[i][j] = true;
                    }
            num[u]++;
        }
}

int main()
{
    freopen("wissqu.in", "r", stdin);
    freopen("wissqu.out", "w", stdout);
    for (int i = 0; i < 4; ++i) scanf("%s", matrix[i]);
    memset(v, true, sizeof(v));
    memset(path, 0, sizeof(path));
    flag = true;
    dfs(0);
    printf("%d\n", ans);
    return 0;
}
