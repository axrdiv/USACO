/*
ID: axrdiv1
PROG: hamming
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<int> L;
int N, B, D;

int countd(int dif) {
    int cnt = 0;
    for(int i = 0; i < B; i++) {
        if(dif & (1 << i)) cnt++;
    }
    return cnt;
}

bool can_push(int d) {
    for(int i = 0; i < L.size(); i++) {
        int dif = d ^ L[i];
        if(countd(dif) < D)
            return false;
    }
    return true;
}

int main() {
    ofstream fout("hamming.out");
    ifstream fin("hamming.in");
    fin >> N >> B >> D;
    int cnt = 0, idx = 0;
    while(cnt < N) {
        if(can_push(idx)) {
            L.push_back(idx);
            cnt++;
        }
        idx++;
    }
    for(int i = 0; i < N-1; i++) {
        if(i%10 < 9)
            fout << L[i] << " ";
        else if(i%10 == 9)
            fout << L[i] << endl;
    }
    fout << L[N-1] << endl;
    return 0;
}
