#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;
int n,f[5003][5003],a[5003];
int ans=0;
int main(){
    scanf("%d",&n);

    // read data from stdin
    for(int i=1;i<=n;i++)
        scanf("%d",&a[i]);

    // 与前一位的差，
    // 这样可以不考虑变调问题
    for(int i=n;i;i--)
        a[i]-=a[i-1];

    // 
    for(int i=2;i<=n;i++)
        for(int j=i+ans+1;j<=n;j++)
            if(a[i]==a[j]) {
                f[i][j] = min(j-i-1, f[i-1][j-1]+1);
                ans = max(ans, f[i][j]);
            }

    printf("%d\n",ans>3?ans+1:0);
    return 0;
}
