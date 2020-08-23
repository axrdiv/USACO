
/*
TASK: prime3
ID: jasison2
LANG: C++
*/

#include<cstdio>
#include<cmath>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 100000;
bool notp[N];
vector<int>v[46][10];
int calc(int x){
    int ret=0;
    while(x){
        ret+=x%10;
        x/=10;
    }
    return ret;
}
void process(){
    memset(notp,0,sizeof(notp));
    int up=int(sqrt(N));
    for(int i=2;i<=up;++i){
        if(!notp[i]){
            for(int j=i*i;j<N;j+=i){
                notp[j]=1;
            }
        }
    }
    for(int i=10000;i<N;++i){
        if(!notp[i]){
            v[calc(i)][i/10000].push_back(i);
        }
    }
}
int sum,head,an;
int ma[5][5];
struct Ans{
    int matrix[5][5];
    bool operator<(const Ans &obj)const {
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j){
                if(matrix[i][j]!=obj.matrix[i][j]){
                    return matrix[i][j]<obj.matrix[i][j];
                }
            }
        }
        return 0;
    }
    void output(){
        for(int i=0;i<5;++i){
            for(int j=0;j<5;++j){
                printf("%d",matrix[i][j]);
            }
            puts("");
        }
    }
}ans[200];
bool judge(int r,int c,int x){
    if(x<0||x>9){
        return 0;
    }
    if(c==4 || r==4){
        if(!(x&1) || x==5){
            return 0;
        }
    }
    if(r==0 || c==0){
        if(x==0){
            return 0;
        }
    }
    return 1;
}
bool fill(bool row,int index,int x){
    bool flag=1;
    if(row){
        for(int j=4;j>=0;--j){
            ma[index][j]=x%10;
            if(!judge(index,j,x%10)){
                flag=0;
            }
            x/=10;
        }
    }else{
        for(int i=4;i>=0;--i){
            ma[i][index]=x%10;
            if(!judge(i,index,x%10)){
                flag=0;
            }
            x/=10;
        }
    }
    return flag;
}
void pushAns(){
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){
            ans[an].matrix[i][j]=ma[i][j];
        }
    }
    an++;
}
bool judge(bool row,int index){
    int tot;
    if(row){
        tot=0;
        for(int j=0;j<5;++j){
            tot=10*tot+ma[index][j];
        }
        if(!binary_search(v[sum][ma[index][0]].begin(),v[sum][ma[index][0]].end(),tot)) {
            return 0;
        }
    }else{
        tot=0;
        for(int i=0;i<5;++i){
            tot=10*tot+ma[i][index];
        }
        if(!binary_search(v[sum][ma[0][index]].begin(),v[sum][ma[0][index]].end(),tot)) {
            return 0;
        }
    }
    return 1;
}
bool specialjudge(){
    int tot=0;
    for(int i=0;i<5;++i){
        tot=10*tot+ma[i][i];
    }
    if(!binary_search(v[sum][ma[0][0]].begin(),v[sum][ma[0][0]].end(),tot)) {
        return 0;
    }
    tot=0;
    for(int i=0;i<5;++i){
        tot=10*tot+ma[4-i][i];
    }
    if(!binary_search(v[sum][ma[4][0]].begin(),v[sum][ma[4][0]].end(),tot)) {
        return 0;
    }
    return 1;
}
bool alljudge(){
    return judge(false, 0) &&
           judge(false, 1) &&
           judge(true, 1)  &&
           judge(true, 2)  &&
           judge(true, 3)  &&
           judge(true, 4)  &&
           specialjudge();
}
void output(){
    for(int i=0;i<5;++i){
        for(int j=0;j<5;++j){
            printf("%d",ma[i][j]);
        }
        puts("");
    }
    puts("");
}
void fillall(){
    ma[1][1]=sum-ma[0][0]-ma[2][2]-ma[3][3]-ma[4][4];
    if(!judge(1,1,ma[1][1])) return;
    ma[1][0]=sum-ma[1][1]-ma[1][2]-ma[1][3]-ma[1][4];
    if(!judge(1,0,ma[1][0])) return;
    for(ma[4][0]=1;ma[4][0]<10;ma[4][0]+=2){
        if(ma[4][0]==5) continue;
        ma[3][1]=sum-ma[4][0]-ma[2][2]-ma[1][3]-ma[0][4];
        if(!judge(3,1,ma[3][1])) continue;
        ma[4][1]=sum-ma[4][0]-ma[4][2]-ma[4][3]-ma[4][4];
        if(!judge(4,1,ma[4][1])) continue;
        ma[3][0]=sum-ma[3][1]-ma[3][2]-ma[3][3]-ma[3][4];
        if(!judge(3,0,ma[3][0])) continue;
        ma[2][1]=sum-ma[0][1]-ma[1][1]-ma[3][1]-ma[4][1];
        if(!judge(2,1,ma[2][1])) continue;
        ma[2][0]=sum-ma[0][0]-ma[1][0]-ma[3][0]-ma[4][0];
        if(!judge(2,0,ma[2][0])) continue;
        if(alljudge()){
            pushAns();
        }
    }
}
void dsolve(int c){
    if(c==1){
        fillall();
        return;
    }
    for(int i=v[sum][ma[0][c]].size()-1;i>=0;--i){
        if (fill(false,c,v[sum][ma[0][c]][i])){
            dsolve(c-1);
        }
    }
}
void solve(){
    an=0;
    for(int i=v[sum][head].size()-1;i>=0;--i){
        if (fill(true,0,v[sum][head][i])){
            dsolve(4);
        }
    }
    if(an==0){
        puts("NONE");
    }else{
        sort(ans,ans+an);
        for(int i=0;i<an;++i){
            if(i!=0){
                puts("");
            }
            ans[i].output();
        }
    }
}
int main() {
    freopen("prime3.in","r",stdin);
    freopen("prime3.out","w",stdout);
    process();
    while(scanf("%d%d",&sum,&head)!=EOF){
        solve();
    }
    return 0;
}
