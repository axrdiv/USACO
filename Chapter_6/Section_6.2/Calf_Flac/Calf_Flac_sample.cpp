#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<cmath>
#include<algorithm>
#include<queue>
#include<stack>
#include<deque>
#include<map>
#include<iostream>
using namespace std;
typedef long long  LL;
const double pi=acos(-1.0);
const double e=exp(1);
const int N = 200009;
 
char con[N],name[N];
 
int main()
{
    int i=0,p,j=0,n,t;
    while(scanf("%c",&con[i])!=EOF)
    {
        if((con[i]>=65&&con[i]<=90)||(con[i]>=97&&con[i]<=122))
        {
            name[j++]=con[i];
        }
        i++;
    }
    int head,tail,mid=0,most=0;
    int spot=1;
 
    t=i-1;
    n=j-1;
 
    for(i=0; i<=n; i++)
    {
        mid=0;
        head=i;
        tail=i+1999;
        while(1)
        {
            if(tail>n)
                tail=n;
            else
            {
                if(head>tail)
                    break;
                if(name[head]>=65&&name[head]<=90&&(name[head]==name[tail])||(name[head]+32==name[tail]))
                {
 
                        if(head!=tail)
                            mid+=2;
                        else
                            mid+=1;
                        head++;
                        tail--;
 
                }
                else if(name[head]>=97&&name[head]<=122&&(name[head]==name[tail])||(name[head]-32==name[tail]))
                {
                        if(head!=tail)
                            mid+=2;
                        else
                            mid+=1;
                        head++;
                        tail--;
                }
                else
                {
                    if(head==i)
                        tail--;
 
                    head=i;
                    mid=0;
                }
            }
        }
        if(mid>most)
        {
            most=mid;
            spot=i+1;
        }
    }
 
    int cnt=0;
    printf("%d\n",most);
 
    for(i=0; i<=t; i++)
    {
        if((con[i]>=65&&con[i]<=90)||(con[i]>=97&&con[i]<=122))
        {
            cnt++;
        }
        if(cnt==spot)
        {
            cnt=0;
            for(j=i; cnt<most; j++)
            {
                if((con[j]>=65&&con[j]<=90)||(con[j]>=97&&con[j]<=122))
                    cnt++;
                printf("%c",con[j]);
            }
            break;
        }
    }
    if(most!=0)
        putchar('\n');
    return 0;
}