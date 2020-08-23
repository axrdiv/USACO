/*
ID: axrdiv1
PROG: latin
LANG: C++
*/

#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

const int fact[] = {1, 1, 2, 6, 24, 120, 720};
const int MAXN = 10;

int N;
int id, cnt[MAXN], a[MAXN];
long long ans;
bool row[MAXN][MAXN], col[MAXN][MAXN], v[MAXN];

void find() {
    id = 2;
    int l, t;
    memset(v, 0, sizeof(v));
    for(int i = 1; i <= N; i++) {
        if(!v[i]) {
            t = i; l = 0;
            do {
                v[t] = true;
                t = a[t];
                l++;
            }while(!v[t]);
            if(l > id) {
                id = l;
            }
        }
    }
}

void dfs(int x, int y) {
    for(int i = 1; i <= N; i++) {
        if(row[x][i] && col[y][i]) {
            if(x == 2) {
                a[y] = i;
                if(y == N) {
                    find();
                    if(cnt[id] > 0) {
                        ans += cnt[id];
                        return;
                    }
                }
            }
            row[x][i] = false;
            col[y][i] = false;
            if(y == N) {
                if(x == N-1) {
                    cnt[id]++;
                    ans++;
                } else
                    dfs(x+1, 2);
            } else
                dfs(x, y+1);
            row[x][i] = true;
            col[y][i] = true;
        }
    }
}

int main() {
    freopen("latin.in", "r", stdin);
    freopen("latin.out", "w", stdout);
    scanf("%d", &N);
    if(N == 2) {
        ans = 1;
    } else {
        memset(row, true, sizeof(row));
        memset(col, true, sizeof(col));
        memset(cnt, 0, sizeof(cnt));
        for(int i = 2; i < N; i++) row[i][i] = false;
        for(int i = 1; i <= N; i++) col[i][i] = false;
        ans = 0;
        a[1] = 2;
        dfs(2, 2);
        ans *= fact[N-1];
    }
    printf("%lld\n", ans);
    return 0;
}
