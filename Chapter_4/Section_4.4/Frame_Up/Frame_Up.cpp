/*
ID: axrdiv1
PROG: frameup
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<cstring>
using namespace std;
const int MAX = 30 + 3;
const int MAXN = 26 + 3;

char frame[MAX][MAX];
int relation[MAXN][MAXN];
int alph[MAXN];                 // record 1 to nf
char malph[MAXN];               // from 1 to nf
char output[MAXN];
int noverlap[MAXN];
int vis[MAXN];
vector<string> ans;

ofstream fout("frameup.out");
ifstream fin("frameup.in");

int H, W, nf = 0;
struct state {
    int vis[MAXN];
    int overlap[MAXN];
    int n;
    string s;
    state() {
        memset(vis, 0, sizeof(vis));
        memset(overlap, 0, sizeof(overlap));
        n = 0;
    }
    state operator= (const state& b) {
        n = b.n;
        memcpy(vis, b.vis, sizeof(b.vis));
        memcpy(overlap, b.overlap, sizeof(b.overlap));
        s = b.s;
        return *this;
    }
};

struct fr {
    int u = MAX,
        d = -1,
        l = MAX,
        r = -1;
};

fr record[MAXN];                // from 1 to nf

int main() {
    fin >> H >> W;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            fin >> frame[i][j];
            char& c = frame[i][j];
            if(c != '.' && !alph[c-'A']) {
                nf++;
                alph[c-'A'] = nf;
                malph[nf] = c;
            }
        }
    }

    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            if(frame[i][j] != '.') {
                fr& nf = record[alph[frame[i][j] - 'A']];
                nf.u = min(nf.u, i);
                nf.d = max(nf.d, i);
                nf.l = min(nf.l, j);
                nf.r = max(nf.r, j);
            }
        }
    }

#ifdef DEBUG
    cout << " ";
    for(int j = 0; j < W; j++)
        cout << j;
    cout << endl;
    for(int i = 0; i < H; i++) {
        cout << i;
        for(int j = 0; j < W; j++) {
            cout << frame[i][j];
        }
        cout << endl;
    }

    cout << endl;
    for(int i = 1; i <= nf; i++) {
        cout << malph[i] << " "
            << record[i].u << " "
            << record[i].d << " "
            << record[i].l << " "
            << record[i].r << endl;
    }
#endif
    for(int idx = 1; idx <= nf; idx++) {
        fr& f = record[idx];
        for(int i = f.l; i <= f.r; i++) {
            if(frame[f.u][i] != '.' && frame[f.u][i] != malph[idx]) {
                relation[idx][alph[frame[f.u][i]-'A']] = 1;
            }
            if(frame[f.d][i] != '.' && frame[f.d][i] != malph[idx]) {
                relation[idx][alph[frame[f.d][i]-'A']] = 1;
            }
        }
        for(int i = f.u; i <= f.d; i++) {
            if(frame[i][f.l] != '.' && frame[i][f.l] != malph[idx]) {
                relation[idx][alph[frame[i][f.l]-'A']] = 1;
            }
            if(frame[i][f.r] != '.' && frame[i][f.r] != malph[idx]) {
                relation[idx][alph[frame[i][f.r]-'A']] = 1;
            }
        }
        for(int i = 1; i <= nf; i++)
            noverlap[idx] += relation[idx][i];
#ifdef DEBUG
        cout << noverlap[idx] << endl;
#endif
    }

    /*
    // prototype
    for(int i = nf-1; i >= 0; i--) {
        for(int idx = 1; idx <= nf; idx++) {
            if(!vis[idx] && noverlap[idx] <= 0) {
                output[i] =  malph[idx];
                vis[idx] = 1;
                for(int j = 1; j <= nf; j++)
                    noverlap[j] -= relation[j][idx];
                break;
            }
        }
    }
    fout << output << endl;
    */
    state init;
    memcpy(init.overlap, noverlap, sizeof(noverlap));
    queue<state> que;
    que.push(init);

    while(!que.empty()) {
        state st = que.front(); que.pop();
        if(st.n == nf) {
            ans.push_back(st.s);
        }
        for(int idx = 1; idx <= nf; idx++) {
            if(!st.vis[idx] && st.overlap[idx] == 0) {
                state nst = st;
                nst.s = malph[idx] + nst.s;
                nst.vis[idx] = 1;
                for(int j = 1; j <= nf; j++)
                    nst.overlap[j] -= relation[j][idx];
                nst.n++;
                que.push(nst);
            }
        }
    }

    sort(ans.begin(), ans.end());
    for(int i = 0; i < (int)ans.size(); i++)
        fout << ans[i] << endl;

    return 0;
}
