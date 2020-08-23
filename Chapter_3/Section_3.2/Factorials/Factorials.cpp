/*
ID: axrdiv1
PROG: fact4
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cmath>
#include<map>
#include<vector>
using namespace std;
typedef long long LL;
const int maxn = 4220 + 10;

ofstream fout("fact4.out");
ifstream fin("fact4.in");
int n;
int prim[maxn], cnt[maxn];

bool is_prim(int p) {
    if(p == 1) return false;
    if(p == 2) return true;
    if(p == 3) return true;
    for(int i = 2; i <= sqrt(p); i++) {
        if(p % i == 0) return false;
    }
    return true;
};

void solve() {
    for(int ti = 2; ti <= n; ti++) {
        if(is_prim(ti)) {
            prim[ti] = 1;
            cnt[ti]++;
        }
        else {
            int nti = ti;
            for(int i = 2; i <= ti/2; i++) {
                if(!prim[i]) continue;
                while(!(nti%i)) {
                    nti /= i;
                    cnt[i]++;
                }
                if(nti == 1) break;
            }
        }
    }
}

int dry(int ret, int p, int cnt) {
    int pp = 1;
    for(int i = 0; i < cnt; i++) 
        pp = (pp * p) % 10;
    ret = (ret * pp) % 10;
    return ret;
}

int main() {
    fin >> n;
    solve();
    /*
    for(int i = 0; i <= n; i++) {
        if(prim[i]) cout << i << " " << cnt[i] << endl;
    }
    */
    int maxzero = min(cnt[2], cnt[5]);
    cnt[2] -= maxzero;
    cnt[5] -= maxzero;
    int ret = 1;
    for(int i = 1; i <= n; i++) {
        if(!prim[i] || cnt[i] == 0) continue;
        ret = dry(ret, i, cnt[i]);
    }
    fout << ret << endl;
    return 0;
}
