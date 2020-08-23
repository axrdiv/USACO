//niiick
#include<iostream>
#include<cmath>
#include<algorithm>
#include<queue>
#include<cstring>
#include<cstdio>
#include<map>
using namespace std;
typedef long long lt;

int read()
{
    int x=0,f=1;
    char ss=getchar();
    while(ss<'0'||ss>'9') {
        if(ss=='-')f=-1;
        ss=getchar();
    }
    while(ss>='0'&&ss<='9') { 
        x=x*10+ss-'0';
        ss=getchar();
    }
    return x*f;
} 

const int maxn=40010;
int n,m;
int a[maxn];
int rak[maxn],sa[maxn],tp[maxn],tax[maxn];
int height[maxn];

void rsort()
{
    for(int i=0;i<=m;++i)
        tax[i]=0;
    for(int i=1;i<=n;++i)
        tax[rak[i]]++;
    for(int i=1;i<=m;++i)
        tax[i]+=tax[i-1];
    for(int i=n;i>=1;--i)
        sa[tax[rak[tp[i]]]--]=tp[i];
}

void ssort()
{
    m=210;
    for(int i=1;i<=n;++i)
        rak[i]=a[i],tp[i]=i;

    rsort();
    for(int k=1;k<=n;k<<=1)
    {
        int p=0;
        for(int i=n-k+1;i<=n;++i)
            tp[++p]=i;
        for(int i=1;i<=n;++i)
            if(sa[i]>k)
                tp[++p]=sa[i]-k;

        rsort();
        swap(rak,tp);
        rak[sa[1]]=p=1;
        for(int i=2;i<=n;++i)
            rak[sa[i]]=(tp[sa[i]]==tp[sa[i-1]]&&tp[sa[i]+k]==tp[sa[i-1]+k])?p:++p;

        if(p>=n)
            break;
        m=p;
    }
}

void getH()
{
    int k=0;
    for(int i=1;i<=n;++i)
    {
        if(k) k--;
        int j=sa[rak[i]-1];
        while(a[i+k]==a[j+k])
            k++;
        height[rak[i]]=k;
    }
}

int check(int x)
{
    int mx=sa[1],mi=sa[1];
    for(int i=2;i<=n;i++)
    {
        if(height[i]<x)
            mx=mi=sa[i];
        else
        {
            if(sa[i]<mi)
                mi=sa[i];
            if(sa[i]>mx)
                mx=sa[i];
            if(mx-mi>x)
                return 1;
        }
    }
    return 0;
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        if(n==0)
            break;

        for(int i=1;i<=n;++i) 
            a[i]=read();

        for(int i=1;i<n;++i) 
            a[i]=a[i+1]-a[i]+90;
        n--;//差分数组长度少1

        ssort();
        getH();

        int ans=0;
        int L=0,R=n,mid;
        while(L<R)
        {
            mid=(L+R)>>1;
            if(check(mid))
                ans=mid,L=mid+1;
            else
                R=mid;
        }
        if(ans<4)
            printf("0\n");
        else
            printf("%d\n",ans+1);
    }
    return 0;
}
