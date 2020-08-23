/*
ID: axrdiv1
PROG: snail
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
const int MAXN = 120;

/*
 *      0
 *    3   1
 *      2
 */

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

typedef struct pos {
    int x, y, dir;
    pos(int x=0, int y=0, int dir=0) : x(x), y(y), dir(dir) {};

    pos next() {
        pos p;
        p.x = x + dx[dir];
        p.y = y + dy[dir];
        p.dir = dir;
        return p;
    }

    pos before() {
        pos p;
        p.x = x - dx[dir];
        p.y = y - dy[dir];
        p.dir = dir;
        return p;
    }

    bool valid(int n) const {
        return x >= 0 && x < n && y >= 0 && y < n;
    }

    pos operator= (const pos& p) {
        x = p.x;
        y = p.y;
        dir = p.dir;
        return *this;
    }

} P;

ofstream fout("snail.out");
ifstream fin("snail.in");

int N, B;
int graph[MAXN][MAXN];
bool vis[MAXN][MAXN];
int mxl;

void dfs(P st, int l) {
    P t = st;
    int hold[MAXN][MAXN];
    // store the memory
    memcpy(hold, vis, sizeof(vis));

    while(t.valid(N)) {
        if(vis[t.x][t.y]) {
            memcpy(vis, hold, sizeof(vis));
            return;
        }
        if(graph[t.x][t.y]) break;
        vis[t.x][t.y] = 1;
        t = t.next();
        mxl = max(mxl, ++l);
    }

    if(!t.valid(N) || (t.valid(N) && graph[t.x][t.y])) {  // encounter something
        P bp = t.before();
        vis[bp.x][bp.y] = 0;
        bp.dir = (bp.dir+1)%4;
        P nbp = bp.next();
        if(nbp.valid(N) && !graph[nbp.x][nbp.y])
            dfs(bp, l-1);

        bp = t.before();
        bp.dir = (bp.dir+3)%4;
        nbp = bp.next();
        if(nbp.valid(N) && !graph[nbp.x][nbp.y])
        dfs(bp, l-1);
    }

    // reset memory
    memcpy(vis, hold, sizeof(vis));
}

int main() {
    fin >> N >> B;
    char c; int t;
    for(int i = 0; i < B; i++) {
        fin >> c >> t;
        graph[t-1][c-'A'] = 1;
    }

    P st(0, 0, 1);
    dfs(st, 0);

    st.dir = 2;
    dfs(st, 0);

    fout << mxl << endl;
    return 0;
}
