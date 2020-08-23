/*
ID: axrdiv1
PROG: fence8
LANG: C++
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

ofstream fout("fence8.out");
ifstream fin("fence8.in");

int N, R;
int space, tot;
int boards[50 + 5],
    rails[1024 + 10],
    sum[1024 + 10];

bool dfs(int pos, int dep, const int &ans) {
    if(dep == 0) return true;
    if(space > tot - sum[ans]) return false;
    for(int i = pos; i > 0; i--) {
        if(boards[i] >= rails[dep]) {
            boards[i] -= rails[dep];
            if(boards[i] < rails[1]) space += boards[i];
            bool flag = false;
            if(rails[dep] == rails[dep - 1])
                flag = dfs(i, dep - 1, ans);
            else
                flag = dfs(N, dep - 1, ans);

            if(boards[i] < rails[1]) space -= boards[i];
            boards[i] += rails[dep];

            if(flag) return true;
        }
    }
    return false;
}

int bs() {
    int l = 0, r = R;
    while(l < r) {
        int mid = (l + r) / 2 + 1;
        space = 0;
        if(dfs(N, mid, mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}

int main() {
    fin >> N;
    tot = 0;
    for(int i = 1; i <= N; i++) {
        fin >> boards[i];
        tot += boards[i];
    }

    fin >> R;
    for(int i = 1; i <= R; i++)
        fin >> rails[i];

    sort(boards + 1, boards + N + 1);
    sort(rails + 1, rails + R + 1);

    for(int i = 1; i <= R; i++) {
        sum[i] += sum[i - 1] + rails[i];
    }

    fout << bs() << endl;
    return 0;
}
