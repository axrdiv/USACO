/*
ID: axrdiv1
PROG: fracdec
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;
const int maxn = 100000*10+10;

ofstream fout("fracdec.out");
ifstream fin("fracdec.in");
int N, D, vis[maxn];
vector<int> dig;
char line[maxn];

int divi(int n, int d) {
    int cnt = 1;
    while(n > 0) {
        if(vis[n]) return vis[n];
        vis[n] = cnt++;
        dig.push_back(n/d);
        // cout << n/d << endl;
        n = n-(n/d)*d;
        n = n * 10;
    }
    return 0;
}

int main() {
    fin >> N >> D;
    string ans;
    sprintf(line, "%d.", N/D);
    ans += line;
    int cnt = divi((N-(N/D)*D)*10, D);
    for(int i = 0; i < (int)dig.size(); i++) {
        if(i == cnt-1) ans += "(";
        sprintf(line, "%d", dig[i]);
        ans += line;
    }
    if(cnt) ans += ")";
    if(!dig.size()) ans += "0";

    // print '\n' per 76 character
    int nchar = 0;
    for(int i = 0; i < ans.size(); i++) {
        fout << ans[i];
        if(++nchar % 76 == 0) fout << endl;
    }
    if(ans.size() % 76 != 0) fout << endl;
    return 0;
}
