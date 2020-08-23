/*
ID: axrdiv1
PROG: kimbits
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;
const int maxn = 31 + 5;
ofstream fout("kimbits.out");
ifstream fin("kimbits.in");

int d[maxn][maxn];
int N, L;
long long int I;
unsigned int tmp;
// using dp solution
// 状态转移方程：
// d(n,l) = d(n-1,l) + d(n-1,l-1);
// d(n,l) 表示在n位中，恰有l个二进制1的个数。
void dp() {
    // initial states
    for(int i = 0; i <= N; i++)
        d[i][0] = 1;

    for(int i = 1; i <= N; i++)
        for(int j = 1; j <= i; j++)
            d[i][j] = d[i-1][j] + d[i-1][j-1];
}

bool num[33];

void search() {
    // consider l from high postion to low postion
    // and count sum from low postion to high position
    // if the sum of d[k][0...l] is enough (also means d[k-1][0...l] doesn't counting enough)
    // that's means num[k] is 1
    // and 1...k-1 position must have l-1 1s.
    long long int tI = I;
    for(int l = L; l > 0; l--) {
        long long int s, last;
        for(int k = 0; k <= N; k++) {
            last = s;
            s = 0;
            for(int i = 0; i <= l; i++)
                s += d[k][i];
            if(s >= tI) {
                num[k] = 1, tI -= last;
                break;
            }
        }
    }
}

int main() {
    fin >> N >> L >> I;
    dp();
    search();
    for (int k = N; k >= 1; k--)
        fout << num[k];
    fout << endl;
    return 0;
}
