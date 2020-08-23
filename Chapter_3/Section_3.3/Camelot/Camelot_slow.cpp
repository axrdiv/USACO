/*
ID: axrdiv1
PROG: camelot
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int maxr = 30 + 3;

int board[maxr*maxr][maxr][maxr];
int vis[maxr][maxr];

const int dr[2][8] = {{1, 0, -1, 1, -1, 1, 0, -1}, {2, 1, -1, -2, -2, -1, 1, 2}};
const int dc[2][8] = {{-1, -1, -1, 0, 0, 1, 1, 1}, {-1, -2, -2, -1, 1, 2, 2, 1}};


ofstream fout("camelot.out");
ifstream fin("camelot.in");
int R, C;

struct pos {
    int r, c;
    pos(int r, int c): r(r), c(c) {}
    bool exist() {
        return r >= 0 && r < R && c >= 0 && c < C;
    }

    pos next(const int* ddr,const int* ddc, int d) {
        pos np(r, c);
        np.r += ddr[d];
        np.c += ddc[d];
        return np;
    }
    int idx() {
        return r * maxr + c;
    }
};
vector<pos> chess;
queue<pair<pos, int> > que;

void bfs(pos pst, int st) {
    memset(vis, 0, sizeof(vis));

    que.push(make_pair(pst, 0));
    vis[pst.r][pst.c] = 1;

    while(!que.empty()) {
        pos tp = que.front().first; 
        int d = que.front().second;
        que.pop();

        board[st][tp.r][tp.c] = d;

        for(int i = 0; i < 8; i++) {
            pos np = tp.next(dr[st>0], dc[st>0], i);
            if(np.exist() && !vis[np.r][np.c]) {
                vis[np.r][np.c] = 1;
                que.push(make_pair(np, d+1));
            }
        }
    }
}

int main() {
    fin >> R >> C;
    memset(board, 0x3f3f, sizeof(board));

    char c; int r;
    for(int i = 1; fin >> c >> r; i++) {
        chess.push_back(pos(r-1, c-'A'));
        // board[c-'A'][r-1] = i;
    }

    /*
    for(int st = 0; st < (int)chess.size(); st++) {
        bfs(st);
    }
    */

    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            pos np(r, c);
            bfs(np, np.idx());
        }
    }

    cout << "=======" << endl;
    /*
    for(int st = 0; st < (int)chess.size(); st++) {
        for(int r = 0; r < R; r++) {
            for(int c = 0; c < C; c++)
                cout << board[st][r][c] << " ";
            cout << endl;
        }
        cout << "-----" << endl;
    }
    */

    int ans = 0x3f3f3f;
    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            int sum = 0;
            for(int st = 0; st < (int)chess.size(); st++) {
                sum += board[chess[st].idx()][r][c];
            }
            ans = min(ans, sum);
            for(int kr = 0; kr < R; kr++) {
                for(int kc = 0; kc < C; kc++) {
                    pos kp(kr, kc);
                    int ttsu = board[0][kp.r][kp.c] + board[kp.idx()][r][c];
                    for(int st = 1; st < (int)chess.size(); st++) {     // chose a knight
                        int tsu = ttsu + board[chess[st].idx()][kr][kc];
                        int tsum = tsu + sum - board[0][r][c] - board[chess[st].idx()][r][c];
                        ans = min(ans, tsum);
                    }
                }
            }
        }
    }
    fout << ans << endl;
    return 0;
}
