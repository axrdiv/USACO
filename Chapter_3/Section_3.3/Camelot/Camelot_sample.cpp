#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

struct pp{
    int l,c;
    int d;
}kn[2000],ki;

int st,r,c;
int dx[8]={1,2,2,1,-1,-2,-2,-1};
int dy[8]={2,1,-1,-2,-2,-1,1,2};
bool v[50][30];
int ans=1000000000,sum,d[50][30][50][30];//d[a,b,c,d] -> (a,b) to (c,d)
queue<pp> q;

bool yuejie(int x,int y)
{
    return (x<=0||x>r||y<=0||y>c);
}

void bfs(int bx,int by)
{
    memset(v,0,sizeof(v));
    q.push((pp){bx,by,0}); v[bx][by]=1; d[bx][by][bx][by]=0;
    while (!q.empty())
    {

        int xx=q.front().l,yy=q.front().c;

        d[bx][by][xx][yy]=q.front().d; q.pop();

        for (int i=0;i<8;i++)
        {
            int x=xx+dx[i],y=yy+dy[i];
            if (!yuejie(x,y)&&!v[x][y]) v[x][y]=1,q.push((pp){x,y,d[bx][by][xx][yy]+1});
        }
    }
}

void print(int x,int y)
{
    for (int i=1;i<=r;i++,cout<<endl)
    for (int j=1;j<=c;j++) cout<<d[i][j][x][y]<<" ";
    cout<<endl;
}

int a(int x){return (x>0)?x:-x;}

int main()
{
    cin>>r>>c;
    memset(d,0x10f,sizeof(d));
    char cross; int line;
    while (cin>>cross>>line)
    {
        if (st==0) st=1,ki.l=line,ki.c=cross-'A'+1;
        else kn[st].l=line,kn[st++].c=cross-'A'+1;
    }
    st--;
    //1,2
    for (int i=1;i<=r;i++)
      for (int j=1;j<=c;j++) bfs(i,j);

    //3,4,5
    for (int i=1;i<=r;i++)
    for (int j=1;j<=c;j++)  //ji he point 
    {
        int sum=0;
//      print(i,j);
        for (int k=1;k<=st;k++) sum+=d[kn[k].l][kn[k].c][i][j];
        ans=min(sum+max(a(ki.l-i),a(ki.c-j)),ans);
        for (int k=1,summ=sum;k<=st;summ=sum,k++)  //knight who pick up the king
        {
            summ-=d[kn[k].l][kn[k].c][i][j];
            for (int ii=max(1,ki.l-3);ii<=min(r,ki.l+3);ii++)  //别越界了 
              for (int jj=max(1,ki.c-3);jj<=min(c,ki.c+3);jj++)
              ans=min(
                summ+d[kn[k].l][kn[k].c][ii][jj]+
                max(a(ii-ki.l),a(jj-ki.c))+d[ii][jj][i][j],ans);
        }
    }
    cout<<ans<<endl;
}