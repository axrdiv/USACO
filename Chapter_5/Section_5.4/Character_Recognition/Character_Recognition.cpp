/*
ID: axrdiv1
PROG: charrec
LANG: C++
*/
#include<fstream>
#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

ofstream fout("charrec.out");
ifstream fin("charrec.in");
ifstream fontin("font.in");

int read(istream& is, vector<string>& v) {
    int N;
    is >> N;
    string s;
    for(int i = 0; i < N; i++) {
        is >> s;
        v.push_back(s);
    }
    return N;
}

int diff19(int lineno, char &ch, vector<vector<vector<int> > >& linediff, const int M) {
    int mindiff = -1;
    for(int i = 0; i < M; i++) {
        for(int miss = 0; miss < 20; miss++) {
            int totaldiff = 0;
            for(int j = 0; j < 19; j++) {
                if(j < miss)
                    totaldiff += linediff[lineno + j][i][j];
                else
                    totaldiff += linediff[lineno + j][i][j + 1];
            }
            if(mindiff < 0 || totaldiff < mindiff) {
                mindiff = totaldiff;
                ch = (i == 0 ? ' ' : ('a' + i - 1));
            }
        }
    }
    if(mindiff > 20 * 20 * 0.30)
        ch = '?';
    return mindiff;
}

int diff20(int lineno, char& ch, vector<vector<vector<int> > >& linediff, const int M) {
    int mindiff = -1;
    for(int i = 0; i < M; i++) {
        int totaldiff = 0;
        for(int j = 0; j < 20; j++) {
            totaldiff += linediff[lineno + j][i][j];
        }
        if(mindiff < 0 || totaldiff < mindiff) {
            mindiff = totaldiff;
            ch = (i == 0 ? ' ': ('a' + i - 1));
        }
    }
    if(mindiff > 20 * 20 * 0.3)
        ch = '?';

    return mindiff;
}

int diff21(int lineno, char &ch, vector<vector<vector<int> > >& linediff, const int M) {
    int mindiff = -1;
    for(int i = 0; i < M; i++) {
        for(int dublicated = 1; dublicated <= 20; ++dublicated) {
            int totaldiff = 0;
            for(int j = 0; j < 21; ++j) {
                if(j < dublicated)
                    totaldiff += linediff[lineno + j][i][j];
                else if(j == dublicated) {
                    if(linediff[lineno + j][i][j - 1] < linediff[lineno + j - 1][i][j - 1])
                        totaldiff = totaldiff - linediff[lineno + j - 1][i][j - 1] + linediff[lineno + j][i][j - 1];
                }
                else
                    totaldiff += linediff[lineno + j][i][j - 1];
            }
            if(mindiff < 0 || totaldiff < mindiff) {
                mindiff = totaldiff;
                ch = (i == 0 ? ' ' : ('a' + i - 1));
            }
        }
    }
    if(mindiff > 20 * 20 * 0.3)
        ch = '?';
    return mindiff;
}

int main() {
    vector<string> font;
    vector<string> regn;
    int M = read(fontin, font) / 20;
    int N = read(fin, regn);
    vector<vector<vector<int> > > linediff(N, vector<vector<int> >(M, vector<int>(20, 0)));

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            for(int r = 0; r < 20; r++) {
                for(int c = 0; c < 20; c++) {
                    linediff[i][j][r] += (regn[i][c] != font[j*20+r][c]);
                }
            }
        }
    }

    vector<char> chars(N, '*');
    vector<int> prev(N, -1);
    vector<int> diff(N, -1);

    char ch;
    for(int i = 18; i < N; i++) {
        if(i - 19 == -1 || (i - 19 >= 0 && diff[i - 19] >= 0)) {
            diff[i] = diff19(i - 18, ch, linediff, M);
            if(i - 19 != -1)
                diff[i] += diff[i - 19];
            prev[i] = i - 19;
            chars[i] = ch;
        }
        if(i - 20 == -1 || (i - 20 >= 0 && diff[i - 20] >= 0)) {
            int d = diff20(i - 19, ch, linediff, M);
            if(i - 20 != -1)
                d += diff[i - 20];
            if(diff[i] < 0 || d < diff[i]) {
                diff[i] = d;
                prev[i] = i - 20;
                chars[i] = ch;
            }
        }
        if(i - 21 == -1 || (i - 21 >= 0 && diff[i - 21] >= 0)) {
            int d = diff21(i - 20, ch, linediff, M);
            if(i - 21 != -1)
                d += diff[i - 21];
            if(diff[i] < 0 || d < diff[i]) {
                diff[i] = d;
                prev[i] = i - 21;
                chars[i] = ch;
            }
        }
    }

    int cur = N - 1;
    stack<char> st;
    while(cur != -1) {
        st.push(chars[cur]);
        cur = prev[cur];
    }

    while(!st.empty()) {
        fout << st.top();
        st.pop();
    }
    fout << endl;

    return 0;
}
