/*
ID: axrdiv1
PROG: tour
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
using namespace std;
const int MAX_N = 100 + 5;

ofstream fout("tour.out");
ifstream fin("tour.in");
int N, V;

map<string, int> city;
vector<int> G[MAX_N];

int dp[MAX_N][MAX_N];

void solve() {
    dp[1][1] = 1;
    for(int c1 = 0; c1 < N; c1++) {
        for(int c2 = c1 + 1; c2 <= N; c2++) {
            for(int i = 0; i < (int)G[c2].size(); i++) {
                int k = G[c2][i];
                if(dp[c1][k]) {
                    dp[c1][c2] = max(dp[c1][c2], dp[c1][k] + 1);
                    dp[c2][c1] = max(dp[c1][c2], dp[c2][c1]);
                }
            }
        }
    }

    /*
    for(int i = 1; i <= N; i++) {
        for(int j = 1; j <= N; j++) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    */

    int ans = 1;
    for(int i = 0; i < (int)G[N].size(); i++) {
        ans = max(ans, dp[G[N][i]][N]);
    }
    fout << ans << endl;
}

int main() {
    fin >> N >> V;
    string s;
    for(int i = 1; i <= N; i++) {
        fin >> s;
        city[s] = i;
    }

    string s1, s2;
    for(int i = 1; i <= V; i++) {
        fin >> s1 >> s2;
        int c1 = city[s1], c2 = city[s2];
        G[c1].push_back(c2);
        G[c2].push_back(c1);
    }

    solve();

    return 0;
}
