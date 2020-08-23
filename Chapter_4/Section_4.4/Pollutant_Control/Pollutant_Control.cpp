/*
ID: axrdiv1
PROG: milk6
LANG: C++
*/

// 最小割问题

#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<set>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn = 35;
const int INF = (1<<30);

ofstream fout("milk6.out");
ifstream fin("milk6.in");

int org_adj[maxn][maxn], adj[maxn][maxn];
int vis[maxn], pre[maxn], flw[maxn];
int N, M;
vector<int> shutdown;
map<pair<int,int>, int> rote;
struct edge {
    int s, e, c, id;
    edge(int s=0, int e=0, int c=0, int id=0): s(s), e(e), c(c), id(id) {};
    bool operator< (const edge& b) const {
        return c > b.c || (c == b.c && id < b.id);
    }
};

vector<edge> vec;

int minicut() {
    int source = 1, sink = N;
    if(source == sink) return (1<<30);

    int netflow = 0;
    while(true) {
        for(int i = 1; i <= N; i++) {
            pre[i] = 0;
            flw[i] = 0;
            vis[i] = 0;
        }
        flw[source] = INF;
        int loc;
        while(true) {
            int maxflow = 0;
            loc = 0;
            for(int i = source; i <= sink; i++) {
                if(flw[i] > maxflow && !vis[i]) {
                    maxflow = flw[i];
                    loc = i;
                }
            }

            if(loc == 0) break;
            if(loc == sink) break;

            vis[loc] = 1;
            for(int i = 1; i <= N; i++) {
                if(adj[loc][i] && flw[i] < min(maxflow, adj[loc][i])) {
                    flw[i] = min(adj[loc][i], maxflow);
                    pre[i] = loc;
                }
            }
        }
        if(loc == 0) break;
        int pathcapacity = flw[sink];
        netflow += pathcapacity;

        int curnode = sink;
        while(curnode != source) {
            int nextnode = pre[curnode];
            adj[nextnode][curnode] -= pathcapacity;
            adj[curnode][nextnode] += pathcapacity;
            curnode = nextnode;
        }
    }
    return netflow;
}

int main() {
    fin >> N >> M;
    int s, e, c;
    for(int i = 1; i <= M; i++) {
        fin >> s >> e >> c;
        org_adj[s][e] += c;
        rote[make_pair(s, e)] = i;
        vec.push_back(edge(s, e, c, i));
    }
    memcpy(adj, org_adj, sizeof(org_adj));
    int t = minicut();
    fout << t << " ";
    sort(vec.begin(), vec.end());
    for(int i = 0; i < (int)vec.size(); i++) {
        edge& ed = vec[i];
        if(ed.c > t) continue;

        memcpy(adj, org_adj, sizeof(org_adj));
        adj[ed.s][ed.e] -= ed.c;

        int nt = minicut();
        if(t - nt == ed.c) {
            shutdown.push_back(ed.id);
            org_adj[ed.s][ed.e] -= ed.c;
            t = nt;
        }
    }
    sort(shutdown.begin(), shutdown.end());

    fout << shutdown.size() << endl;
    for(int i = 0; i < (int)shutdown.size(); i++) {
        fout << shutdown[i] << endl;
    }
    return 0;
}
