/*
ID: axrdiv1
PROG: nuggets
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;
const int maxn = 10 + 3;
const int maxtry = 256*256 - 2*256 + 5;

ofstream fout("nuggets.out");
ifstream fin("nuggets.in");

int N, packages[maxn];
int d[maxtry];

int main() {
    fin >> N;
    for(int i = 0; i < N; i++) {
        fin >> packages[i];
        d[packages[i]] = 1;
    }

    int maxrt = 0;
    for(int i = 0; i < maxtry; i++) {
        for(int j = 0; j < N; j++) {
            if(i >= packages[j] && d[i-packages[j]]) {
                d[i] = 1;
                break;
            }
        }
        if(d[i] == 0) maxrt = i;
    }
    if(maxrt > 65024) maxrt = 0;
    fout << maxrt << endl;
    return 0;
}
