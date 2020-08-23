/*
ID: axrdiv1
PROG: milk3
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<cstring>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int maxst = 21*21*21;
int vis[maxst];
int cap[3];
struct state {
    int cmt[3];
    state(int a=0, int b=0, int c=0) {
        cmt[0] = a;
        cmt[1] = b;
        cmt[2] = c;
    }
};
vector<int> ans;

queue<state> que;

void bfs() {
    while(!que.empty()) {
        state sp = que.front(); que.pop();
        if(sp.cmt[0] == 0) ans.push_back(sp.cmt[2]);
        // 倒水
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i == j) continue;
                // 从i出到j桶
                // 要求： 桶i里面有水，并且桶j还有空间
                state p = sp;
                if(p.cmt[i] > 0 && cap[j] > p.cmt[j]) {
                    int canmove = min(p.cmt[i], cap[j]-p.cmt[j]);
                    p.cmt[i] -= canmove;
                    p.cmt[j] += canmove;
                    // 如果这个状态没有访问过，就加入queue
                    int hash = p.cmt[0] * 21 * 21 + p.cmt[1] * 21 + p.cmt[2];
                    if(!vis[hash]) {
                        vis[hash] = 1;
                        que.push(p);
                    }
                }
            }
        }

    }
}
int main() {
    memset(vis, 0, sizeof(vis));
    ofstream fout("milk3.out");
    ifstream fin("milk3.in");
    fin >> cap[0] >> cap[1] >> cap[2];
    que.push(state(0, 0, cap[2]));
    vis[cap[2]] = 1;
    bfs();
    sort(ans.begin(), ans.end());
    for(int i = 0; i < ans.size()-1; i++) {
        fout << ans[i] << " ";
    }
    fout << ans[ans.size()-1] << endl;
    return 0;
}
