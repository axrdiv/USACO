/*
ID: ylx14271
PROG: milk6
LANG: C++
 */
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int read()
{
    char s;int k=0,base=1;
    while((s=getchar())!='-'&&s!=EOF&&!(s>='0'&&s<='9'));
    if(s==EOF)exit(0);
    if(s=='-')base=-1,s=getchar();
    while(s>='0'&&s<='9'){k=k*10+(s-'0');s=getchar();}
    return k*base;
}
void write(int x)
{
    if(x<0){putchar('-');write(-x);}
    else{if(x/10)write(x/10);putchar(x%10+'0');}
}
int pre[100];
int n,m;
struct node
{
    int u,v,w;//w:损失
    int id;
} a[3000];
int f[50][50];//流量(损失
int c[50][50];
int p[100],a1;
int u1,v1,c1;
int q[4000];
void add(int uu,int vv,int ww)//连两条边,一条正的边和一条反向边
{
    f[uu][vv]+=ww;//加到uu→vv这条边上去
    a1++;
    a[a1].id=a1;
    a[a1].u=uu;a[a1].v=vv;a[a1].w=ww;//存起来
}
int w[4000],d1;
int cmp(node aa,node bb)
{
    if (aa.w==bb.w) return aa.id<bb.id;
    return aa.w>bb.w;
}
int spfa(int x)
{
    memcpy(c,f,sizeof(c));//c存f数组的东西
    c[a[x].u][a[x].v]-=a[x].w;//删掉这条边
    int ans1=0;
    while (true)//搜到 搜不到路径
    {
        int l=0,r=1;q[1]=1;
        memset(pre,-1,sizeof(pre));//初始化
        while (l<r)
        {
            l++;
            int x1=q[l];
            //cout<<x1<<" ";
            for (int i=1;i<=n;i++)
            {
                if (c[x1][i]>0&&pre[i]==-1)//没被走过(没有前驱)并且流量<容量
                {
                    pre[i]=x1;//标记
                    r++;q[r]=i;//入队
                }
            }
            if (pre[n]>0) break;//搜完了
        }
        //cout<<endl;
        if (pre[n]==-1) break; //找不到就退掉
        int mi=233333333;
        for (int i=n;i>1;i=pre[i]) mi=min(mi,c[pre[i]][i]);//找瓶颈
        for (int i=n;i>1;i=pre[i]) c[pre[i]][i]-=mi;//减去
        ans1+=mi;
        //cout<<"---   "<<mi<<"   \n";
    }
    return ans1;
}
int main()
{
    freopen("milk6.in","r",stdin);
    freopen("milk6.out","w",stdout);
    n=read();
    m=read();
    a1=0;
    for (int i=1;i<=m;i++)//建图
    {
        u1=read();v1=read();c1=read();
        add(u1,v1,c1);
    }
    int xxx=spfa(0);//找最大流
    printf("%d ",xxx);
    d1=0;
    int s1=0;
    sort(a+1,a+m+1,cmp);
    for (int j=1;j<=m;j++)//一条一条边的删
    {
        s1=spfa(j);
        if (s1+a[j].w==xxx)    
        {
            f[a[j].u][a[j].v]-=a[j].w;//开始没写这句然后炸了
            d1++;//存起来
            w[d1]=a[j].id;
            xxx=s1;
        }
    }
    printf("%d\n",d1);
    sort(w+1,w+d1+1);//从小到大排序
    for (int i=1;i<=d1;i++) printf("%d\n",w[i]);
    return 0;
}