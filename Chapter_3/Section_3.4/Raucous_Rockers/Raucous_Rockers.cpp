/*
ID: axrdiv1
PROG: rockers
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

const int maxt = 20 + 3;
const int maxm = 20 + 3;
const int maxn = 20 + 3;

int d[2][maxn][maxt];

int dur[maxn];

ofstream fout("rockers.out");
ifstream fin("rockers.in");

int N, T, M;

void dp() {
    for(int m = 1; m <= M; m++) {
        for(int n = 1; n <= N; n++) {
            for(int t = T; t >= 0; t--) {
                int& tmp = d[m&1][n][t];
                tmp = max(d[m&1][n-1][t], d[!(m&1)][n-1][T]);
                // use old disk
                if(t >= dur[n])
                    tmp = max(tmp, d[m&1][n-1][t-dur[n]]+1);

                // use new
                tmp = max(tmp, d[!(m&1)][n-1][T]+(t>=dur[n]));
            }
        }
    }
}

int main() {
    fin >> N >> T >> M;

    for(int i = 1; i <= N; i++)
        fin >> dur[i];

    dp();

    fout << d[M&1][N][T] << endl;

    return 0;
}
