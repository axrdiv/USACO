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

// d(k,i,j) 最高层k，树有i个节点，第k层有j个节点
int d[maxk][maxn][100+10];     // 最多有199个节点，那么最多有100个叶子节点

int C(int jn, int j2) {
    long long tmp = 1;
    for(int i = 0; i < j2; i++) {
        tmp = tmp * (jn-i);
        tmp = tmp / (i+1);
    }
    return tmp % HASH;
}

// i - j + 1 /2
void dp() {
    for(int k = 3; k <= K; k++) {
        for(int i = 5; i <= N; i+=2) {
            for(int j = 2; j <= (i+1)/2; j+=2) {
                for(int jn = j/2; jn <= (i-j+1)/2; jn++) {
                    if(jn%2 || d[k-1][i-j][jn] == 0) continue;
                    // cout << k << " " << i << " " << j << " " << jn << " " << d[k-1][i-j][jn] << endl;
                    d[k][i][j] = (d[k][i][j] + d[k-1][i-j][jn] * C(jn, j/2)) % HASH;
                    // cout << k << " " << i << " " << j << " " << jn << " " << d[k][i][j] << " " << d[k-1][i-j][jn] << endl;
                }
            }
        }
    }
}

int main() {
    ofstream fout("nocows.out");
    ifstream fin("nocows.in");
    fin >> N >> K;
    d[2][3][2] = 1;
    // cout << "k i j jn d d-1" << endl;
    dp();
    int cnt = 0;
    for(int i = 0; i < 100; i++) {
        (cnt += d[K][N][i]) %= HASH;
    }
    fout << cnt << endl;

    return 0;
}
