/*
ID: axrdiv1
PROG: fence
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<stack>
using namespace std;
const int maxn  = 500 + 5;

int fen[maxn][maxn];

ofstream fout("fence.out");
ifstream fin("fence.in");

int F;
stack<int> stk;
stack<int> ans;

void Euler(int st) {
    stk.push(st);
    while(!stk.empty()) {
        int t = stk.top();
        bool flag = 1;
        for(int i = 1; i < maxn; i++) {
            if(fen[t][i]) {
                fen[t][i]--; fen[i][t]--;
                stk.push(i);
                flag = 0;
                break;
            }
        }
        if(flag) {
            ans.push(t);
            stk.pop();
        }
    }
}
int main() {
    fin >> F;
    int a, b, st = maxn;
    for(int i = 0; i < F; i++) {
        fin >> a >> b;
        fen[a][b]++;
        fen[b][a]++;
    }
    for(int i = 1; i < maxn; i++) {
        int sum = 0;
        for(int j = 0; j < maxn; j++)
            sum += fen[i][j];
        if(sum) st = min(st, i);
        if(sum & 1) {
            st = i; break;
        }
    }
    Euler(st);
    while(!ans.empty()) {
        fout << ans.top() << endl;
        ans.pop();
    }


    return 0;
}
