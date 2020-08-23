/*
ID: axrdiv1
PROG: msquare
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<map>
#include<string>
#include<queue>
using namespace std;

const int maxn = 10000;
map<string, string> ops;
queue<string> que;

ofstream fout("msquare.out");
ifstream fin("msquare.in");

string begn = "12345678";
string obj;

string op(string sq, int i) {
    if(i == 0) {
        for(int i = 0; i < 4; i++) {
            swap(sq[i], sq[7-i]);
        }
    }
    else if(i == 1) {
        char tmp = sq[3];
        sq[3] = sq[2];
        sq[2] = sq[1];
        sq[1] = sq[0];
        sq[0] = tmp;

        tmp = sq[4];
        sq[4] = sq[5];
        sq[5] = sq[6];
        sq[6] = sq[7];
        sq[7] = tmp;
    }
    else if(i == 2) {
        char tmp = sq[1];
        sq[1] = sq[6];
        sq[6] = sq[5];
        sq[5] = sq[2];
        sq[2] = tmp;
    }
    return sq;
}
void bfs() {
    que.push(begn);
    ops[begn] = "";
    while(!que.empty()) {
        string st = que.front(); que.pop();
        if(st == obj) return;
        for(int i = 0; i < 3; i++) {
            string nst = op(st, i);
            if(!ops.count(nst)) {
                ops[nst] = ops[st] + (char)('A'+i);
                que.push(nst);
            }
        }
    }
}

int main() {
    char c;
    for(int i = 0; i < 8; i++) {
        fin >> c;
        obj.push_back(c);
    }
    bfs();
    fout << ops[obj].size() << endl << ops[obj] << endl;
    /*
    for(int i = 0; i < 3; i++)
        cout << op(obj, i) << endl;
    */

    return 0;
}
