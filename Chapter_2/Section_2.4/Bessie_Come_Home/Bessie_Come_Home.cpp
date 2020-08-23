/*
ID: axrdiv1
PROG: comehome
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

const int maxn = 2*26 + 4;

ofstream fout("comehome.out");
ifstream fin("comehome.in");

int path[maxn][maxn];
int vis[maxn];
int P, d;
char from, to;

struct heap_pos {
    int t, d;
    heap_pos(int t=0, int d=0): t(t), d(d) {};
    bool operator< (const heap_pos& b) const {
        return d > b.d;
    }
};

heap_pos dijk() {
    int st = 25+26;
    heap_pos p;
    priority_queue<heap_pos> que;
    que.push(heap_pos(st, 0));
    while(!que.empty()) {
        p = que.top(); que.pop();
        if(vis[p.t]) continue;
        vis[p.t] = 1;
        if(p.t > 25 && p.t != 25+26) return p;
        for(int i = 0; i < maxn; i++) {
            if(!vis[i] && path[p.t][i]) {
                que.push(heap_pos(i, p.d+path[p.t][i]));
            }
        }
    }
    return p;
}

int main() {
    fin >> P;
    for(int i = 0; i < P; i++) {
        fin >> from >> to >> d;
        // 'a'-'z''A'-'Z'
        int ifrom, ito;
        ifrom = (isupper(from) ? from-'A'+26 : from-'a');
        ito = (isupper(to) ? to-'A'+26 : to-'a');
        if(!path[ifrom][ito]) {
            path[ifrom][ito] = d;
            path[ito][ifrom] = d;
        } else {
            path[ifrom][ito] = min(path[ifrom][ito], d);
            path[ito][ifrom] = min(path[ito][ifrom], d);
        }
    }

    heap_pos p = dijk();
    fout << (char)(p.t-26+'A') << " " << p.d << endl;
    return 0;
}
