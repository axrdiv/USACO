/*
ID: axrdiv1
PROG: money
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn = 10000 + 10;

ifstream fin("money.in");
ofstream fout("money.out");

int V, N;
vector<int> coins;
LL dp[maxn];

int main() {
    fin >> V >> N;
    for(int i = 0; i < V; i++) {
        int tmp;
        fin >> tmp;
        coins.push_back(tmp);
    }
    sort(coins.begin(), coins.end());
    // initialize 
    dp[0] = 1;
    for(int i = 0; i < V; i++)
        for(int j = coins[i]; j <= N; j++)
            dp[j] += dp[j-coins[i]];

    fout << dp[N] << endl;
    return 0;
}
