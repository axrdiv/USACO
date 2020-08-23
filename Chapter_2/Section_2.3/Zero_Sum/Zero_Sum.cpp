/*
ID: axrdiv1
PROG: zerosum
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;
ofstream fout("zerosum.out");
ifstream fin("zerosum.in");

const int maxn = 10;
int oper[maxn];
int N, cnt;

bool is_eq() {
    int s = 0;
    int lopt = 2, num = 0;
    for(int i = 1; i <= N; i++) {
        num = num * 10 + i;
        if(i == N || oper[i] > 1) {
            if(lopt == 2) s += num;
            if(lopt == 3) s -= num;
            num = 0; lopt = oper[i];
        }
    }
    return s == 0;
}

// 0: 没访问 1: 空格 2: 加号 3: 减号
void dfs(int d) {
    if(d == N) {
        if(is_eq()) {
            fout << "1";
            for(int i = 1; i < N; i++) {
                fout << ((oper[i] == 1) ? " " : ((oper[i] == 2) ? "+" : "-" )) << i+1;
            }
            fout << endl;
        }
        return;
    }
    for(int i = 1; i <= 3; i++) {
        oper[d] = i;
        dfs(d+1);
    }
}

int main() {
    fin >> N;
    dfs(1);
    return 0;
}
