#include<bits/stdc++.h>
using namespace std;
int a[110][110]={0},
    l[110][110]={0},
    n;
int in[110]={0},
    out[110]={0},
    team[110]={0};
int ins=0,
    outs=0,
    sum=0;

inline void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        int t;
        scanf("%d",&t);
        while(t>0)
        {
            a[i][t]=l[i][t]=1;
            in[t]++;//需要记录入度和出度
            out[i]++;
            scanf("%d",&t);
        }
    }
    return;
}

inline void floyed()
{
    for(int k=1;k<=n;k++)
    for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
    a[i][j]=a[i][j]||(a[i][k]&&a[k][j]);
    return;
}

inline void work()
{
    memset(team,-1,sizeof(team));
    for(int i=1;i<=n;i++)
    {
        if(team[i]==-1) //如果i点未涂色 
            team[i]=i;  //涂色 
        else
        {
            in[team[i]]+=in[i];     //i所属的强联通分量入度加上i的入度 
            out[team[i]]+=out[i];   //出度同理 
        }
        for(int j=1;j<=n;j++)           //这里每个点都要搜一遍 
            if(a[i][j]&&a[j][i])        //如果i,j属于同一强联通分量 
            {
                team[j]=team[i];        //涂色 
                if(l[i][j])             //如果i,j直接有边相连 
                {
                    in[team[i]]--;      //i所属的强联通分量入度-1
                    out[team[i]]--;     //出度同理 
                }
            }
    }
    return;
}

inline void print()
{
    for(int i=1;i<=n;i++)
    if(team[i]==i)//搜索缩点后的各个点 
    {
        sum++;//强连通分量数 
        if(in[i]==0)ins++;//入度为0的点数 
        if(out[i]==0)outs++;//出度为0的点数 
    }
    if(sum==1)printf("1\n0");//如果只有一个强联通分量 
    else printf("%d\n%d",ins,max(ins,outs));
    return;
}

int main()
{
    init();
    floyed();
    work();
    print();
    return 0;
}
