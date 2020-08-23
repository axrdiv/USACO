/*
ID:xsy97051
LANG:C++
TASK:cowxor
*/
#include <iostream>
#include <cstdio>
using std::cout, std::cin, std::endl;
int num[100005],next[1000005][2],pos[1000005];

int main()
{
    freopen("cowxor.in", "r", stdin);
    freopen("cowxor.out", "w", stdout);
    int k,ans=0,anss=1,anse=1,tot=1,n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>num[i];
        num[i]^=num[i-1];

        k=1;
        for(int j=20;j>=0;j--)
        {
            if(!next[k][(num[i-1]>>j) & 1])         //如果相同就不添加，保证靠前
                next[k][(num[i-1]>>j) & 1] = ++tot; //记录指向的位置
            k = next[k][(num[i-1]>>j) & 1];
        }

        pos[k]=i-1;

        k=1;
        for(int j=20;j>=0;j--)
            if(next[k][!((num[i]>>j) & 1)])
                k=next[k][!((num[i]>>j) & 1)];
            else
                k=next[k][(num[i]>>j) & 1];

        if((num[i]^num[pos[k]]) > ans)
        {
            ans=num[i]^num[pos[k]];
            anss=pos[k]+1;
            anse=i;
        }
    }

    cout<<ans<<" "<<anss<<" "<<anse<<endl;
    return 0;
}
