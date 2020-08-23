/*
ID: lorelei3
TASK: latin
LANG: C++
*/

#include <fstream>
#include <memory.h>

using namespace std;

const int fact[] = {1,1,2,6,24,120,720};
const int MAXN = 10;

ifstream fin("latin.in");
ofstream fout("latin.out");

int n, id, cnt[MAXN], a[MAXN];
long long ans;
bool row[MAXN][MAXN], col[MAXN][MAXN], v[MAXN];

void find(){
    id=2;
    int l,t;
    memset(v, false, sizeof(v));
    for(int i=1; i<=n; ++i)
        if(!v[i]){
            t=i; l=0;
            do{
                v[t]=true;
                t = a[t];
                l++;
            }while(!v[t]);
            if(l>id)
                id=l;
        }
}

void dfs(int x, int y){

    for(int i=1; i<=n; ++i)
        if(row[x][i] && col[y][i]){
            if(x==2){
                a[y]=i;
                if(y==n){
                    find();
                    if(cnt[id]>0){
                        ans += cnt[id];
                        return;
                    }
                }
            }
            row[x][i]=false;
            col[y][i]=false;
            if(y==n){
                if(x==n-1){
                    cnt[id]++;
                    ans++;
                }else
                    dfs(x+1, 2);
            }else
                dfs(x, y+1);
            row[x][i]=true;
            col[y][i]=true;
        }
}

int main(){
    fin>>n; 

    if(n==2)
        ans=1;
    else{
        int i;
        memset(row, true, sizeof(row));
        memset(col, true, sizeof(col));
        memset(cnt, 0, sizeof(cnt));
        for(i=2; i<n; ++i) row[i][i]=false;
        for(i=1; i<=n; ++i) col[i][i]=false;
        ans=0;
        a[1]=2;
        dfs(2,2);
        ans *= fact[n-1];
    }

    fout<<ans<<endl;

    return 0;
}