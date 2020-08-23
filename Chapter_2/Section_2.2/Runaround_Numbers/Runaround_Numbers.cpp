/*
ID: axrdiv1
PROG: runround
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<algorithm>
using namespace std;
typedef unsigned long ulong;

ulong M;
int nd;

int ndig(ulong m) {
    int cnt = 0;
    while(m) {
        cnt++; m /= 10;
    }
    return cnt;
}

int msum(ulong m) {
    int s = 0;
    while(m) {
        s += m % 10;
        m /= 10;
    }
    return s;
}

bool is_ident(ulong m) {
    int cnt = 0;
    while(m) {
        int idx = m % 10;
        if(idx == 0) return false;
        if(cnt & (1<<idx)) return false;
        cnt |= (1<<idx);
        m /= 10;
    }
    return true;
}

int get_num(ulong m, int n) {
    while(n--) {
        m /= 10;
    }
    return m%10;
}

bool is_round(ulong m) {
    int cnt = 0, idx = 0, tim = nd;
    do {
        tim--;
        int move = idx + nd - get_num(m, idx)%nd;
        move %= nd;
        if(idx == move || cnt & (1<<idx)) return false;
        cnt |= (1<<idx);
        idx = move;
    } while(idx);

    if(tim) return false;

    return true;
}


int main() {
    ofstream fout("runround.out");
    ifstream fin("runround.in");
    fin >> M;
    while(M++) {
        nd = ndig(M);
        if(is_ident(M) && is_round(M)) {
            fout << M <<endl;
            break;
        }
    }
    return 0;
}
