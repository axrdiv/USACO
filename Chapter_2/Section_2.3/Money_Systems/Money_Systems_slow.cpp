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

const int maxn = 10000 + 10;

ifstream fin("money.in");
ofstream fout("money.out");

int V, N;
vector<int> coins;
long long cnt;

void dfs(int s, int up) {
    if(s < 0) return;
    if(s == 0) {
        cnt++;
        return;
    }
    for(int i = coins.size()-1; i >= 0; i--) {
        if(coins[i] > up || coins[i] > s) continue;
        dfs(s-coins[i], coins[i]);
    }
}
int main() {
    fin >> V >> N;
    for(int i = 0; i < V; i++) {
        int tmp;
        fin >> tmp;
        coins.push_back(tmp);
    }
    sort(coins.begin(), coins.end());
    dfs(N, coins.back());
    fout << cnt << endl;
    return 0;
}
