/*
ID: axrdiv1
PROG: butter
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<algorithm>
#include<cstring>
using namespace std;

const int maxn = 500 + 5;
const int maxp = 800 + 5;
const int maxdis = 9999999;

ofstream fout("butter.out");
ifstream fin("butter.in");

int cows[maxn], d[maxp], adj[maxp][maxp]; 
int vis[maxp], is_cows[maxp];
int ret = maxdis;

int N, P, C;

void dijk(int st) {
    memset(vis, 0, sizeof(vis));
    vis[st] = 1;
    for(int i = 1; i <= P; i++) {
        d[i] = adj[st][i];
    }

    int idx;
    for(int tt = 2; tt <= P; tt++) {
        int mind = maxdis;
        for(int i = 1; i <= P; i++)
            if(!vis[i] && mind > d[i])
                mind = d[i], idx = i;

        vis[idx] = 1;

        for(int i = 1; i <= P; i++) {
            if(!vis[i] && d[idx] + adj[idx][i] < d[i])
                d[i] = d[idx]+adj[idx][i];
        }
    }
}


int main() {
    memset(adj, 0x3f3f, sizeof(adj));
    fin >> N >> P >> C;
    int a, b, dd;
    for(int i = 0; i < N; i++) {
        fin >> cows[i];
    }

    for(int i = 0; i < C; i++) {
        fin >> a >> b >> dd;
        adj[b][a] = adj[a][b] = dd;
    }

    for(int i = 1; i <= P; i++)
        adj[i][i] = 0;

    for(int st = 1; st <= P; st++) {
        dijk(st);
        int tsum = 0;
        for(int c = 0; c < N; c++) {
            tsum += d[cows[c]];
        }
        ret = min(ret, tsum);
    }

    fout << ret << endl;

    return 0;
}
