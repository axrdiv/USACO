/*
ID: axrdiv1
PROG: range
LANG: C++
*/
#include<iostream>
#include<fstream>
using namespace std;

const int maxn = 250 + 5;
// int square[maxn][maxn];
int d[2][maxn][maxn];
int cnt[maxn];

ofstream fout("range.out");
ifstream fin("range.in");

const int dx[] = {0, 0, 1, 1};
const int dy[] = {0, 1, 0, 1};

int N;
int main() {
    fin >> N;
    char c;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            fin >> c;
            d[0][i][j] = c-'0';
        }
    }
    /*
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            cout << d[1][i][j] << " ";
        }
        cout << endl;
    }
    */
    for(int dia = 2; dia <= N; dia++) {
        for(int i = 0; i <= N-dia; i++) {
            for(int j = 0; j <= N-dia; j++) {
            int flag = 1;
            for(int t = 0; t < 4; t++) {
                if(!d[dia&1][i+dx[t]][j+dy[t]]) {
                    flag = 0; break;
                }
            }
            d[~dia&1][i][j] = flag;
            cnt[dia] += flag;
            }
        }
    }

    for(int i = 2; i <= N; i++)
        if(cnt[i])
            fout << i << " " << cnt[i] << endl;
    return 0;
}
