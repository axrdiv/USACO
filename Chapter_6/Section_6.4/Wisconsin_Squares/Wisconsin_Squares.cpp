/*
ID: axrdiv1
PROG: wissqu
LANG: C++
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

char matrix[8][8];
bool vis[4][4], flag;
char path[16][10];
int ans, num[5] = {3, 3, 3, 4, 3};

bool judge(int x0, int y0, int x1, int y1, int k) {
    for(int i = x0; i <= x1; i++)
        for(int j = y0; j <= y1; j++)
            if(i >= 0 && i < 4 && j >= 0 && j < 4 && matrix[i][j] == k + 'A') return false;
    return true;
}

void dfs(int dep) {
    if(dep == 16) {
        if(flag) {
            for(int i = 0; i < 16; i++) printf("%s\n", path[i]);
            flag = false;
        }
        ans++;
        return;
    }
    for(int u = 0; u < 5; u++)
        if(num[u]) {
            num[u]--;
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++)
                    if(!vis[i][j] && judge(i-1, j-1, i+1, j+1, u)) {
                        vis[i][j] = true;
                        if(flag) {
                            path[dep][0] = u + 'A';
                            path[dep][1] = ' ';
                            path[dep][2] = i + '0' + 1;
                            path[dep][3] = ' ';
                            path[dep][4] = j + '0' + 1;
                        }
                        char tmp = matrix[i][j];
                        matrix[i][j] = u + 'A';
                        dfs(dep + 1);
                        matrix[i][j] = tmp;
                        vis[i][j] = false;
                    }
            num[u]++;
        }
}

int main() {
    freopen("wissqu.in", "r", stdin);
    freopen("wissqu.out", "w", stdout);
    for(int i = 0; i < 4; i++) scanf("%s", matrix[i]);
    memset(vis, 0, sizeof(vis));
    memset(path, 0, sizeof(path));
    flag = true;
    dfs(0);
    printf("%d\n", ans);
    return 0;
}
