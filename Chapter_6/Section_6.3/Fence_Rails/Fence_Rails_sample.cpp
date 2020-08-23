/*
TASK:fence8
LANG:C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int n, r, wood[55], need[1024], sum[1024], ans, space, tot;

bool dfs(int dep, int pos)
{
    if (dep == 0) return true;
    if (space > tot - sum[ans]) return false;
    for (int i = pos; i <= n; ++i)
        if (wood[i] >= need[dep])
        {
            wood[i] -= need[dep];
            if (wood[i] < need[1]) space += wood[i];
            bool flag = false;
            if (need[dep] == need[dep - 1]) flag = dfs(dep - 1, i);
            else flag = dfs(dep - 1, 1);
            if (wood[i] < need[1]) space -= wood[i];
            wood[i] += need[dep];
            if (flag) return true;
        }
    return false;
}

int bs(int left, int right)
{
    while (left < right)
    {
        ans = (left + right) / 2 + 1;
        space = 0;
        if (dfs(ans, 1)) left = ans;
        else right = ans - 1;
    }
    return left;
}

bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    freopen("fence8.in", "r", stdin);
    freopen("fence8.out", "w", stdout);
    scanf("%d", &n);
    tot = 0;
    for (int i = 1; i <= n; ++i) scanf("%d", &wood[i]), tot += wood[i];
    sort(wood + 1, wood + n + 1, cmp);
    scanf("%d", &r);
    sum[0] = 0;
    for (int i = 1; i <= r; ++i) scanf("%d", &need[i]);
    sort(need + 1, need + r + 1);
    for (int i = 1; i <= r; ++i) sum[i] = sum[i - 1] + need[i];
    printf("%d\n", bs(0, r));
    return 0;
}
