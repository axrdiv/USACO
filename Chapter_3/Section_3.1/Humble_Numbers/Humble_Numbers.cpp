/*
ID: axrdiv1
PROG: humble
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
const int maxn = 100000 + 5;
const int maxk = 100 + 5;

ofstream fout("humble.out");
ifstream fin("humble.in");
int d[maxn], prim[maxk], pptr[maxk];

int K, N;
int main() {
    fin >> K >> N;
    for(int i = 0; i < K; i++) {
        fin >> prim[i];
    }

    d[0] = 1;
    for(int i = 1; i <= N; i++) {
        int min = 2147483647;
        for(int j = 0; j < K; j++) {
            while(prim[j] * d[pptr[j]] <= d[i-1]) pptr[j]++;
            if(prim[j] * d[pptr[j]] < min) min = prim[j] * d[pptr[j]];
        }
        d[i] = min;
    }
    fout << d[N] << endl;
    return 0;
}
