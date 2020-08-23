/*
ID: axrdiv1
PROG: ttwo
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

const int maxn = 10;
char forest[maxn][maxn];
bool vis[maxn*maxn*4][maxn*maxn*4];

ofstream fout("ttwo.out");
ifstream fin("ttwo.in");

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

struct pos {
    int x, y, d;
    pos(int x=0, int y=0, int d=0): x(x), y(y), d(d) {};
    bool is_vaild() {
        return x >= 0 && x < maxn && y >= 0 && y < maxn && forest[x][y] != '*';
    }
    int hash() {
        return (x * maxn + y)*4+d;
    }
    pos next() {
        pos np(x+dx[d], y+dy[d], d);
        if(np.is_vaild()) return np;
        else return pos(x, y, (d+1)%4);
    }
    bool operator== (const pos& b) const {
        return x == b.x && y == b.y;
    }
};



pos FJ, CW;

int force() {
    int cnt = 0;
    while(!(FJ == CW)) {
        // cout << FJ.x << " " << FJ.y << endl;
        // cout << CW.x << " " << CW.y << endl;
        if(vis[FJ.hash()][CW.hash()]) return 0;
        vis[FJ.hash()][CW.hash()] = 1;
        FJ = FJ.next();
        CW = CW.next();
        cnt++;
    }
    return cnt;
}

int main() {
    string line;
    for(int i = 0; i < maxn; i++) {
        fin >> line;
        stringstream ss(line);
        for(int j = 0; j < maxn; j++) {
            ss >> forest[i][j];
            if(forest[i][j] == 'F')
                FJ = pos(i, j, 0);
            if(forest[i][j] == 'C')
                CW = pos(i, j, 0);
        }
    }
    fout << force() << endl;
    return 0;
}
