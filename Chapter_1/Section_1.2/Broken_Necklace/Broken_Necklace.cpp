/*
ID: axrdiv1
PROG: beads
LANG: C++
*/
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>

using namespace std;
int n;
string beads;

int count(int p) {
    // right
    char color = beads[p];
    int t = p, cnt = 1;
    while(cnt < n && (beads[(t+1)%n] == 'w' || beads[(t+1)%n] == color)) {
        cnt++;
        t = (t+1)%n;
    }
    // left
    t = (p + n - 1) % n;
    while(cnt < n && beads[t] != color) {
        cnt++;
        t = (t + n - 1) % n;
    }
    return cnt;
}

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
    fin >> n >> beads;
    int ret = 0;
    for(int i = 0;i < n; i++) {
        if(beads[i] == 'w') continue;
        if(beads[i] == beads[(i+n-1)%n]) continue;
        ret = max(ret, count(i));
    }
    if(ret == 0) ret = n;
    fout << ret << endl;
    return 0;
}
