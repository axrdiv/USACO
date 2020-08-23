/*
ID: axrdiv1
PROG: job
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<queue>
using namespace std;
const int maxn = 1000 + 5;

ofstream fout("job.out");
ifstream fin("job.in");

struct machine {
    int t, a;
    machine(int t=0, int a=0): t(t), a(a) {};
    bool operator< (const machine& b) const {
        return t > b.t || (t == b.t && a > b.a);
    }
};

priority_queue<machine> que;

int N, M1, M2;
int t[maxn];

int main() {
    int ansa, ansb;
    fin >> N >> M1 >> M2;
    for(int i = 0; i < M1; i++) {
        machine m;
        fin >> m.a;
        m.t = m.a;
        que.push(m);
    }

    for(int ti = 0; ti < N; ti++) {
        machine tm = que.top(); que.pop();
        t[ti] = tm.t;
        tm.t += tm.a;
        que.push(tm);
    }
    ansa = t[N-1];

    // clear priority queue
    while(!que.empty()) que.pop();

    for(int i = 0; i < M2; i++) {
        machine m;
        fin >> m.a;
        m.t = m.a;
        que.push(m);
    }

    ansb = 0;
    for(int ti = N-1; ti >= 0 ; ti--) {
        machine m = que.top(); que.pop();
        ansb = max(ansb, t[ti]+m.t);
        m.t += m.a;
        que.push(m);
    }

    fout << ansa << " " << ansb << endl;
    return 0;
}
