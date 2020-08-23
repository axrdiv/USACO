#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#include<queue>
#include<fstream>

using namespace std;

ofstream fout("job.out");
ifstream fin("job.in");

struct node
{
    int nt,v;
    bool operator<(node k)const
    {
        return nt>k.nt;
    }
};

int n,cnta,cntb,ansa,ansb;
int t[1060];

priority_queue<node> q;

int main()
{
    fin >> n >> cnta >> cntb;

    for(int i=1;i<=cnta;i++)
    {
        node koishi;
        fin >> koishi.v;
        koishi.nt=koishi.v;
        q.push(koishi);
    }
    //推入一个优先队列 
    for(int i=1;i<=n;i++)
    {
        node koishi=q.top();
        q.pop();
        t[i]=koishi.nt;
        koishi.nt+=koishi.v;
        q.push(koishi);
    }
    ansa=t[n];
    //模拟[有空闲洗衣机就塞]过程 
    //第一问完毕 

    while(!q.empty())q.pop();

    for(int i=1;i<=cntb;i++)
    {
        node koishi;
        fin >> koishi.v;
        koishi.nt=koishi.v;
        q.push(koishi);
    }
    //同上推入队列 
    ansb=0;
    for(int i=n;i>=1;i--)//从后往前,这点很重要 
    {
        node koishi=q.top();
        q.pop();
        if(koishi.nt+t[i]>ansb)
            ansb=koishi.nt+t[i]; 
        koishi.nt+=koishi.v;//记录当前烘干机要在将来烘干第i件衣服
        q.push(koishi);
    }
    //模拟规划烘干的过程

    cout << ansa << " " << ansb << endl;

    return 0;
}
