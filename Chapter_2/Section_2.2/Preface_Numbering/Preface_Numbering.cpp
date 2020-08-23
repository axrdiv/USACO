/*
ID: axrdiv1
PROG: preface
LANG: C++
*/

/*
 *  I 1      L 50       M 1000
 *  V 5      C 100
 *  X 10     D 500
 */
#include<iostream>
#include<cmath>
#include<fstream>
#include<map>
#include<algorithm>
using namespace std;
const int maxn = 3500 + 10;

int d[7][maxn];
long long cnt[7];
map<int, int> index;

void init() {
    index.insert(make_pair(1, 0));
    index.insert(make_pair(5, 1));
    index.insert(make_pair(10, 2));
    index.insert(make_pair(50, 3));
    index.insert(make_pair(100, 4));
    index.insert(make_pair(500, 5));
    index.insert(make_pair(1000, 6));
    d[0][1] = 1;        // I
    d[0][4] = 1;        // IV
    d[1][4] = 1;        // IV
    d[1][5] = 1;        // V
    d[0][9] = 1;        // IX
    d[2][9] = 1;        // IX
    d[2][10] = 1;       // X
    d[2][40] = 1;       // XL
    d[3][40] = 1;       // XL
    d[3][50] = 1;       // L
    d[2][90] = 1;       // XC
    d[4][90] = 1;       // XC
    d[4][100] = 1;      // C
    d[4][400] = 1;      // CD
    d[5][400] = 1;      // CD
    d[5][500] = 1;      // D
    d[4][900] = 1;      // CM
    d[6][900] = 1;      // CM
    d[6][1000] = 1;     // M
}

void dp(int t) {
    for(int i = 0; i < 7; i++) {
        if(d[i][t]) return;
    }

    int idx = 0;
    int T = t;
    while(T) {
        int base = pow(10, idx);
        int tail = T % 10;

        if(tail <= 3) {
            d[index[base]][t] += tail * d[index[base]][base];
        }
        else if(tail == 4) {
            d[index[5*base]][t] += d[index[5*base]][4*base];
            d[index[base]][t] += d[index[base]][base];
        }
        else if(tail == 9) {
            d[index[10*base]][t] += d[index[10*base]][9*base];
            d[index[base]][t] += d[index[base]][9*base];
        }
        else {
            d[index[5*base]][t] += d[index[5*base]][5*base];
            d[index[base]][t] += (tail - 5) * d[index[base]][base];
        }
        T = T / 10;
        idx++;
    }
}

int n;
char cs[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};

int main() {
    ofstream fout("preface.out");
    ifstream fin("preface.in");
    fin >> n;
    // fill(d, d+7*maxn, -1);
    init();
    for(int i = 1; i <= n; i++) {
        dp(i);
    }
    for(int i = 0; i < 7; i++) {
        for(int t = 1; t <= n; t++)
            cnt[i] += d[i][t];
        if(cnt[i]) fout << (char)cs[i] << " " << cnt[i] << endl;
    }
    /*
    for(int t = 1; t <= n; t++) {
        for(int i = 0; i < 7; i++)
            cout << d[i][t];
        cout << " " << t << endl;
    }
    */
    return 0;
}
