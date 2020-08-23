/*
ID: axrdiv1
PROG: holstein
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<queue>
using namespace std;
const int maxv = 25 + 5;
const int maxg = 15 + 5;

int v, vit[maxv], g, gre[maxg][maxv];
int nnen[maxv] = {0};

struct stat {
    int en[maxv] = {0};
    int type, st, cnt;
    stat(int type, int st, int cnt): type(type), st(st), cnt(cnt) {}
};

queue<stat> Q;

bool is_enough(const stat& p) {
    for(int i = 0; i < v; i++) {
        if(p.en[i] < vit[i]) return false;
    }
    return true;
}

stat bfs() {
    Q.push(stat(0, 0, 0));
    while(!Q.empty()) {
        stat p = Q.front(); Q.pop();
        if(is_enough(p)) return p;
        for(int i = p.st; i < g; i++) {
            int ntype = p.type | (1 << i);
            stat np(ntype, i+1, p.cnt+1);
            for(int j = 0; j < v; j++)
                np.en[j] = p.en[j] + gre[i][j];
            Q.push(np);
        }
    }
    return stat(0, 0, 0);
}

int main() {
    ofstream fout("holstein.out");
    ifstream fin("holstein.in");
    fin >> v;
    for(int i = 0; i < v; i++)
        fin >> vit[i];
    fin >> g;
    for(int i = 0; i < g; i++) for(int j = 0; j < v; j++) {
        fin >> gre[i][j];
    }

    stat p = bfs();
    fout << p.cnt;
    for(int i = 0; i < g; i++) {
        if(p.type & (1<<i)) fout << " " << i+1;
    }
    fout << endl;

    return 0;
}
