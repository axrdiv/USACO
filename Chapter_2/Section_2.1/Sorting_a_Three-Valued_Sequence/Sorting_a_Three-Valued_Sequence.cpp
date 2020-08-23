/*
ID: axrdiv1
PROG: sort3
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;
const int maxn = 1000 + 10;

int n, list[maxn];
int cnt[3] = {0};
int ccnt[3][3] = {0};
int main() {
    ofstream fout("sort3.out");
    ifstream fin("sort3.in");
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> list[i];
        cnt[--list[i]]++;
    }
    for(int i = 0; i < n; i++) {
        int should;
        if(i < cnt[0]) should = 0;
        else if(i < cnt[0] + cnt[1]) should = 1;
        else should = 2;
        ccnt[should][list[i]]++;
    }
    int ret = 0, tmp;
    for(int i = 1; i < 3; i++) {
        for(int j = 0; j < i; j++) {
            tmp = min(ccnt[i][j], ccnt[j][i]);
            ccnt[i][j] -= tmp;
            ccnt[j][i] -= tmp;
            ret += tmp;
        }
    }
    ret += 2 * max(ccnt[1][0], ccnt[0][1]);

    fout << ret << endl;

    return 0;
}
