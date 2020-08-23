//dp[5005]为子序列长度，num[5005]为种类
//这里就不写高精度了（只有90分），防抄袭，自己写 
#include<bits/stdc++.h>//万能头文件 
using namespace std;//流操作命名空间 

//lines[5005]是股价，其余不赘述 
int lines[5005];
int dp[5005];
long long num[5005];

ofstream fout("buylow.out");
ifstream fin("buylow.in");

int main(){
    //输入与各种初值 
    int a;fin>>a;int mx=0;
    long long nums=0;
    lines[0]=2147483647;
    dp[0]=0;
    num[0]=1;
    for(int i=1;i<=a;i++)
        fin>>lines[i];//输入 
    for(int i=1;i<=a;i++){
        //遍历每一天 
        for(int j=i-1;j>=0;j--){//找此天最长子序列 
            if(lines[i]<lines[j] and dp[i]<=dp[j])
                dp[i]=dp[j]+1;
        }
        for(int j=i-1;j>=0;j--){
            //加上所有上一子序列值的NUM
            //直到值相等就停止 
            if(lines[i]<lines[j] and dp[i]==dp[j]+1)
                num[i]+=num[j]; 
            else if(lines[i]==lines[j] and dp[i]==dp[j])
                break;
        }
    }

    //找到最大DP，并得到此DP num的总和 
    for(int i=1;i<=a;i++)
        if(mx<dp[i]) {
            mx=dp[i];nums=num[i];
        } else if(mx==dp[i])
            nums+=num[i];

    cout<<mx<<" "<<nums << endl;//输出 
    return 0;
}
