/*
ID: axrdiv1
PROG: spin
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

const int round = 360;
int overlap[round];

ofstream fout("spin.out");
ifstream fin("spin.in");

struct gap {
    int st, ex;
    gap(int st=0, int ex=0): st(st), ex(ex) {}
};

struct wheel {
    int sp, w;
    gap gs[5];
    wheel(int sp=0, int w=0): sp(sp), w(w) {}
};

wheel whs[5];

int solve() {
    const int maxn = round;
    for(int t = 0; t < maxn; t++) {
        memset(overlap, 0, sizeof(overlap));
        for(int i = 0; i < 5; i++) {
            int st = t * whs[i].sp;
            for(int j = 0; j < whs[i].w; j++) {
                for(int k = 0; k <= whs[i].gs[j].ex; k++) {
                    int now = (st+whs[i].gs[j].st + k) % 360;
                    overlap[now]++;
                    if(overlap[now] == 5) return t;
                }
            }
        }
    }
    return -1;
}

int main() {
    int sp, w;
    for(int i = 0; i < 5; i++) {
        fin >> sp >> w;
        whs[i] = wheel(sp, w);
        for(int j = 0; j < w; j++) {
            int st, ex;
            fin >> st >> ex;
            whs[i].gs[j] = gap(st, ex);
        }
    }

    int ret = solve();
    if(ret >= 0) fout << ret << endl;
    else fout << "none" << endl;

    return 0;
}
