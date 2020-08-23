/*
ID: axrdiv1
PROG: fence6
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int maxn = 100;
int adj[2][maxn][maxn];
int len[maxn], vis[maxn];

ofstream fout("fence6.out");
ifstream fin("fence6.in");

int N;

struct dis {
    int x, d, p;
    dis(int x, int d, int p): x(x), d(d), p(p) {}
    bool operator< (const dis& b) const {
        return d > b.d || (d == b.d && x > b.x);
    }
};

int dijk(int st, int mind) {
    memset(vis, 0, sizeof(vis));
    priority_queue<dis> que;

    for(int i = 0; i < maxn; i++) {
        if(adj[0][st][i])
            que.push(dis(i, len[i], st));
    }

    while(!que.empty()) {
        dis td = que.top(); que.pop();
        // cout << td.x+1 << " " << td.d << endl;
        if(td.d > mind) return mind;
        if(td.x == st && adj[1][td.x][td.p]) return td.d;
        if(vis[td.x]) continue;
        vis[td.x] = 1;

        int t = 0;
        for(int i = 0; i < maxn; i++)
            if(adj[0][td.x][td.p]) {
                t = 1; break;
            }

        for(int i = 0; i < maxn; i++) {
            if(adj[t][td.x][i] && !vis[i])
                que.push(dis(i, td.d+len[i], td.x));
        }
    }
    return mind;
}

int find_mind() {
    int mind = 100 * 255;
    for(int st = 0; st < maxn; st++)
        mind = dijk(st, mind);
    return mind;
}

int main() {
    fin >> N;
    for(int i = 0; i < N; i++) {
        int s, ls, n1s, n2s, t;
        fin >> s >> ls >> n1s >> n2s;
        len[s-1] = ls;
        for(int j = 0; j < n1s; j++) {
            fin >> t;
            adj[0][s-1][t-1] = 1;
        }
        for(int j = 0; j < n2s; j++) {
            fin >> t;
            adj[1][s-1][t-1] = 1;
        }
    }

    fout << find_mind() << endl;

    return 0;
}
