/*
ID: frontie1
TASK: betsy
LANG: C++
*/
#include <iostream>
#include <cstdio>

using namespace std;

int go_r[4] = {0, -1, 0, 1};
int go_c[4] = {1, 0, -1, 0};

int N;
bool visited[10][10] = {{0}};
int cnt = 0;

int state(int r, int c)//0-normal; 1-must; 2-invalid; 3-valley
{
    if(r == N && c == 1) return 0;
    int tem = 0;
    for(int i = 0; i < 4; ++i){
        if(visited[r+go_r[i]][c+go_c[i]]) tem++;
    }
    if(tem == 4) return 2;
    if(tem == 3) return 1;

    if(tem == 2){
        if(visited[r+go_r[0]][c+go_c[0]] == visited[r+go_r[2]][c+go_c[2]]){
            return 3;
        }
    }
    return 0;
}

void DFS(int dep, int r, int c)
{

    if(r == N && c == 1){
        if(dep == N*N-1) ++cnt;
        return;
    }
    if(dep == N*N-1) return;
    visited[r][c] = true;

    int must_direction = -1;
    int nxt_r, nxt_c;
    for(int i = 0; i < 4; ++i){
        nxt_r = r + go_r[i];
        nxt_c = c + go_c[i];
        if(visited[nxt_r][nxt_c]) continue;
        if(state(nxt_r, nxt_c) == 1){
            if(must_direction == -1) must_direction = i;
            else{
                visited[r][c] = false;
                return;
            }
        }
    }
    if(must_direction != -1){
        DFS(dep+1, r+go_r[must_direction], c+go_c[must_direction]);
    }
    else{
        for(int i = 0; i < 4; ++i){
            nxt_r = r + go_r[i];
            nxt_c = c + go_c[i];
            if(visited[nxt_r][nxt_c]) continue;
            if(state(nxt_r, nxt_c) == 3) continue;
            DFS(dep+1, nxt_r, nxt_c);
        }
    }
    visited[r][c] = false;
    return;
}

int main()
{
    freopen("betsy.in", "r", stdin);
    freopen("betsy.out", "w", stdout);

    cin >> N;

    for(int i = 0; i <= N+1; ++i){
        visited[i][0] = true;
        visited[i][N+1] = true;
        visited[0][i] = true;
        visited[N+1][i] = true;
    }

    DFS(0, 1, 1);

    cout << cnt << endl;

    return 0;
}
