/*
ID: axrdiv1
PROG: betsy
LANG: C++
*/

// 搜索方法不足以解决 N=7;

#include<iostream>
#include<cstring>
#include<queue>
using namespace std;

const int MAXN = 9;
bool vis[MAXN][MAXN];
int link[MAXN][MAXN];
int ans, N;

const int dx[] = {0, 0, 1, -1};
const int dy[] = {-1, 1, 0, 0};

inline int state(int x, int y) {
    /* 0-normal; 1-must; 2-invalid; 3-vally
     */
    if(x == 1 && y == N) return 0;
    int cnt = 0;
    for(int d = 0; d < 4; d++) {
        if(vis[x+dx[d]][y+dy[d]]) cnt++;
    }
    if(cnt == 4) return 2;
    if(cnt == 3) return 1;

    if(cnt == 2) {
        if(vis[x + dx[0]][y + dy[0]] == vis[x - dx[0]][y - dy[0]])
            return 3;
    }
    return 0;
}

void dfs(int cur, int x, int y) {
    if(cur == N * N) {
        if(x == 1 && y == N)
            ans++;
        return;
    }

    int mustdir = -1;
    for(int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if(vis[nx][ny]) continue;
        if(state(nx, ny) == 1) {
            if(mustdir == -1) mustdir = d;
            else return;
        }
    }
    if(mustdir != -1) {
        int nx = x + dx[mustdir];
        int ny = y + dy[mustdir];
        vis[nx][ny] = 1;
        dfs(cur + 1, nx, ny);
        vis[nx][ny] = 0;
    }
    else {
        for(int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if(nx > 0 && nx <= N && ny > 0 && ny <= N) {
                if(vis[nx][ny]) continue;
                if(state(nx, ny) == 3) continue;
                vis[nx][ny] = 1;
                dfs(cur + 1, nx, ny);
                vis[nx][ny] = 0;
            }
        }
    }
}

int main() {
    freopen("betsy.in", "r", stdin);
    freopen("betsy.out", "w", stdout);
    scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        vis[0][i] = vis[i][0] = vis[N + 1][i] = vis[i][N + 1] = 1;
    }
    vis[1][1] = 1;
    dfs(1, 1, 1);
    printf("%d\n", ans);
    return 0;
}
