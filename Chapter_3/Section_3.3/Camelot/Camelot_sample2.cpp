/*
ID:zhangji78
LANG:C++
TASK:camelot
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
int dx[8]={-2,-1,-2,1,2,2,1,-1};//骑士遍历的方向
int dy[8]={-1,2,1,2,1,-1,-2,-2};
const int inf=99999999;//假装这是正无穷（手动滑稽）
struct node
{
    int x,y,s;//用于宽搜的list数组。x->行坐标，y->列坐标，s->到这儿
}list[12000];//需要用几步。
struct wz
{
    int x,y;
}king,knight[12000];
//玄学...明明数据最大也就是26*40，却一定要开到12000，我之前开1200都
//会RE...
int n,m,tj,head,tail;
bool kk[30][50];
int bk[50][30][50][30],all,bs;
//bk[i][j][k][l]表示(i,j)到(k,l)骑士走的距离...
void bfs(int x,int y)
{
//emmm...标准的bfs，如果不喜欢可以改成dfs，但是时间...呵呵...因为
//该函数是要反复调用的...建议用bfs...
    head=1;tail=2;
    list[head].x=x;list[head].y=y;
    bk[x][y][x][y]=0;//这是一个坑点
    memset(kk,false,sizeof(kk));kk[x][y]=true;
    while(head<tail)
    {
        if(tail==n*m+1)break;
        for(int i=0;i<=7;i++)
        {
            int xx=list[head].x+dx[i],yy=list[head].y+dy[i];
            if(xx>=1&&xx<=n&&yy>=1&&yy<=m)
            {
                if(kk[xx][yy]==false)
                {
                    kk[xx][yy]=true;
                    list[tail].x=xx;list[tail].y=yy;
                    list[tail].s=list[head].s+1;
                    bk[x][y][xx][yy]=list[tail].s;
                    bk[xx][yy][x][y]=list[tail].s;
                    tail++;
                }
            }
        }
        head++;
    }
}
void build_bk()
{
    memset(bk,1,sizeof(bk));//本来想弄63的，后来炸了...
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)bfs(i,j);//反复调用，构建bk数组
    }
}
/*
这玩意儿本来是我之前想着先找集合点确定集合点再看怎么接皇帝的...
后来发现...是我太天真了...
但是还是把它保留着吧...留个纪念...（手动滑稽）
void find()
{
    int minn=inf,sum=0,xx,yy;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=m;j++)
        {
            for(int k=1;k<=tj;k++)sum+=bk[knight[k].x][knight[k].y][i][j];
            if(sum<minn)
            {
                minn=sum;
                xx=i;yy=j;
            }
            sum=0;
        }
    }
    for(int k=1;k<=tj;k++)all+=bk[knight[k].x][knight[k].y][xx][yy];
    edx=xx;edy=yy;
}
*/
int kn_ki()
{
    int minnn=inf;
    for(int edx=1;edx<=n;edx++)
    {
        for(int edy=1;edy<=m;edy++)
        {
            //枚举集合点...不会超时...
            int minn=inf;bool bkkk=false;
            for(int s=1;s<=tj;s++)
            {
                all+=bk[knight[s].x][knight[s].y][edx][edy];
                if(bk[knight[s].x][knight[s].y][edx][edy]>=bk[0][0][0][0]){bkkk=true;break;}
            }
            //all统计到这个点一共要多少步
            //bkkk是看有没有骑士不能到这里，如果不能到的话就不能做
            //集合点
            if(bkkk==true)
            {
                all=0;
                //这步不能省，贼坑了...
                continue;
            }
            for(int s=1;s<=tj;s++)
            {
                int ss=inf;
                for(int i=king.x-2;i<=king.x+2;i++)
                {
                    if(i>=1&&i<=n)
                    {
                        for(int j=king.y-2;j<=king.y+2;j++)
                        {
                            if(j>=1&&j<=m)
                            {
                                int jl=max(abs(i-king.x),abs(j-king.y));
                                //一大坑点啊...
                                ss=min(ss,bk[knight[s].x][knight[s].y][i][j]+bk[i][j][edx][edy]+jl);
                            }
                        }
                    }
                }
                minn=min(minn,all-bk[knight[s].x][knight[s].y][edx][edy]+ss);
                //不算这个点原来到终点的距离，直接算它接国王的距离
            }
            all=0;
            //这步不能省...贼坑...
            minnn=min(minnn,minn);
        }
    }
    return minnn;
}
int main()
{
    //freopen("camelot.in","r",stdin);
    //freopen("camelot.out","w",stdout);
    scanf("%d%d",&n,&m);
    getchar();char c;int xx,yy;bool bsk=false;
    while(cin>>c)//不能用scanf，会有玄学错误
    {
        yy=c-'A'+1;
        scanf("%d",&xx);//这玩意儿也是坑点...之前输入的时候是一个字
                        //符一个字符地输入，但是两位数就输入不了了
        if(bsk==false)king.x=xx,king.y=yy,bsk=true;//如果是第一个
        else
        {
            knight[++tj].x=xx;
            knight[tj].y=yy;
        }
    }
    if(tj==0)printf("0\n");//坑点*n！若没有骑士，就输出0！
    else
    {
        build_bk();
        printf("%d\n",kn_ki());
    }
    return 0;
}