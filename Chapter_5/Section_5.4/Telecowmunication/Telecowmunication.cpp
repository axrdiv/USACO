/*
ID: axrdiv1
PROG: telecow
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
using namespace std;
const int MAX_N = 100 + 5;
const int INF = 1000;

ofstream fout("telecow.out");
ifstream fin("telecow.in");
int N, M, c1, c2;
int adj[MAX_N * 2][MAX_N * 2];
int org_adj[MAX_N * 2][MAX_N * 2];
int prevn[MAX_N * 2];
int flow[MAX_N * 2];
int vis[MAX_N * 2];

void init() {
    for(int p = 1; p <= N; p++) {
        // 入口 -> 出口
        org_adj[p + N][p] = 1;
    }
}

int netflow(int st, int ed) {
    int totalflow = 0;
    while(true) {
        for(int i = 1; i < 2*N + 2; i++) {
            prevn[i] = -1;
            flow[i] = 0;
            vis[i] = 0;
        }
        flow[st] = INF;

        int maxflow;
        int maxloc;
        while(true) {
            maxflow = 0;
            maxloc = -1;
            for(int i = 1; i < 2*N + 2; i++) {
                if(flow[i] > maxflow && !vis[i]) {
                    maxflow = flow[i];
                    maxloc = i;
                }
            }
            if(maxloc == -1) break;
            if(maxloc == ed) break;
            vis[maxloc] = 1;

            // update its neighbors
            for(int i = 0; i < 2*N + 2; i++) {
                if(flow[i] < min(maxflow, adj[maxloc][i])) {
                    prevn[i] = maxloc;
                    flow[i] = min(maxflow, adj[maxloc][i]);
                }
            }
        }
        if(maxloc == -1) break;
        int pathcapacity = flow[ed];
        totalflow += pathcapacity;

        int curnode = ed;
        while(curnode != st) {
            int nextnode = prevn[curnode];
            adj[nextnode][curnode] -= pathcapacity;
            adj[curnode][nextnode] += pathcapacity;
            curnode = nextnode;
        }
    }
    return totalflow;
}

int main() {
    fin >> N >> M >> c1 >> c2;
    init();

    int from, to;
    for(int i = 0; i < M; i++) {
        fin >> from >> to;
        org_adj[from][to + N] = INF;
        org_adj[to][from + N] = INF;
    }

    memcpy(adj, org_adj, sizeof(org_adj));
    int nflow = netflow(c1, c2 + N);

    vector<int> ans;

    for(int i = 1; i <= N; i++) {
        memcpy(adj, org_adj, sizeof(org_adj));
        adj[i + N][i] = 0;
        int cutflow = netflow(c1, c2 + N);
        if(cutflow == nflow - 1) {
            ans.push_back(i);
            nflow = cutflow;
            org_adj[i + N][i] = 0;
            if(nflow == 0) break;
        }
    }

    fout << ans.size() << endl;
    for(int i = 0; i < (int)ans.size() - 1; i++) {
        fout << ans[i] << " ";
    }
    fout << ans.back() << endl;

    return 0;
}
