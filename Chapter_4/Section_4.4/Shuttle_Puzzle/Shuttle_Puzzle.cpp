/*
ID: axrdiv1
PROG: shuttle
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<set>
#include<string>
using namespace std;
const int MAXN = 30;
const int MAXO = 2000;

// 0 hole; 1 white; 2 black;
int board[MAXN];
int oper[MAXO];

set<string> vis;

ofstream fout("shuttle.out");
ifstream fin("shuttle.in");
int N;

bool test() {
    for(int i = 1; i <= N; i++) {
        if(board[i] != 2) return false;
    }
    if(board[N+1] != 0) return false;
    for(int i = N+2; i <= 2*N+1; i++) {
        if(board[i] != 1) return false;
    }
    return true;
}

bool dfsid(int d, int hole, const int& m) {
    if(d == m) {
        return test();
    }

    if(hole >= 3 && board[hole-2] == 1 && board[hole-1] != board[hole-2]) {
        board[hole] = board[hole-2]; board[hole-2] = 0;
        oper[d] = hole-2;
        if(dfsid(d+1, hole-2, m)) return true;
        board[hole-2] = board[hole]; board[hole] = 0;
    }
    if(hole >= 2 && board[hole-1] == 1) {
        board[hole] = board[hole-1]; board[hole-1] = 0;
        oper[d] = hole-1;
        if(dfsid(d+1, hole-1, m)) return true;
        board[hole-1] = board[hole]; board[hole] = 0;
    }
    if(hole <= 2*N && board[hole+1] == 2) {
        board[hole] = board[hole+1]; board[hole+1] = 0;
        oper[d] = hole+1;
        if(dfsid(d+1, hole+1, m)) return true;
        board[hole+1] = board[hole]; board[hole] = 0;
    }
    if(hole <= 2*N-1 && board[hole+2] == 2 && board[hole+1] != board[hole+2]) {
        board[hole] = board[hole+2]; board[hole+2] = 0;
        oper[d] = hole+2;
        if(dfsid(d+1, hole+2, m)) return true;
        board[hole+2] = board[hole]; board[hole] = 0;
    }
    return false;
}

int main() {
    fin >> N;

    for(int m = 1; m <= MAXO; m++) {

        for(int i = 1; i <= N; i++) board[i] = 1;
        board[N+1] = 0;
        for(int i = N+2; i <= 2*N+1; i++) board[i] = 2;

        if(dfsid(0, N+1, m)) {
            for(int i = 0; i < m; i++) {
                if(i && i % 20 == 0) fout << endl;
                else if(i % 20) fout << " ";
                fout << oper[i];
            }
            fout << endl;
            break;
        }
    }

    return 0;
}
