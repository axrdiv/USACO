#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue> 
#include<iostream>
#define clear(a,b) memset(a,b,sizeof a)
#define R register

using namespace std;

const int gz=1500000+10;

inline void in(R int &x)
{
    R int f=1;x=0;char s=getchar();
    while(!isdigit(s)){if(s=='-')f=-1;s=getchar();}
    while(isdigit(s)){x=x*10+s-'0';s=getchar();}
    x*=f;
}

int head[gz],depth[gz],tot,n,m,cur[gz],s,t;

struct cod{int u,v,w;}edge[gz];

inline void add(R int x,R int y,R int z)
{
    edge[++tot].u=head[x];
    edge[tot].v=y;
    edge[tot].w=z;
    head[x]=tot;
}

inline bool bfs()
{
    clear(depth,0);queue<int>q;
    depth[s]=1;q.push(s);
    for(R int i=1;i<=n;i++)cur[i]=head[i];
    while(!q.empty())
    {
        R int u=q.front();q.pop();
        for(R int i=head[u];i!=-1;i=edge[i].u)
        {
            if(depth[edge[i].v]==0 and edge[i].w>0)
            {
                depth[edge[i].v]=depth[u]+1;
                q.push(edge[i].v);
            }
        }
    }
    return depth[t];
}

inline int dfs(R int u,R int dist)
{
    if(u==t or !dist)return dist;
    R int di=0,f;
    for(R int i=cur[u];i!=-1;i=edge[i].u)
    {
        cur[u]=i;
        if(depth[edge[i].v]==depth[u]+1 and (f=dfs(edge[i].v,min(edge[i].w,dist))))
        {
            di+=f;dist-=f;
            edge[i].w-=f;edge[i^1].w+=f;
            if(dist==0)break;
        }
    }
    return di;
}

inline int dinic()
{
    R int ans=0;
    while(bfs())ans+=dfs(s,214748364);
    return ans;
}

int main()
{
    in(m),in(n);s=1,t=n;
    clear(head,-1);tot=-1;
    for(R int i=1,x,y,z;i<=m;i++)
    {
        in(x),in(y),in(z);
        add(x,y,z);add(y,x,0);
    }
    printf("%d\n",dinic());
}