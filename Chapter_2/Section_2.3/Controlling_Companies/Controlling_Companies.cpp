/*
ID: axrdiv1
PROG: concom
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
const int maxn = 100 + 5;

// d(i,j) company i holds how many shares of company j;
// d(i,j) 公司i控制公司j的股份
// dfs暴力搜索
int d[maxn][maxn];
bool vis[maxn];
int cnt[maxn];
int N, comcnt = 1;
int comap[maxn], icomap[maxn];

ofstream fout("concom.out");
ifstream fin("concom.in");

void dfs(int it) {
    vis[it] = 1;
    for(int ij = 1; ij < maxn; ij++) {
        cnt[ij] += d[it][ij];
        if(!vis[ij] && cnt[ij] >= 50) {
            dfs(ij);
        }
    }
}

int main() {
    fin >> N;
    int it, jt, pt;
    for(int i = 0; i < N; i++) {
        fin >> it >> jt >> pt;
        /*
        if(!comap[it]) {
            comap[it] = comcnt;
            icomap[comcnt++] = it;
        }
        if(!comap[jt]) {
            comap[jt] = comcnt;
            icomap[comcnt++] = jt;
        }
        d[comap[it]][comap[jt]] = pt;
        */
        d[it][jt] = pt;
    }

    for(int it = 1; it < maxn; it++) {
        memset(vis, 0, sizeof(vis));
        memset(cnt, 0, sizeof(cnt));
        dfs(it);
        for(int ij = 1; ij < maxn; ij++) {
            if(it == ij) continue;
            // if(cnt[ij] >= 50) fout << icomap[it] << " " << icomap[ij] << endl;
            if(cnt[ij] >= 50) fout << it << " " << ij << endl;
        }
    }


    return 0;
}
