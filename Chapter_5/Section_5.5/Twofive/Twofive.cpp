/*
ID: axrdiv1
PROG: twofive
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;

ofstream fout("twofive.out");
ifstream fin("twofive.in");

char C;
int N;
bool vis[26];
int dp[6][6][6][6][6];
int maxr[5], maxc[5];
int len[5];
char line[30];

int count(int a, int b, int c, int d, int e, int k) {
    int &ans = dp[a][b][c][d][e];
    if(ans) return ans;
    if(vis[k]) return count(a, b, c, d, e, k + 1);

    if(a < 5 && k > maxr[0] && k > maxc[a]) ans += count(a + 1, b, c, d, e, k + 1);
    if(b < a && k > maxr[1] && k > maxc[b]) ans += count(a, b + 1, c, d, e, k + 1);
    if(c < b && k > maxr[2] && k > maxc[c]) ans += count(a, b, c + 1, d, e, k + 1);
    if(d < c && k > maxr[3] && k > maxc[d]) ans += count(a, b, c, d + 1, e, k + 1);
    if(e < d && k > maxr[4] && k > maxc[e]) ans += count(a, b, c, d, e + 1, k + 1);

    return ans;
}

int main() {
    fin >> C;
    if(C == 'N') fin >> N;
    else fin >> line;

    memset(maxr, -1, sizeof(maxr));
    memset(maxc, -1, sizeof(maxc));

    for(int i = 0; i < 5; i++) {
        for(int j = 0; j < 5; j++) {
            len[i]++;
            if(C == 'N') {
                for(int k = 0; k < 25; k++) {
                    if(!vis[k] && k > maxr[i] && k > maxc[j]) {
                        maxr[i] = maxc[j] = k;
                        vis[k] = true;
                        memset(dp, 0, sizeof(dp));
                        dp[5][5][5][5][5] = 1;
                        int cnt = count(len[0], len[1], len[2], len[3], len[4], 0);
                        if(cnt >= N) {
                            line[i * 5 + j] = 'A' + k;
                            break;
                        } else {
                            N -= cnt;
                            vis[k] = false;
                        }
                    }
                }
            }
            else {
                for(int k = 0; k < line[i * 5 + j] - 'A'; k++) {
                    if(!vis[k] && k > maxr[i] && k > maxc[j]) {
                        vis[k] = true;
                        maxr[i] = maxc[j] = k;
                        memset(dp, 0, sizeof(dp));
                        dp[5][5][5][5][5] = 1;
                        N += count(len[0], len[1], len[2], len[3], len[4], 0);
                        vis[k] = false;
                    }
                }
                vis[line[i * 5 + j] - 'A'] = true;
            }
        }
    }
    if(C == 'N')
        fout << line << endl;
    else
        fout << N + 1 << endl;
    return 0;
}
