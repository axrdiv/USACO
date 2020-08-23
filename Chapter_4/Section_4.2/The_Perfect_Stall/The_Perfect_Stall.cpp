/*
ID: axrdiv1
PROG: stall4
LANG: C++
*/

/*
有点最大匹配的意思
*/

#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
const int maxn = 200 + 5;
const int maxm = 200 + 5;
const int maxnum = maxn + maxm;

int adj[maxnum][maxnum];
int vis[maxnum], prevnode[maxnum];
int flow[maxnum];

ifstream fin("stall4.in");
ofstream fout("stall4.out");

int N, M;
int netflow(int source, int sink) {
    if(source == sink) return (1<<30);

    int total_flow = 0;

    while(true) {
        for(int i = 0; i < maxnum; i++) {
            prevnode[i] = 0;
            flow[i] = 0;
            vis[i] = 0;
        }
        flow[source] = (1<<10);
        int flag_inner = 1;
        int maxloc;
        while(flag_inner) {
            int maxflow = 0;
            maxloc = -1;
            for(int i = 0; i < maxnum; i++) {
                if(flow[i] > maxflow && !vis[i]) {
                    maxflow = flow[i];
                    maxloc = i;
                }
            }
            if(maxloc == -1) {
                flag_inner = 0; break;
            }
            if(maxloc == sink) {
                flag_inner = 0; break;
            }
            vis[maxloc] = 1;
            // update it's neighbors
            for(int i = 0; i < maxnum; i++) {
                if(adj[maxloc][i] > 0 && flow[i] < min(maxflow, adj[maxloc][i])) {
                    prevnode[i] = maxloc;
                    flow[i] = min(maxflow, adj[maxloc][i]);
                }
            }
        }
        if(maxloc == -1)
            break;
        int pathcapacity = flow[sink];
        total_flow += pathcapacity;

        int curnode = sink;
        while(curnode != source) {
            int nextnode = prevnode[curnode];
            adj[nextnode][curnode] -= pathcapacity;
            adj[curnode][nextnode] += pathcapacity;
            curnode = nextnode;
        }
    }
    return total_flow;
}

int main() {
    fin >> N >> M;
    for(int i = 1; i <= N; i++) {
        adj[0][i] = 1;
    }
    for(int i = 0; i <= M; i++) {
        adj[maxn+i][maxnum-1] = 1;
    }

    int s, m;
    for(int i = 1; i <= N; i++) {
        fin >> s;
        for(int j = 0; j < s; j++) {
            fin >> m;
            adj[i][maxn+m] = 1;
        }
    }

    fout << netflow(0, maxnum-1) << endl;

    return 0;
}
