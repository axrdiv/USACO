/*
ID: axrdiv1
PROG: holstein
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;
const int maxv = 25 + 5;
const int maxg = 15 + 5;

int v, vit[maxv], g, gre[maxg][maxv];
int type;
int en[maxv] = {0};

bool is_enough() {
    for(int i = 0; i < v; i++) {
        if(en[i] < vit[i]) return false;
    }
    return true;
}

bool dfs(int st, int d) {
    if(d == 0) 
        return is_enough();

    for(int i = st; i < g; i++) {
        if(type & (1<<i)) continue;
        type |= (1 << i);
        for(int j = 0; j < v; j++)
            en[j] += gre[i][j];
        // cout << type;
        if(dfs(st+1, d-1)) return true;
        type &= ~(1 << i);
        for(int j = 0; j < v; j++)
            en[j] -= gre[i][j];
        // cout << " " << type << endl;
    }
    return false;
}

int dfsid() {
    for(int s = 1; s <= g; s++) {
        if(dfs(0, s)) return s;
    }
    return g+1;
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

    fout << dfsid();
    for(int i = 0; i < g; i++) {
        if(type & (1<<i)) fout << " " << i+1;
    }
    fout << endl;

    return 0;
}
