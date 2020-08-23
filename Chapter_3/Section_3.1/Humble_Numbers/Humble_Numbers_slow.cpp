/*
ID: axrdiv1
PROG: humble
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<queue>
#include<functional>
#include<vector>
#include<set>
using namespace std;

typedef long long LL;
const LL maxn = (1<<30);

ofstream fout("humble.out");
ifstream fin("humble.in");

vector<LL> primes;

priority_queue<LL, vector<LL>, greater<LL> > que;
set<LL> vis;

int K, N;
int main() {
    LL p;
    fin >> K >> N;
    for(int i = 0; i < K; i++) {
        fin >> p;
        primes.push_back(p);
    }

    que.push(1);
    N++;
    while(N) {
        LL t = que.top(); que.pop();
        vis.erase(t);
        N--;
        if(N == 0) {
            fout << t << endl;
            break;
        }
        for(int j = 0; j < K; j++) {
            LL p = t * primes[j];
            if(p < maxn) {
                if(vis.count(p)) continue;
                else {
                    vis.insert(p);
                    que.push(t * primes[j]);
                }
            }
        }
    }
    return 0;
}
