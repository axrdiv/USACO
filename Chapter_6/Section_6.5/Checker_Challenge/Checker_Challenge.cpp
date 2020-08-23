/*
ID: axrdiv1
LANG: C++
PROG: checker
*/

#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAXN = 15;
int ans, N;
int fthree[5][MAXN];
bool vis[3][MAXN * 2];

inline bool bigger(int cur) {
    for(int i = 0; i < N; i++)
        if(fthree[cur][i] != fthree[4][i])
            return fthree[cur][i] > fthree[4][i];
    return false;
}

void dfs(int cur) {
    if(cur == N) {
        ans++;

        for(int i = 2; i >= 0; i--) {
            if(bigger(i)) {
                for(int j = 0; j < N; j++) {
                    fthree[i + 1][j] = fthree[i][j];
                    fthree[i][j] = fthree[4][j];
                }
            }
            else break;
        }

        return;
    }

    for(int i = 0; i < N; i++) {
        if(vis[0][i] || vis[1][cur + i] || vis[2][N + i - cur])
            continue;

        vis[0][i] = vis[1][cur + i] = vis[2][N + i - cur] = 1;
        fthree[4][cur] = 1 + i;
        dfs(cur + 1);
        vis[0][i] = vis[1][cur + i] = vis[2][N + i - cur] = 0;
    }
}

void solve() {
    memset(fthree[0], 0x7f, sizeof(int) * 4 * MAXN);
    dfs(0);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < N; j++)
            printf("%d%c", fthree[i][j], (j == N - 1 ? '\n' : ' '));

    printf("%d\n", ans);
}

int main() {
    freopen("checker.in", "r", stdin);
    freopen("checker.out", "w", stdout);
    scanf("%d", &N);
    solve();
    return 0;
}
