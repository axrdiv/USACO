/*
ID: axrdiv1
PROG: calfflac
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdio>
#include<cctype>
using namespace std;
const int MAXN = 20000;

char original[MAXN], strip[MAXN];

int main() {
    freopen("calfflac.in", "r", stdin);
    freopen("calfflac.out", "w", stdout);
    int or_t = 0, st_t = 0;
    while(scanf("%c", &original[or_t]) != EOF) {
        char c = tolower(original[or_t]);
        if(c >= 'a' && c <= 'z') {
            strip[st_t++] = c;
        }
        or_t++;
    }

    int longest = 0;
    int idx = 0;

    for(int i = 0; i < st_t; i++) {
        int st = i;
        int ed = st + 1999;
        int tmpl = 0;
        while(st <= ed) {
            ed = min(ed, st_t - 1);
            if(strip[st] == strip[ed]) {
                if(st != ed)
                    tmpl += 2;
                else
                    tmpl += 1;
                st++;
                ed--;
            }
            else {
                if(st == i) ed--;

                st = i;
                tmpl = 0;
            }
        }
        if(tmpl > longest) {
            longest = tmpl;
            idx = i;
        }
    }
    cout << longest << endl;

    int tidx = 0;
    while(idx+1) {
        char c = tolower(original[tidx++]);
        if(c >= 'a' && c <= 'z') {
            idx--;
        }
    }

    tidx--;
    while(longest) {
        printf("%c", original[tidx]);
        char c = tolower(original[tidx++]);
        if(c >= 'a' && c <= 'z') {
            longest--;
        }
    }
    printf("\n");

    return 0;
}
