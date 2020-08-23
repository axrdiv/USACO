/*
ID: axrdiv1
PROG: ditch
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int maxm = 200 + 5;
const int maxn = 200 + 5;
long long adj[maxm][maxm];
int vis[maxn], prevnode[maxn];
long long flow[maxn];
int N, M;

ofstream fout("ditch.out");
ifstream fin("ditch.in");

int netflow() {
    int source = 1, sink = M;
    if(source == sink) return (1<<30);

    int total_flow = 0;

    while(true) {
        for(int i = 1; i <= M; i++) {
            prevnode[i] = 0;
            flow[i] = 0;
            vis[i] = 0;
        }
        flow[source] = (1<<30);
        int maxloc;
        while(true) {
            long long maxflow = 0;
            maxloc = 0;
            for(int i = 1; i <= M; i++) {
                if(flow[i] > maxflow && !vis[i]) {
                    maxflow = flow[i];
                    maxloc = i;
                }
            }
            if(maxloc == 0) {
                break;
            }
            if(maxloc == sink) {
                break;
            }
            vis[maxloc] = 1;
            // update it's neighbors
            for(int i = 1; i <= M; i++) {
                if(adj[maxloc][i] > 0 && flow[i] < min(maxflow, adj[maxloc][i])) {
                    prevnode[i] = maxloc;
                    flow[i] = min(maxflow, adj[maxloc][i]);
                }
            }
        }
        if(maxloc == 0)
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
    int s, e, c;
    for(int i = 0; i < N; i++) {
        fin >> s >> e >> c;
        adj[s][e] += c;
    }
    fout << netflow() << endl;
    return 0;
}
