/*
ID: axrdiv1
PROG: dualpal
LANG: C++
*/
#include<fstream>
#include<iostream>

using namespace std;

char line[32];
int N, S;

bool is_pal(int num, int base) {
    int cnt = 0;
    while(num) {
        line[cnt++] = '0' + num%base;
        num = num / base;
    }
    int l = 0, r = cnt-1;
    while(l < r) {
        if(line[l] != line[r]) return false;
        l++;
        r--;
    }
    return true;
}

int main() {
    ofstream fout ("dualpal.out");
    ifstream fin ("dualpal.in");
    fin >> N >> S;

    for(int i = S+1; N; i++) {
        int cnt = 0;
        for(int b = 2; b <= 10; b++) {
            if(is_pal(i, b)) {
                cnt++;
                if(cnt == 2) {
                    fout << i << endl;
                    N--;
                    break;
                }
            }
        }
    }
    return 0;
}
