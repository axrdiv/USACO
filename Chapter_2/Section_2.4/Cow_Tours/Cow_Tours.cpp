/*
ID: axrdiv1
PROG: cowtour
LANG: C++
*/

/*
Step 1. find connect component
Step 2. calculate point pairs distence
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<string>
using namespace std;

const int maxn = 150 + 5;
const double inf = 1000000;

ifstream fin("cowtour.in");
FILE* fout = fopen("cowtour.out", "w");

struct pos {
    int x, y;
    pos(int x=0, int y=0): x(x), y(y) {};
};
vector<pos> pastures;

struct heap_pos {
    int t;
    double d;
    heap_pos(int t=0, double d=0): t(t), d(d) {};
    bool operator< (const heap_pos& b) const {
        return d > b.d;
    }
};

double dist(int an,int bn) {
    pos& a = pastures[an];
    pos& b = pastures[bn];
    return sqrt((double)(a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int N, adj[maxn][maxn], vis[maxn], con[maxn];
double maxd[maxn], diam[maxn];


void dijk(int st) {
    memset(vis, 0, sizeof(vis));
    double d[maxn];
    fill(d, d+maxn, -1);
    priority_queue<heap_pos> que;
    que.push(heap_pos(st, 0));
    while(!que.empty()) {
        heap_pos p = que.top(); que.pop();
        if(vis[p.t]) continue;
        vis[p.t] = 1;
        d[p.t] = p.d;
        for(int i = 0; i < N; i++) {
            if(!vis[i] && con[i] == con[st] && adj[p.t][i]) {
                que.push(heap_pos(i, p.d+dist(p.t,i)));
            }
        }
    }

    for(int i = 0; i < N; i++) {
        if(d[i] > 0) maxd[st] = max(maxd[st], d[i]);
    }
}

void connect(int st, int C) {
    memset(vis, 0, sizeof(vis));
    queue<int> que;
    que.push(st);
    vis[0] = 1;
    int cnt = 0;
    while(!que.empty()) {
        cnt++;
        int t = que.front(); que.pop();
        con[t] = C;
        for(int i = 0; i < N; i++) {
            if(!vis[i] && adj[i][t]) {
                que.push(i);
                vis[i] = 1;
            }
        }
    }
}

int main() {
    int x, y;
    string line;
    fin >> N;
    for(int i = 0; i < N; i++) {
        fin >> x >> y;
        pastures.push_back(pos(x, y));
    }
    for(int i = 0; i < N; i++) {
        fin >> line;
        for(int j = 0; j < N; j++) {
            adj[i][j] = (line[j] == '1' ? 1 : 0);
        }
    }
    // find connect part
    fill(con, con+maxn, -1);
    int nCon = 0;
    for(int i = 0; i < N; i++) {
        if(con[i] == -1) {
            connect(i, nCon++);
        }
    }

    for(int i = 0; i < N; i++) { dijk(i); }


    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(con[i] != con[j]) continue;
            diam[i] = max(diam[i], maxd[j]);
        }
    }

    /*
    for(int i = 0; i < N; i++) {
        printf("%lf\t", diam[i]);
    }
    cout << endl;
    */

    double ret = inf;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(con[i] == con[j]) continue;
            ret = min(ret, max(max(diam[i], diam[j]), maxd[i]+maxd[j]+dist(i, j)));
        }
    }
    fprintf(fout, "%.6lf\n", ret);

    return 0;
}
