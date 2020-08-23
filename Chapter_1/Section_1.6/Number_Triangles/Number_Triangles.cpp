/*
ID: axrdiv1
PROG: numtri
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxr = 1000 + 10;
int dp[2][maxr];

int R;
int main() {
    memset(dp, 0, sizeof(dp));
    ofstream fout("numtri.out");
    ifstream fin("numtri.in");
    fin >> R >> dp[0][1];
    int t = 1;
    for(int ln = 2; ln <= R; ln++) {
        for(int i = 1; i <= ln; i++) {
            int tmp;
            fin >> tmp;
            dp[t][i] = max(tmp+dp[t^1][i], tmp+dp[t^1][i-1]);
        }
        t ^= 1;
    }
    int ans = 0;
    for(int i = 0; i <= R+1; i++) { ans = max(ans, dp[t^1][i]); }
    fout << ans << endl;
    return 0;
}
