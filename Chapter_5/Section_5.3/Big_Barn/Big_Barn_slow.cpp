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

bool dp[2][MAX_N][MAX_N];

int solve() {
    int mxl; 
    bool ans = 0;
    for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
        ans |= dp[0][i][j];

    for(mxl = 1; ans; mxl++) {
        ans = 0;
        // cout << mxl << endl;
        for(int i = 0; i < N-mxl; i++) {
            for(int j = 0; j < N-mxl; j++) {
                dp[mxl&1][i][j] = dp[(mxl+1)&1][i][j] && dp[(mxl+1)&1][i+1][j] && dp[(mxl+1)&1][i][j+1] && dp[(mxl+1)&1][i+1][j+1];
                ans |= dp[mxl&1][i][j];
                // cout << dp[mxl&1][i][j];
            }
            // cout << endl;
        }
        // cout << endl;
    }
    return mxl-1;
}

int main() {
    fin >> N >> T;
    fill(dp[0][0], dp[0][0]+MAX_N*MAX_N, true);

    int tx, ty;
    for(int i = 0; i < T; i++) {
        fin >> tx >> ty;
        dp[0][--tx][--ty] = false;
    }
    fout << solve() << endl;
    return 0;
}
