/*
ID: axrdiv1
PROG: wormhole
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
struct wormhole {
    int x, y, i;
    wormhole(int x=0, int y=0, int i=0): x(x), y(y), i(i) {};
    bool operator < (const wormhole& p) const {
        return y < p.y || (y == p.y && x < p.x);
    }
};
vector<wormhole> farm;
vector<int> pl;
int pair[20];

int n;

bool is_vaild(const vector<int>& pl) {
    for(int i = 0; i < pl.size(); i++){
        if(pl[i] == i) return false;
        if(pl[pl[i]] != i) return false;
    }
    return true;
}



bool is_circle(const vector<int>& pl) {
    for(int beg = 0; beg < pl.size(); beg++) {
        /* 
         * beg 是入口，进入以后从next点出来
         */
        int ext = pl[beg], cnt = pl.size();
        while(cnt--) {
            if(ext < pl.size()-1 && farm[ext].y == farm[ext+1].y) {
                if(ext+1 == beg) return true;
                ext = pl[ext+1];
            }
            else { break; }
        }
    }
    // 所有的点都不能走回路
    return false;
}

void dfs(vector<int>& pl, int d, int& cnt) {
    if(d == n) {
        if(is_circle(pl)) cnt++;
        return;
    }

    int fi = 0;
    while(pl[fi] != -1) {
        fi++;
    }
    for(int i = fi+1; i < n; i++) {
        if(pl[i] == -1) {
            pl[i] = fi; pl[fi] = i;
            dfs(pl, d+2, cnt);
            pl[i] = -1; pl[fi] = -1;
        }
    }
}

int main() {
    ofstream fout("wormhole.out");
    ifstream fin("wormhole.in");
    fin >> n;
    for(int i = 0; i < n; i++) {
        int x, y;
        fin >> x >> y;
        farm.push_back(wormhole(x, y, i));
        pl.push_back(i);
    }
    sort(farm.begin(), farm.end());     // 如果同一行右边还有Wormhole的话，那一定是相邻的下一个位置。

    int cnt = 0;
    
    fill(pl.begin(), pl.end(), -1);
    dfs(pl, 0, cnt);

    fout << cnt << endl;

    return 0;
}
