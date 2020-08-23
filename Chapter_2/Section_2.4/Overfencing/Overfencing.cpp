/*
ID: axrdiv1
PROG: maze1
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;

const int maxl = 40 * 100;
const int maxw = 38;
const int maxh = 100;

int W, H;

vector<string> maze;
bool vis[maxh][maxw];
int mlen[maxh][maxw];

ofstream fout("maze1.out");
ifstream fin("maze1.in");

struct pos {
    int x, y;
    pos(int x=0, int y=0): x(x), y(y) {};
};

pos exits[2];
queue<pair<pos, int> > Q;

void find_exit() {
    int cnt = 0;
    // find four edges
    for(int i = 1; i < 2*W+1; i+=2) {
        if(maze[0][i] == ' ') {
            exits[cnt++] = pos(0, (i-1)/2);
        }
        if(maze[2*H][i] == ' ') {
            exits[cnt++] = pos(H-1, (i-1)/2);
        }
    }
    for(int i = 1; i < 2*H+1; i+=2) {
        if(maze[i][0] == ' ') {
            exits[cnt++] = pos((i-1)/2, 0);
        }
        if(maze[i][2*W] == ' ') {
            exits[cnt++] = pos((i-1)/2, W-1);
        }
    }
    /*
    cout << exits[0].x << " " << exits[0].y << endl;
    cout << exits[1].x << " " << exits[1].y << endl;
    */
}

void bfs(pos& p) {
    memset(vis, 0, sizeof(vis));
    Q.push(make_pair(p, 1));
    vis[p.x][p.y] = 1;
    while(!Q.empty()) {
        pos tp = Q.front().first;
        int td = Q.front().second;
        Q.pop();
        mlen[tp.x][tp.y] = min(mlen[tp.x][tp.y], td);
        // left
        if(!vis[tp.x][tp.y-1] && maze[2*tp.x+1][2*tp.y] == ' ' && tp.y-1 >= 0) {
            vis[tp.x][tp.y-1] = 1;
            Q.push(make_pair(pos(tp.x, tp.y-1), td+1));
        }
        // right
        if(!vis[tp.x][tp.y+1] && maze[2*tp.x+1][2*tp.y+2] == ' ' && tp.y+1 < W) {
            vis[tp.x][tp.y+1] = 1;
            Q.push(make_pair(pos(tp.x, tp.y+1), td+1));
        }
        // up
        if(!vis[tp.x-1][tp.y] && maze[2*tp.x][2*tp.y+1] == ' ' && tp.x-1 >= 0) {
            vis[tp.x-1][tp.y] = 1;
            Q.push(make_pair(pos(tp.x-1, tp.y), td+1));
        }
        // down
        if(!vis[tp.x+1][tp.y] && maze[2*tp.x+2][2*tp.y+1] == ' ' && tp.x+1 < H) {
            vis[tp.x+1][tp.y] = 1;
            Q.push(make_pair(pos(tp.x+1, tp.y), td+1));
        }
    }
}

int main() {
    fin >> W >> H;
    string line;
    fin.get();
    for(int i = 0; i < 2*H+1; i++) {
        getline(fin, line);
        maze.push_back(line);
    }
    /*
    for(int i = 0; i < 2*H+1; i++) {
        cout << maze[i] << endl;
    }
    */
    // cout << maze.size() << " " << maze[0].size() << endl;
    find_exit();

    for(int i = 0; i < H; i++) for(int j = 0; j < W; j++)
        mlen[i][j] = maxl;

    bfs(exits[0]);
    bfs(exits[1]);
    int ret = 0;
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            // cout << mlen[i][j] << " ";
            ret = max(ret, mlen[i][j]);
        }
        // cout << endl;
    }

    fout << ret << endl;

    return 0;
}
