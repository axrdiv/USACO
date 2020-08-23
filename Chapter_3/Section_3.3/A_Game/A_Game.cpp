/*
ID: axrdiv1
PROG: game1
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;
const int maxn = 100 + 5;

int board[maxn], cumulate[maxn];
int d[maxn][maxn];

ofstream fout("game1.out");
ifstream fin("game1.in");

int dp(int l, int r) {
    if(l >= r) return 0;
    if(d[l][r] > 0) return d[l][r];
    int sum = cumulate[r] - cumulate[l];
    d[l][r] = sum - min(dp(l+1, r), dp(l, r-1));
    return d[l][r];
}
int N;
int main() {
    fin >> N;
    int cu = 0;
    for(int i = 0; i < N; i++) {
        cumulate[i] = cu;
        fin >> board[i];
        cu += board[i];
    }
    cumulate[N] = cu;

    /*
    for(int i = 0; i <= N; i++)
        cout << cumulate[i] << " ";
    cout << endl;
    */

    int p1 = dp(0, N);
    fout << p1 << " " << cumulate[N]-cumulate[0]-p1 << endl;

    return 0;
}
