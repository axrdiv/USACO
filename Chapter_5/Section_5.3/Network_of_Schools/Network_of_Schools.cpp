/*
ID: axrdiv1
PROG: schlnet
LANG: C++
*/

/* 
 * Task A:
 *  computes the minimal number of schools that must receive a copy of the new
 *  software in order for the software to reach all schools in the network
 *  according to the agreement
 *
 *  Solution:
 *
 * Task B:
 *  we want to ensure that by sending the copy of new software to an arbitrary
 *  school, this software will reach all schools in the network.To achieve this
 *  goal we may have to extend the lists of receivers by new members. Compute
 *  the minimal number of extensions that have to be made so that whatever
 *  school we send the new software to, it will reach all other schools 
 *
 *  Solution:
 */

/*
 * 详见PCCB P320
 */

#include<iostream>
#include<fstream>
#include<vector>
#include<cstring>
using namespace std;
const int MAX_V = 120;

ofstream fout("schlnet.out");
ifstream fin("schlnet.in");
int N;
vector<int> G[MAX_V];        // 图的邻接表表示
vector<int> rG[MAX_V];       // 把边反向后的图
vector<int> vs;             // 后续遍历顺序的顶点列表
bool used[MAX_V];            // 访问标记
int cmp[MAX_V];

int in[MAX_V], out[MAX_V];

void dfs(int v) {
    used[v] = true;
    for(int i = 0; i < (int)G[v].size(); i++) {
        if(!used[G[v][i]]) dfs(G[v][i]);
    }
    vs.push_back(v);
}

void rdfs(int v, int k) {
    used[v] = true;
    cmp[v] = k;
    for(int i = 0; i < (int)rG[v].size(); i++) {
        if(!used[rG[v][i]]) rdfs(rG[v][i], k);
    }
}

int scc() {
    memset(used, 0, sizeof(used));
    vs.clear();
    for(int v = 1; v <= N; v++) {
        if(!used[v]) dfs(v);
    }
    memset(used, 0, sizeof(used));
    int k = 0;
    for(int i = vs.size() - 1; i >= 0; i--) {
        if(!used[vs[i]]) rdfs(vs[i], k++);
    }
    return k;
}

void solve() {
    int num = scc();
    if(num == 1) {
        fout << 1 << endl << 0 << endl;
        return;
    }

    for(int u = 1; u <= N; u++) {   // u -> v
        // u->v 如果这两个点的颜色相同，那么算是
        // 一个点来处理。即既不计算入度也不计算出度
        // 如果颜色不相同，则当成两个点来处理，
        // 即 out[uu]++; in[vv]++;
        // 这里的点可以理解为缩点后的点
        for(int i = 0; i < (int)G[u].size(); i++) {
            int v = G[u][i];
            int uu = cmp[u], vv = cmp[v];
            if(uu != vv) {
                out[uu]++;
                in[vv]++;
            }
        }
    }

    int zero_in_num = 0, zero_out_num = 0;
    for(int i = 0; i < num; i++) {
        if(!in[i]) zero_in_num++;
        if(!out[i]) zero_out_num++;
    }
    fout << zero_in_num << endl << max(zero_out_num, zero_in_num) << endl;
}

int main() {
    fin >> N;

    // 读入数据
    int to;
    for(int from = 1; from <= N; from++) {
        while((fin >> to) && to) {
            G[from].push_back(to);
            rG[to].push_back(from);
        }
    }

    solve();

    return 0;
}
