/*
 * 使用了
 * Tarjan算法
 */

#include <bits/stdc++.h>
using namespace std;

vector<int> g[105];
set<int> gg[105];
int n,
    dfn[105],
    low[105],
    inst[105],
    bcc[105],
    index_=0,
    cnt=0;

int inDegree[105];
stack<int> st;
void tarjan(int x)
{
    index_++;
    low[x]=dfn[x]=index_;
    st.push(x);
    inst[x]=1;
    for(int i = 0; i< (int)g[x].size(); i++)
    {
        if(!dfn[g[x][i]])
        {
            tarjan(g[x][i]);
            low[x]=min(low[x],low[g[x][i]]);
        }
        else if(inst[g[x][i]])
            low[x]=min(low[x],dfn[g[x][i]]);
    }
    if(dfn[x] == low[x])
    {
        cnt++;
        while(st.top() != x)
        {
            bcc[st.top()]=cnt;
            inst[st.top()]=0;
            st.pop();
        }
        bcc[st.top()]=cnt;
        inst[st.top()]=0;
        st.pop();
    }
}
int main()
{
//  freopen("","r",stdin);
//  freopen("","w",stdout);
    ios::sync_with_stdio(0);   //syn加速

    cin>>n;

    for(int i = 1; i <= n; i++)
    {
        int x;
        while(cin>>x && x)
            g[i].push_back(x);
    }

    for(int i = 1; i <= n; i++)
        if(!dfn[i])
            tarjan(i);

    for(int i = 1; i <= n; i++)
    {
        for(int j = 0; j < (int)g[i].size(); j++)
        {
            if(bcc[g[i][j]]!=bcc[i] && gg[bcc[i]].find(bcc[g[i][j]])==gg[bcc[i]].end())
            {
                gg[bcc[i]].insert(bcc[g[i][j]]);
                inDegree[bcc[g[i][j]]]++;
            }
        }
    }
    int ans1=0,ans2=0;
    for(int i=1;i<=cnt;i++)
    {
        if(inDegree[i]==0) ans1++;
        if(gg[i].size()==0) ans2++;
    }
    if(cnt==1)
        cout<<1<<endl<<0<<endl;
    else
        cout<<ans1<<endl<<max(ans1,ans2)<<endl;
    return 0;
}
