/*
ID: axrdiv1
PROG: inflate
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

const int maxm = 10000 + 5;
const int maxn = 10000 + 5;

ofstream fout("inflate.out");
ifstream fin("inflate.in");

int dp[maxm];

struct problem {
    int p, m;
    double per;
    problem(int p, int m): p(p), m(m) {
        per = (double)p / m;
    }
    bool operator< (const problem& ot) const {
        return per < ot.per;
    }
};

vector<problem> vec;

int M, N;
int main() {
    int point, minute;
    fin >> M >> N;
    for(int i = 0; i < N; i++) {
        fin >> point >> minute;
        vec.push_back(problem(point, minute));
    }

    for(int i = 1; i <= M; i++) {
        for(int j = 0; j < N; j++) {
            if(i < vec[j].m) continue;
            dp[i] = max(dp[i], dp[i-vec[j].m]+vec[j].p);
        }
    }

    fout << dp[M] << endl;
    return 0;
}
