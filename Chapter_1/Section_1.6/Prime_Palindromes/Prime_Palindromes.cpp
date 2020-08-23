/*
ID: axrdiv1
PROG: pprime
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
const int maxn = 8;
int dig[maxn];

bool is_prime(int p) {
    if(p < 2) return false;
    if(p == 2) return true;
    if(p % 2 == 0) return false;
    for(int i = 3; i * i <= p; i += 2) {
        if(p % i == 0) return false;
    }
    return true;
}

int a, b;

int nnum(int a) {
    int cnt = 0;
    while(a) {
        cnt++;
        a = a / 10;
    }
    return cnt;
}

int palin(int numl, int n) {
    int ret = numl;
    if(n & 1) numl = numl / 10;
    while(numl) {
        ret *= 10;
        ret += numl % 10;
        numl /= 10;
    }
    return ret;
}
int main() {
    ofstream fout("pprime.out");
    ifstream fin("pprime.in");
    fin >> a >> b;
    int na = nnum(a);
    int nb = nnum(b);
    for(int n = na; n <= nb; n++) {
        int nleft = (n+1)/2;
        for(int numl = pow(10, nleft-1); numl < pow(10, nleft)-1; numl++) {
            int p = palin(numl, n);
            if(p < a) continue;
            else if(p > b) break;
            if(is_prime(p)) fout << p << endl;
        }
    }
    return 0;
}
