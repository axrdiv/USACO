/*
 TASK: camelot
 LANG: C++
 ID: lutongy1
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>

using namespace std;

//MARK: Global constants

const int MAXR = 30, MAXC = 35;
const int MAXK = MAXR * MAXC;
const int MAXN = MAXR * MAXC * 2;
const int MAXM = MAXN * 10;

const int knightMoves[8][2] = {
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
    {-1, -2},
    {-2, -1},
    {-2, 1},
    {-1, 2}
};

//MARK: Global variables

int X, Y, knightCnt;

int knights[MAXK], kingX, kingY;

inline bool setKnight(int id, int x, int y) {
    knights[id] = ((x << 5) | y);
    // fprintf(stdout, "setKnight(id: %d, x: %d, y: %d) => %s\n", id, x, y, (x < 0 || x >= 32 || y < 0 || y >= 32) ? "true" : "false");
    return (x < 0 || x >= 32 || y < 0 || y >= 32);
}

inline int knightX(int id) {
    // fprintf(stdout, "knightX(id: %d) => %d\n", id, (knights[id] >> 5) & 0x1f);
    return (knights[id] >> 5) & 0x1f;
}

inline int knightY(int id) {
    // fprintf(stdout, "knightY(id: %d) => %d\n", id, knights[id] & 0x1f);
    return knights[id] & 0x1f;
}

inline int kingDist(int x, int y) {
    // fprintf(stdout, "kingDist(x: %d, y: %d) => %d\n", x, y, max(abs(x), abs(y)));
    return max(abs(x - kingX), abs(y - kingY));
}

inline int ctoi(char c) {
    fprintf(stdout, "ctoi(c: \'%c\') => %d\n", c, ((c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0));
    return (c >= 'A' && c <= 'Z') ? c - 'A' + 1 : 0;
}

inline int coordId(int x, int y, bool withKing = false) {
    // fprintf(stdout, "coordId(x: %d, y: %d, withKing: %s) => %d\n", x, y, withKing ? "true" : "false", ((y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0)));
    return (y - 1) + (x - 1) * Y + (withKing ? (X * Y) : 0);
}

inline int coordX(int id) {
    // fprintf(stdout, "coordX(id: %d) => %d\n", id, (id / Y) % X + 1);
    return (id / Y) % X + 1;
}

inline int coordY(int id) {
    // fprintf(stdout, "coordY(id: %d) => %d\n", id, id % Y + 1);
    return id % Y + 1;
}

inline bool coordWithKing(int id) {
    // fprintf(stdout, "coordWithKing(id: %d) => %s\n", id, (id / X / Y) ? "true" : "false");
    return id / X / Y;
}

inline bool isValidMove(int cid, int moveId, int *targid = NULL) {
    int x = coordX(cid) + knightMoves[moveId][0];
    int y = coordY(cid) + knightMoves[moveId][1];
    bool f = (x > 0 && x <= X && y > 0 && y <= Y);
    if (f && targid) *targid = coordId(x, y, coordWithKing(cid));
    fprintf(stdout, "isValidMove(cid: %d, moveId: %d, targid: %p(=>%d)) => %s\n", cid, moveId, targid, targid ? *targid : -1, f ? "true" : "false");
    return f;
}

struct Edge {
    int v, c;
    Edge *next;
} *h[MAXN], pool[MAXM];
int edgeTot;

inline void addEdge(int u, int v, int c) {
    Edge *p = pool + (edgeTot ++);
    p->v = v; p->c = c; p->next = h[u];
    h[u] = p;
    fprintf(stdout, "addEdge(u: %d, v: %d, c: %d) => void\n", u, v, c);
}

void buildMap() {
    int u, v, move;
    // Knight moves
    for (u = 0; u < X * Y * 2; u ++)
        for (move = 0; move < 8; move ++)
            if (isValidMove(u, move, &v))
                addEdge(u, v, 1); // Only forward, since backward will be added later
    // Take king
    for (u = 0, v = X * Y; u < X * Y; u ++, v ++)
        addEdge(u, v, kingDist(coordX(u), coordY(u)));
}

struct Node {
    int id, val;
    bool operator >(const Node other) const {
        return (val == other.val) ? (id > other.id) : val > other.val;
    }
} placeholderNode;

priority_queue<Node, vector<Node>, greater<Node> > q;

const int INF = 0x3f3f3f3f;

int dis[MAXN], pre[MAXN];
bool vis[MAXN];

void dijkstra(int src) {
    while (!q.empty()) q.pop();
    memset(dis, 0x3f, sizeof(dis));
    memset(vis, 0, sizeof(vis));
    memset(pre, -1, sizeof(pre));
    q.push((Node){src, dis[src] = 0});
    while (!q.empty()) {
        int u = q.top().id; q.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (Edge *p = h[u]; p; p = p->next) {
            if (dis[p->v] > dis[u] + p->c) {
                pre[p->v] = u;
                q.push((Node){p->v, dis[p->v] = dis[u] + p->c});
            }
        }
    }
}

//MARK: Debug

void printCoord(int id) {
    fprintf(stdout, "[%c%2d]", coordX(id) - 1 + 'A', coordY(id));
}

void printTrace(int src, int dest) {
    printCoord(src);
    while (src != dest && pre[src] >= 0) {
        int nxt = pre[src];
        if (src - nxt >= X * Y) {
            fprintf(stdout, " (king %d)", dis[src] - dis[nxt]);
        } else {
            fprintf(stdout, " > ");
            printCoord(nxt);
        }
        src = nxt;
    }
    fprintf(stdout, " (END)");
}

int camelot;
int ans, sum, minadd, minaddId, kx, ky;

void processDis() {
    sum = 0; minadd = INF;
    for (int i = 1; i <= knightCnt; i ++) {
        kx = knightX(i); ky = knightY(i);
        if (dis[coordId(kx, ky)] == INF) return;
        sum += dis[coordId(kx, ky)];
        if (minadd > dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)]) {
            minadd = dis[coordId(kx, ky, true)] - dis[coordId(kx, ky)];
            minaddId = i;
        }
    }
    if (!knightCnt) minadd = 0;
    ans = min(ans, sum + minadd);
    fprintf(stdout, "\n");
    for (int i = 1; i <= 60; i ++) fprintf(stdout, "*");
    fprintf(stdout, "\n\n");
    fprintf(stdout, "Camelot = "); printCoord(camelot); fprintf(stdout, "\n");
    fprintf(stdout, "King starts from "); printCoord(coordId(kingX, kingY)); fprintf(stdout, "\n\n");
    for (int i = 1; i <= knightCnt; i ++) {
        fprintf(stdout, "Knight #%3d: ", i);
        kx = knightX(i); ky = knightY(i);
        printTrace(coordId(kx, ky, minaddId == i), camelot);
        fprintf(stdout, "\n\tadds %d to total distance.\n", dis[coordId(kx, ky, minaddId == i)]);
    }
    fprintf(stdout, "\nTotal distance: %8d\nAnswer:         %8d\n", sum + minadd, ans);
    fprintf(stdout, "\n");
    for (int i = 1; i <= 60; i ++) fprintf(stdout, "*");
    fprintf(stdout, "\n\n");
}

//MARK: IO

FILE *in, *out;

//MARK: Main

int main(int argc, char const *argv[]) {
    // Input
    fprintf(stdout, "Reading in...\n");
    in = fopen("camelot.in", "r");
    char s_cx[2];
    int cy;
    fscanf(in, "%d%d%s%d", &Y, &X, s_cx, &kingY);
    kingX = ctoi(s_cx[0]);
    while (fscanf(in, "%s%d", s_cx, &cy) != EOF)
        setKnight(++ knightCnt, ctoi(s_cx[0]), cy);
    fclose(in);
    // Calc
    fprintf(stdout, "Building map...\n");
    buildMap();
    fprintf(stdout, "Initialize variable \'ans\' to 0x%x\n", ans = INF);
    fprintf(stdout, "Iterating through tiles...\n");
    for (camelot = 0; camelot < X * Y; camelot ++) {
        dijkstra(camelot);
        processDis();
    }
    // Output
    fprintf(stdout, "Writing output...\n");
    out = fopen("camelot.out", "w");
    fprintf(out, "%d\n", ans);
    fclose(out);
    fprintf(stdout, "Complete!\n");
    return 0;
}