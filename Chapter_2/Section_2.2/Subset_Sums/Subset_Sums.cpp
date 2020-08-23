/*
ID: axrdiv1
PROG: subset
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;
typedef long long LL;
const int maxd = 1600;
int N; 
LL d[41][1600];

void dp() {
    for(int i = 2; i <= N; i++) {
        for(int j = 0; j < maxd; j++) {
            if(j-i >= 0) d[i][j] += d[i-1][j-i];
            if(j+i < maxd) d[i][j] += d[i-1][j+i];
        }
    }
}
int main() {
    ofstream fout("subset.out");
    ifstream fin("subset.in");
    fin >> N;
    d[1][800-1] = 1;
    d[1][800+1] = 1;
    dp();
    fout << d[N][maxd/2] / 2 << endl;
    return 0;
}
