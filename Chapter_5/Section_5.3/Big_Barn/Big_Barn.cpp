/*
ID: axrdiv1
PROG: bigbrn
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
using namespace std;

const int MAX_N = 1000 + 5; 

ofstream fout("bigbrn.out");
ifstream fin("bigbrn.in");
int N, T;

int dp[MAX_N][MAX_N];

void solve() {
    int ans = 0;
    for(int i = N-2; i >= 0; i--) {
        for(int j = N-2; j >= 0; j--) {
            if(dp[i][j]) {
                dp[i][j] = min(min(dp[i+1][j], dp[i][j+1]), dp[i+1][j+1]) + 1;
                ans = max(ans, dp[i][j]);
            }
        }
    }
    fout << ans << endl;
}

int main() {
    fin >> N >> T;
    fill(dp[0], dp[0]+MAX_N*MAX_N, 1);

    int tx, ty;
    for(int i = 0; i < T; i++) {
        fin >> tx >> ty;
        dp[--tx][--ty] = 0;
    }

    solve();

    return 0;
}
