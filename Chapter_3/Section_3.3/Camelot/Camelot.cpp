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
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxr = 30 + 3;

int board[maxr*maxr][maxr][maxr];
int vis[maxr][maxr];
int withoutk[maxr*maxr];
int withk[maxr][maxr];

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
        return r * maxr + c + 1;
    }
};
vector<pos> chess;
queue<pair<pos, int> > que;

void bfs(pos pst, int st, bool iskn) {
    memset(vis, 0, sizeof(vis));

    que.push(make_pair(pst, 0));
    vis[pst.r][pst.c] = 1;

    while(!que.empty()) {
        pos tp = que.front().first; 
        int d = que.front().second;
        que.pop();

        board[st][tp.r][tp.c] = d;

        for(int i = 0; i < 8; i++) {
            pos np = tp.next(dr[iskn], dc[iskn], i);
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
    fin >> c >> r;
    pos king(r-1, c-'A');
    for(int i = 1; fin >> c >> r; i++) {
        chess.push_back(pos(r-1, c-'A'));
    }


    bfs(king, 0, 0);
    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            pos np(r, c);
            bfs(np, np.idx(), 1);
        }
    }

    /*
    cout << "=======" << endl;
    for(int st = 0; st < (int)chess.size(); st++) {
        cout << "st = " << st << endl;
        cout << "r = " << chess[st].r << endl;
        cout << "c = " << chess[st].c << endl;
        for(int r = 0; r < R; r++) {
            for(int c = 0; c < C; c++)
                printf("%02d ", board[chess[st].idx()][r][c]);
                // cout << board[chess[st].idx()][r][c] << " ";
            cout << endl;
        }
        cout << "-----" << endl;
    }
    */

    int ans = 0x3f3f3f;
    for(int r = 0; r < R; r++) {
        for(int c = 0; c < C; c++) {
            int sum = 0;
            bool flag = 0;
            for(int st = 0; st < (int)chess.size(); st++) {
                if(board[chess[st].idx()][r][c] >= 0x3f3f) {
                    flag = 1; break;
                }
                sum += board[chess[st].idx()][r][c];
            }
            if(flag) continue;
            sum += board[0][r][c];
            ans = min(ans, sum);

            for(int kr = 0; kr < R; kr++) {
                for(int kc = 0; kc < C; kc++) {
                    pos kp(kr, kc);
                    withk[kr][kc] = board[0][kp.r][kp.c] + board[kp.idx()][r][c];
                }
            }

            for(int st = 0; st < (int)chess.size(); st++) {
                // withoutk[chess[st].idx()] = sum - board[0][r][c] - board[chess[st].idx()][r][c];
                int tmp = sum - board[0][r][c] - board[chess[st].idx()][r][c];
                if(tmp >= ans) continue;
                for(int kr = 0; kr < R; kr++) {
                    for(int kc = 0; kc < C; kc++) {
                        ans = min(ans, tmp + withk[kr][kc] + board[chess[st].idx()][kr][kc]);
                    }
                }
            }
        }
    }
    fout << ans << endl;
    return 0;
}
