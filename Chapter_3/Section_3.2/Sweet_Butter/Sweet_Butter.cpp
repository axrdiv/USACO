/*
ID: axrdiv1
PROG: butter
LANG: C++
*/
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 500 + 5;
const int maxp = 800 + 5;
const int maxdis = 9999999;

FILE* fout = fopen("butter.out", "w");
FILE* fin = fopen("butter.in", "r");

int cows[maxn], adj[maxp][maxp]; 

int N, P, C;

int main() {
    memset(adj, 0x3f3f, sizeof(adj));
    fscanf(fin, "%d%d%d", &N, &P, &C);
    int a, b, dd;
    for(int i = 0; i < N; i++) {
        fscanf(fin, "%d", &cows[i]);
    }

    for(int i = 0; i < C; i++) {
        fscanf(fin, "%d%d%d", &a, &b, &dd);
        adj[b][a] = adj[a][b] = dd;
        adj[a][a] = adj[b][b] = 0;
    }

    // Floyd
    for(int k = 1; k <= P; k++) {
        for(int i = 1; i <= P; i++) {
            for(int j = 1; j < i; j++) {
                if(adj[i][j] > adj[i][k] + adj[k][j]) {
                    adj[i][j] = adj[i][k] + adj[k][j];
                    adj[j][i] = adj[i][j];
                }
            }
        }
    }
    int ret = maxdis;
    for(int st = 1; st <= P; st++) {
        int tsum = 0;
        for(int c = 0; c < N; c++) {
            tsum += adj[st][cows[c]];
        }
        if(tsum < ret) ret = tsum;
    }

    fprintf(fout, "%d\n", ret);

    return 0;
}
