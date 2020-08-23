/*
    ID: m1500293
    LANG: C++
    PROG: schlnet
*/
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;
const int max_v = 120;

struct Scc
{
    int V;           //图的顶点数
    vector<int> G[max_v];    //原始图
    vector<int> rG[max_v];   //反向边的图
    vector<int> vs;          //后序遍历顶点列表
    bool used[max_v];        //访问标记
    int cmp[max_v];          //所属强连通分量的拓扑排序
    void init()
    {
        for(int i=0; i<=V; i++) G[i].clear(), rG[i].clear();
    }
    void add_edge(int from, int to)
    {
        G[from].push_back(to);
        rG[to].push_back(from);
    }
    void dfs(int v)
    {
        used[v] = true;
        for(int i=0; i<(int)G[v].size(); i++)
            if(!used[G[v][i]]) dfs(G[v][i]);
        vs.push_back(v);
    }
    void rdfs(int v, int k)
    {
        used[v] = true;
        cmp[v] = k;
        for(int i=0; i<(int)rG[v].size(); i++)
            if(!used[rG[v][i]]) rdfs(rG[v][i], k);
    }
    int scc()
    {
        memset(used, 0, sizeof(used));
        vs.clear();
        for(int v=1; v<=V; v++)
            if(!used[v]) dfs(v);
        memset(used, 0, sizeof(used));
        int k = 1;
        for(int i=vs.size()-1; i>=0; i--)
            if(!used[vs[i]]) rdfs(vs[i], k++);
        return k-1;
    }
}ss;
int num;   //强连通分量的个数
int in[110], out[110];
int main()
{
    freopen("schlnet.in", "r", stdin);
    freopen("schlnet.out", "w", stdout);
    int N;
    scanf("%d", &N);
    ss.V = N;
    ss.init();
    for(int i=1; i<=N; i++)
    {
        int t;
        scanf("%d", &t);
        while(t != 0)
        {
            ss.add_edge(i, t);
            scanf("%d", &t);
        }
    }

    num = ss.scc();
    if(num == 1)
    {
        printf("1\n0\n");
        return 0;
    }
    for(int u=1; u<=N; u++)             //u->v
        // u->v 如果这两个点的颜色相同，那么算是
        // 一个点来处理。即既不计算入度也不计算出度
        // 如果颜色不相同，则当成两个点来处理，
        // 即 out[uu]++; in[vv]++;
        // 这里的点可以理解为缩点后的点
        for(int j=0; j<(int)ss.G[u].size(); j++)
        {
            int v = ss.G[u][j];
            int uu=ss.cmp[u], vv=ss.cmp[v];
            if(uu != vv)
            {
                in[vv]++;
                out[uu]++;
            }
        }
    int in_0_num=0, out_0_num=0;
    for(int i=1; i<=num; i++)
    {
        if(!in[i])  in_0_num++;
        if(!out[i]) out_0_num++;
    }
    printf("%d\n%d\n", in_0_num, max(in_0_num, out_0_num));
    return 0;
}
