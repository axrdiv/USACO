/*
ID: axrdiv1
PROG: nocows
LANG: C++
*/

/* 需要知道的一些树的特性
 * 1. 非空二叉树的叶子节点数量等于双分支节点的数量加1.
 *
 */

/* 使用dp的话
 * 考虑一个状态转移方程：
 * d(k,i,j) = d(k-1,i-j, jn) * C(jn, j/2); 其中jn从j/2到...不等
 */

#include<iostream>
#include<fstream>
using namespace std;
const int maxn = 200 + 10;
const int maxk = 100 + 10;
const int HASH = 9901;
int N, K;

int d[maxn][maxk];

void dp() {
    for(int k = 2; k <= K; k++) {
        for(int i = 3; i <= N; i+=2) {
            for(int j = 1; j < i; j+=2) {
                (d[i][k] += d[j][k-1]*d[i-1-j][k-1]) %= HASH;
            }
        }
    }
}

int main() {
    ofstream fout("nocows.out");
    ifstream fin("nocows.in");
    fin >> N >> K;
    for(int k = 1; k <= K; k++) d[1][k] = 1;
    dp();
    cout << (d[N][K] - d[N][K-1] + HASH) % HASH<< endl;

    return 0;
}
