/*
ID: axrdiv1
PROG: lamps
LANG: C++
*/

/*
 * B1: Change all their state
 * B2: Change the state of all the odd numbered lamps
 * B3: Change the state of all the even numbered lamps
 * B4: Change the state of the lamps whose number is of the form 3*k+1 (with k >= 0) i.e., 1,4,7,...
 */

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;
const int maxn = 100 + 10;

int N, C;
vector<int> pos, neg;
set<string> ans;

bool is_c(const int& butt) {
    int cnt = 0;
    for(int i = 0; i < 4; i++) if(butt & (1<<i)) cnt++;
    if(cnt > C) return false;
    if((cnt%2) != (C%2)) return false;
    return true;
}

void is_ident(const int& butt) {
    bool stat[maxn];
    memset(stat, 1, sizeof(stat));
    if(butt & 1) {
        for(int i = 0; i < N; i++) {
            stat[i] = !stat[i];
        }
    }
    if(butt & (1 << 1)) {
        for(int i = 0; i < N; i += 2) {
            stat[i] = !stat[i];
        }
    }
    if(butt & (1 << 2)) {
        for(int i = 1; i < N; i += 2) {
            stat[i] = !stat[i];
        }
    }
    if(butt & (1 << 3)) {
        for(int i = 0; i < N; i += 3) {
            stat[i] = !stat[i];
        }
    }

    if(pos.size()) {
        for(int i = 0; i < pos.size(); i++) {
            if(!stat[pos[i]-1]) return;
        }
    }
    if(neg.size()) {
        for(int i = 0; i < neg.size(); i++)
            if(stat[neg[i]-1]) return;
    }


    string ret;
    for(int i = 0; i < N; i++) {
        ret.push_back(stat[i]?'1':'0');
    }
    ans.insert(ret);
}

void dfs(int butt, int idx) {
    if(idx == 4) {
        if(is_c(butt)) {
            is_ident(butt);
        }
        return;
    }
    dfs(butt, idx+1);
    butt |= (1<<idx);
    dfs(butt, idx+1);
}
int main() {
    ofstream fout("lamps.out");
    ifstream fin("lamps.in");
    fin >> N >> C;
    int tmp;
    while((fin >> tmp) && tmp != -1) {
        pos.push_back(tmp);
    }
    while((fin >> tmp) && tmp != -1) {
        neg.push_back(tmp);
    }
    dfs(0, 0);
    if(ans.size())
        for(set<string>::iterator it = ans.begin(); it != ans.end(); it++)
            fout << *it << endl;
    else
        fout << "IMPOSSIBLE" << endl;

    return 0;
}
