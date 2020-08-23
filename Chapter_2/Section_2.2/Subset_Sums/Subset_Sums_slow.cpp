/*
ID: axrdiv1
PROG: subset
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;
typedef long long LL;

int n;

bool is_eq(LL& stat) {
    int suml = 0, sumr = 0;
    for(int i = 0; i < n; i++) {
        if(stat & (1<<i)) suml += i+1;
        else sumr += i+1;
    }
    return suml == sumr;
}

void dfs(LL stat, int idx, int& cnt) {
    if(idx == n) {
        if(is_eq(stat)) cnt++;
        return;
    }
    dfs(stat, idx+1, cnt);
    stat = stat | (1 << idx);
    dfs(stat, idx+1, cnt);
}

int main() {
    ofstream fout("subset.out");
    ifstream fin("subset.in");
    fin >> n;
    LL begin = 0;
    int cnt = 0;
    dfs(begin+1, 1, cnt);
    cout << cnt << endl;
    return 0;
}
