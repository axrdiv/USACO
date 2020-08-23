/*
 * Tarjan算法
 * 求出数组c[]，其中c[x]表示x所在的强连通分量的编号。
 * 另外，它还求出了vector数组scc，scc[i]记录了编号为i的强连通分量中的所有节点。
 * 整张图共有cnt个强连通分量。
 */
#include<iostream>
#include<vector>
using namespace std;

const int N = 100000 + 10, M = 100000 + 10;
int ver[M], Next[M], head[N], dfn[N], low[N];
int stack[N], ins[N], c[N];
vector<int> scc[N];
int n, m, tot, num, top, cnt;

void add(int x, int y) {
    ver[++tot] = y, Next[tot] = head[x], head[x] = tot;
}

void tarjan(int x) {
    dfn[x] = low[x] = ++num;
    stack[++top] = x, ins[x] = 1;
    for(int i = head[x]; i; i = Next[i]) {
        if(!dfn[ver[i]]) {
            tarjan(ver[i]);
            low[x] = min(low[x], low[ver[i]]);
        }
        else if(ins[ver[i]])
            low[x] = min(low[x], dfn[ver[i]]);
    }
    if(dfn[x] == low[x]) {
        cnt++; int y;
        do {
            y = stack[top--], ins[y] = 0;
            c[y] = cnt, scc[cnt].push_back(y);
        }while(x != y);
    }
}

int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
    }
    return 0;
}
