/*
ID: axrdiv1
PROG: agrinet
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<queue>
using namespace std;

const int maxn = 100 + 5;

ofstream fout("agrinet.out");
ifstream fin("agrinet.in");

int N, intree[maxn], dist[maxn][maxn];

struct node {
    int a, b, d;
    node(int a, int b, int d): a(a), b(b), d(d) {};
    bool operator< (const node& p) const {
        return d > p.d;
    }
};

priority_queue<node> que;

int construct() {
    int sumdis = 0, st = 0, cnt = 0;
    que.push(node(st, st, 0));
    while(cnt < N) {
        node tnode = que.top(); que.pop();
        if(intree[tnode.b]) continue;
        intree[tnode.b] = 1;
        sumdis += tnode.d; cnt++;
        for(int i = 0; i < N; i++) {
            if(!intree[i]) {
                que.push(node(tnode.b, i, dist[tnode.b][i]));
            }
        }
    }

    return sumdis;
}

int main() {
    fin >> N;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            fin >> dist[i][j];

    fout << construct() << endl;

    return 0;
}
