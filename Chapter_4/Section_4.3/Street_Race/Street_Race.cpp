/*
ID: axrdiv1
PROG: race3
LANG: C++
*/


/*
 * 可能要用最小割算法
 * 其实不用流也是可以，用dfs，然后除去某一个点，查看是否可以到达重点
 */

#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
using namespace std;
const int maxp = 50 + 5;
const int maxa = 100 + 5;
const int maxnum = maxp;

ofstream fout("race3.out");
ifstream fin("race3.in");

int orig_adj[maxp][maxp], adj[maxp][maxp];
int vis[maxnum], prevnode[maxnum];
int flow[maxnum];

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

vector<int> unavoid;
void find_unavoidable(int N) {
    for(int p = 1; p < N; p++) {
        memcpy(adj, orig_adj, sizeof(orig_adj));
        for(int i = 0; i < N; i++) {
            adj[i][p] = 0;
        }
        if(netflow(0, N) == 0)
            unavoid.push_back(p);
    }
}

void dfs(int st, int& cnt, const int& ed, const int& N) {
    if(vis[st]) return;
    cnt++;
    vis[st] = 1;
    if(st == ed) return;
    for(int i = 0; i < N; i++) {
        if(orig_adj[st][i] && !vis[i]) {
            dfs(i, cnt, ed, N);
        }
    }
}

vector<int> split;
void find_split(int N) {
    for(int i = 0; i < (int)unavoid.size(); i++) {
        int cnt = 0;

        memset(vis, 0, sizeof(vis));
        dfs(0, cnt, unavoid[i], N);

        memset(vis, 0, sizeof(vis));
        dfs(unavoid[i], cnt, N, N);
        // cout << cnt << " " << N << endl;
        if(cnt == N+1)
            split.push_back(unavoid[i]);
    }
}


int main() {
    int N;
    for(N = 0; N < maxp; N++) {
        int t, flag = 0;
        while(fin >> t) {
            if(t == -1) { flag = 1; break; }
            if(t == -2) break;
            orig_adj[N][t] = 1;
        }
        if(flag) {
            N -= 1;
            break;
        }
    }
    // cout << N << endl;
    find_unavoidable(N);
    find_split(N);
    fout << unavoid.size();
    for(int i = 0; i < (int)unavoid.size(); i++)
        fout << " " << unavoid[i];
    fout << endl << split.size();
    for(int i = 0; i < (int)split.size(); i++)
        fout << " " << split[i];
    fout << endl;
    return 0;
}
