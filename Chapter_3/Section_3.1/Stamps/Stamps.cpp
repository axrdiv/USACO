/*
ID: axrdiv1
PROG: stamps
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 200 * 10000 + 10;

ofstream fout("stamps.out");
ifstream fin("stamps.in");

vector<int> stamps;
int d[maxn];
int K, N;

int dp() {
    int can = 0;
    while(++can) {
        for(int i = 0; i < N; i++) {
            if(stamps[i] > can) break;
            d[can] = min(d[can], d[can-stamps[i]]+1);
        }
        if(d[can] > K) return can-1;
    }
    return 0;
}

int main() {
    int st;
    fin >> K >> N;
    for(int i = 0; i < N; i++) {
        fin >> st;
        stamps.push_back(st);
    }
    sort(stamps.begin(), stamps.end());

    fill(d, d+maxn, K+1);
    d[0] = 0;
    fout << dp() << endl;
    return 0;
}
