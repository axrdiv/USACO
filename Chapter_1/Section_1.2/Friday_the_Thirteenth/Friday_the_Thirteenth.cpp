/*
ID: axrdiv1
PROG: friday
LANG: C++
*/

#include<iostream>
#include<fstream>

using namespace std;

#define START 1900

const int days[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

int hist[10] = {0};

int main() {
    ofstream fout ("friday.out");
    ifstream fin ("friday.in");
    int n, w = 5;
    fin >> n;
    for(int y = START; y < START + n; y++) {
        int idx;
        if(((y%100 == 0) && (y%400 == 0)) || ((y%100 != 0) && (y%4 == 0)))
            idx = 1;
        else
            idx = 0;
        for(int m = 1; m <= 12; m++) {
            hist[w]++;
            w = (w + days[idx][m]) % 7;
        }
    }
    for(int i = 0; i < 6; i++)
        fout << hist[(i+5)%7] << " ";
    fout << hist[(6+5)%7] << endl;
    return 0;
}
