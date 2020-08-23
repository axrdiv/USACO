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

bool mycmp(char* sa, char* sb) {
    for(int i = 0; i < L; i++) {
        if(*(sa+i) != *(sb+i))
            return *(sa+i) < *(sb+i);
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
    for(int i = 1; i < L; i++) {
        if(mycmp(str+i, minstr)) {
            minstr = str + i;
            mini = i;
        }
    }
    printf("%d\n", mini);

    return 0;
}
