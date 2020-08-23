/*
ID: axrdiv1
PROG: clocks
LANG: C++
*/

#include<cstdio>
#include<cstring>
using namespace std;

int used[10];

const int a[9][9]= {
    {1,1,0,1,1,0,0,0,0},
    {1,1,1,0,0,0,0,0,0},
    {0,1,1,0,1,1,0,0,0},
    {1,0,0,1,0,0,1,0,0},
    {0,1,0,1,1,1,0,1,0},
    {0,0,1,0,0,1,0,0,1},
    {0,0,0,1,1,0,1,1,0},
    {0,0,0,0,0,0,1,1,1},
    {0,0,0,0,1,1,0,1,1}};

int clock[10];
int ans[30], nop = 0;

bool check() {
    for(int i = 0; i < 9; i++)
        if(clock[i]) return false;
    return true;
}

void oper(int op) {
    for(int i = 0; i < 9; i++) {
        clock[i] = (clock[i] + a[op][i]*3) % 12;
    }
    ans[nop++] = op;
}
void unoper(int op) {
    for(int i = 0; i < 9; i++) {
        clock[i] = (12 + clock[i] - a[op][i]*3) % 12;
    }
    nop--;
}

bool dfs(int idx, int dep) {
    if(dep == 0) {
        if(check())
            return true;
        else
            return false;
    }
    for(int i = idx; i < 9; i++) {
        if(used[i]) {
            used[i]--;
            oper(i);
            if(dfs(i, dep-1))
                return true;
            unoper(i);
            used[i]++;
        }
    }
    return false;
}

void solve() {
    for(int i = 0; i < 10; i++) used[i] = 3;
    for(int dep = 0; dep < 28; dep++)
        if(dfs(0, dep)) {
            for(int i = 0; i < nop; i++)
                printf("%s%d", (i ? " " : ""), ans[i] + 1);
            printf("\n");
            return;
        }
}

int main() {
    freopen("clocks.in", "r", stdin);
    freopen("clocks.out", "w", stdout);
    for(int i = 0; i < 9; i++) {
        scanf("%d", &clock[i]);
        clock[i] %= 12;
    }
    solve();

    return 0;
}
