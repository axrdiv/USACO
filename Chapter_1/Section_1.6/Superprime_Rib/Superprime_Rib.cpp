/*
ID: axrdiv1
PROG: sprime
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
const int maxn = 1000000;
int dp[2][maxn];

int N;

bool is_prime(int p) {
    float s = sqrt(p);
    for(int i = 2; i <= s; i++) {
        if(p % i == 0) return false;
    }
    return true;
}

int main() {
    ofstream fout("sprime.out");
    ifstream fin("sprime.in");
    fin >> N;
    int t = 0, cnt = 4;
    dp[t][0] = 2; dp[t][1] = 3; dp[t][2] = 5; dp[t][3] = 7;
    for(int i = 2; i <= N; i++) {
        int ccnt = 0;
        for(int j = 0; j < cnt; j++) {
            for(int k = 1; k < 10; k += 2) {
                if(is_prime(10*dp[t][j]+k)) dp[t^1][ccnt++] = 10*dp[t][j]+k;
            }
        }
        cnt = ccnt;
        t ^= 1;
    }
    for(int i = 0; i < cnt; i++) {
        fout << dp[t][i] << endl;
    }
    return 0;
}
