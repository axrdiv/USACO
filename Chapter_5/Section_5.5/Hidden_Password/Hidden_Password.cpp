/*
ID: axrdiv1
PROG: hidden
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<cstdio>
#include<cstring>
using namespace std;
const int MAX_L = 100000 + 5;
char str[MAX_L * 2];
int L;

bool mycmp(char* sa, char* sb, int& st) {
    for(st = 0; st < L; st++) {
        if(*(sa+st) != *(sb+st))
            return *(sa+st) < *(sb+st);
    }
    return false;
}

int main() {
    freopen("hidden.in", "r", stdin);
    freopen("hidden.out", "w", stdout);
    scanf("%d\n", &L);
    int line = L / 72 + 1;
    for(int i = 0; i < line; i++) {
        scanf("%s\n", str + i*72);
    }
    memcpy(str+L, str, sizeof(char)*L);

    char* minstr = str;
    int mini = 0;
    int i = 1;
    while(i < L){
        int st = 0;
        if(mycmp(str+i, minstr, st)) {
            minstr = str + i;
            mini = i;
        }
        i += (st == 0) ? 1 : st;
    }
    printf("%d\n", mini);

    return 0;
}
